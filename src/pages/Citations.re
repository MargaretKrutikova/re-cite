open Types;

module CitationsQuery = ReasonApolloHooks.Query.Make(Queries.GetCollection);

[@react.component]
let make = (~citations) => {
  switch (citations) {
  | [||] =>
    <>
      <Text>
        {React.string("There are no citations in your collection.")}
      </Text>
    </>
  | array =>
    array->Belt.Array.map(citation =>
      <Citation
        key={citation.id |> string_of_int}
        text={citation.text}
        author={citation.author.name}
        date={citation.added->Belt.Option.getWithDefault("")}
      />
    )
    |> React.array
  };
};
