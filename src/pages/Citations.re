open DesignSystem;
open Types;

module Classes = {
  let citation =
    Css.(
      style([
        marginBottom(`lg |> Styles.space),
        borderBottom(px(1), `solid, `hex("dcdcdc")),
        paddingBottom(`md |> Styles.space),
      ])
    );
};

module CitationsQuery = ReasonApolloHooks.Query.Make(Queries.GetCollection);

[@react.component]
let make = (~citations) => {
  switch (citations) {
  | [||] =>
    <div>
      {React.string(
         {j|The list is empty! Start by adding something funny 🙂|j},
       )}
    </div>
  | array =>
    array->Belt.Array.map(citation =>
      <Citation
        key={citation.id |> string_of_int}
        text={citation.text}
        author={citation.author.name}
        date={citation.added->Belt.Option.getWithDefault("")}
        className=Classes.citation
      />
    )
    |> React.array
  };
};
