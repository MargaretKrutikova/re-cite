open ApolloHooks;

let str = React.string;

[@react.component]
let make = (~slug, ~id, ~onEdit) => {
  let variables = Queries.GetCitationById.make(~slug, ~id, ())##variables;
  let (simple, _) = useQuery(Queries.GetCitationById.definition, ~variables);

  switch (simple) {
  | NoData => React.null
  | Error(e) =>
    Js.log(e);
    <p> {str("Error")} </p>;
  | Loading => <p> {str("Loading...")} </p>
  | Data(data) =>
    switch (data##citations) {
    | [||] => <Text> {str("No citation found!")} </Text>
    | [|citationObj|] =>
      <CitationBig citation={Queries.toCitation(citationObj)} slug onEdit />
    | _ => str("Multiple citations exist under the same id")
    }
  };
};
