open Types;
open Queries;
open ApolloHooks;

[@react.component]
let make = (~slug, ~onEdit) => {
  let variables = GetCitations.make(~slug, ())##variables;
  let (simple, _) = useQuery(GetCitations.definition, ~variables);

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
        array
        ->Belt.Array.map(citationObj => Queries.toCitation(citationObj))
        ->Belt.Array.map(citation =>
            <CitationListItem
              slug
              key={citation.id |> string_of_int}
              text={citation.text}
              author={citation.author.name}
              date={citation.added |> ApiDate.toDisplayString}
              id={citation.id}
              upvoteUserIds={citation.upvoteUserIds}
              upvoteCount={citation.numberOfUpvotes}
              onEdit={() => onEdit(citation)}
            />
          )
        |> React.array
      }
    | _ => React.string("Multiple collections exist under the same name")
    }
  };
};
