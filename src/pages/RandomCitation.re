open ApolloHooks;

let str = React.string;

module Classes = {
  let refreshButton = Css.(style([marginLeft(`auto)]));
};

[@react.component]
let make = (~slug, ~onEdit) => {
  let variables = Queries.GetRandomCitation.make(~slug, ())##variables;
  let (simple, full) =
    useQuery(Queries.GetRandomCitation.definition, ~variables);

  switch (simple) {
  | NoData => React.null
  | Error(e) =>
    Js.log(e);
    <p> {str("Error")} </p>;
  | Loading => <p> {str("Loading...")} </p>
  | Data(data) =>
    switch (data##get_random_citation_by_slug) {
    | [||] => <Text> {str("No citation found!")} </Text>
    | [|citation|] =>
      <>
        <CitationBig slug onEdit citation={Queries.toCitation(citation)} />
        <Button
          size=`Large
          className=Classes.refreshButton
          color=`Primary
          icon=true
          variant=`Contained
          onClick={_ => full.refetch(~variables, ()) |> ignore}>
          <ReactFeather.RefreshIcon />
        </Button>
      </>
    | _ => str("Multiple citations exist under the same id")
    }
  };
};
