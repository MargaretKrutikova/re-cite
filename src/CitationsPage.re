open DesignSystem;

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

module CitationsQuery = ReasonApolloHooks.Query.Make(Queries.GetAllCitations);

[@react.component]
let make = () => {
  let variables =
    Queries.GetAllCitations.make(~collectionName="test-citations", ())##variables;

  let (simple, _full) = CitationsQuery.use(~variables, ());

  switch (simple) {
  | Loading => <p> {React.string("Loading...")} </p>
  | Data(data) =>
    data##citations
    ->Belt.Array.map(citation =>
        <Citation
          key={citation.id |> string_of_int}
          text={citation.text}
          author={citation.author.name}
          date={citation.added->Belt.Option.getWithDefault("")}
          className=Classes.citation
        />
      )
    |> React.array
  | NoData
  | Error(_) => <p> {React.string("Error")} </p>
  };
};

/* <Citation
     text={j|Någon annan får granska det. Det är inte mitt jobb att granska min egen kod!|j}
     author="Erik T"
     date="2019-05-10"
     className=Classes.citation
   />
   <Citation
     text={j|Vi behöver inte vara så konstruktiva.|j}
     author="Erik T"
     className=Classes.citation
     date="2019-05-10"
   />
   <Citation
     text={j|Jag skulle kunna, om jag vill, definiera varje cell som en person. För att det är en individ.|j}
     author="Erik T"
     date="2019-05-10"
     className=Classes.citation
   /> */
