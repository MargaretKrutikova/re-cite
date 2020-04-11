open Types;

module PageQuery = ReasonApolloHooks.Query.Make(Queries.GetCitations);

module PageQuery2 = ReasonApolloHooks.Query.Make(Queries.GetCitationsTest);

[@react.component]
let make = (~slug, ~onEdit) => {
  let variables = Queries.GetCitations.makeVariables(~slug, ());
  let (simple, _) = PageQuery.use(~variables, ());

  let variables2 =
    Queries.GetCitationsTest.makeVariables(~slug, ~loggedInUserId="ASD", ());

  let (simple2, _) = PageQuery2.use(~variables=variables2, ());

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
          <CitationListItem
            slug
            key={citation##id |> string_of_int}
            text={citation##text}
            author={citation##author##name}
            date={citation##added |> Obj.magic}
            id={citation##id |> string_of_int}
            onEdit={() => onEdit(citation)}
          />
        )
        |> React.array
      }
    | _ => React.string("Multiple collections exist under the same name")
    }
  };
};
