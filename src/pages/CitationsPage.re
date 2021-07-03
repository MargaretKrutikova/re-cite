open Queries;
open ApolloHooks;

let perPage = 20;

[@react.component]
let make = (~slug, ~onEdit) => {
  let variables =
    GetCitations.make(~slug, ~offset=0, ~limit=perPage, ())##variables;
  let (_, full) =
    useQuery(
      GetCitations.definition,
      ~variables,
      ~notifyOnNetworkStatusChange=true,
    );

  let fetchMore = offset => {
    let variables =
      GetCitations.make(~slug, ~offset, ~limit=perPage, ())##variables;

    full.fetchMore(
      ~variables,
      ~updateQuery=[%bs.raw
        {|
          function(prevResult, { fetchMoreResult, ...rest }) {
            if (!fetchMoreResult || !prevResult) return prevResult;

            const prevCollection = prevResult.collections[0];

            const newCitations = fetchMoreResult.collections[0].citations;
            const combinedCitations = [...prevCollection.citations, ...newCitations];

            const newCollection = { ...prevCollection, citations: combinedCitations };
            const collections = [...fetchMoreResult.collections];
            collections[0] = newCollection;

            return { ...fetchMoreResult, collections };
          }
        |}
      ],
      (),
    );
  };

  switch (full) {
  | {loading: true, data: None} => <p> {React.string("Loading...")} </p>
  | {data: Some(data)} =>
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
      | citations =>
        <CitationsList
          citations
          slug
          onEdit
          fetchMore={() => {
            let isFetchingMore =
              full.networkStatus == ApolloHooksTypes.FetchMore;
            if (!isFetchingMore) {
              fetchMore(citations |> Belt.Array.length) |> ignore;
            };
          }}
        />
      }
    | _ => React.string("Multiple collections exist under the same name")
    }
  | {error: Some(e)} =>
    Js.log(e);
    <p> {React.string("Error")} </p>;
  | {error: None, data: None, loading: false} =>
    <p> {React.string("Not asked")} </p>
  };
};
