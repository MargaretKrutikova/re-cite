open Types;

module GetCitations = [%graphql
  {|
  query($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      citations(order_by: {added: desc, id: desc}) @bsRecord {
        id
        text
        added @bsDecoder(fn: "Js.Json.decodeString")
        author @bsRecord {
          id
          name
        }
      }
    }
  }
|}
];

module PageQuery = ReasonApolloHooks.Query.Make(GetCitations);

[@react.component]
let make = (~slug, ~onEdit) => {
  let variables = GetCitations.make(~slug, ())##variables;
  let (simple, _) = PageQuery.use(~variables, ());

  switch (simple) {
  | NoData => React.null
  | Error(e) =>
    Js.log(e);
    <p> {React.string("Error")} </p>;
  | Loading => <p> {React.string("Loading...")} </p>
  | Data(data) =>
    switch (data##collections) {
    | [||] =>
      Route.push(NotFound);
      React.null;
    | [|collection|] =>
      switch (collection##citations) {
      | [||] =>
        <Text>
          {React.string("There are no citations in your collection.")}
        </Text>
      | array =>
        array->Belt.Array.map(citation =>
          <Citation
            slug
            key={citation.id |> string_of_int}
            text={citation.text}
            author={citation.author.name}
            date={citation.added->Belt.Option.getWithDefault("")}
            id={citation.id |> string_of_int}
            onEdit={() => onEdit(citation)}
          />
        )
        |> React.array
      }
    | _ => React.string("Multiple collections exist under the same name")
    }
  };
};
