let str = React.string;

module PageQuery = ReasonApolloHooks.Query.Make(Queries.GetCitationById);

[@react.component]
let make = (~slug, ~id) => {
  let variables = Queries.GetCitationById.make(~slug, ~id, ())##variables;
  let (simple, _) = PageQuery.use(~variables, ());

  switch (simple) {
  | NoData => React.null
  | Error(e) =>
    Js.log(e);
    <p> {str("Error")} </p>;
  | Loading => <p> {str("Loading...")} </p>
  | Data(data) =>
    switch (data##citations) {
    | [||] => <Text> {str("No citation found!")} </Text>
    | [|citation|] => <CitationBig citation />
    | _ => str("Multiple citations exist under the same id")
    }
  };
};
