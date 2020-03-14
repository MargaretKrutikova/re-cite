let str = React.string;

module PageQuery = ReasonApolloHooks.Query.Make(Queries.GetRandomCitation);

[@react.component]
let make = (~slug) => {
  let variables = Queries.GetRandomCitation.make(~slug, ())##variables;
  let (simple, _) = PageQuery.use(~variables, ());

  switch (simple) {
  | NoData => React.null
  | Error(e) =>
    Js.log(e);
    <p> {str("Error")} </p>;
  | Loading => <p> {str("Loading...")} </p>
  | Data(data) =>
    switch (data##get_random_citation_by_slug) {
    | [||] => <Text> {str("No citation found!")} </Text>
    | [|citation|] => <CitationBig citation />
    | _ => str("Multiple citations exist under the same id")
    }
  };
};
