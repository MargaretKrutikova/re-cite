// let graphqlUrl = "https://re-cite-stage.herokuapp.com/v1/graphql";
let graphqlUrl = "https://sirseszwtdwfowwgxjcc.nhost.run/v1/graphql";

let makeApolloClient = _ => {
  // Create an InMemoryCache
  let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

  // Create an HTTP Link
  let httpLink = ApolloLinks.createHttpLink(~uri=graphqlUrl, ());

  // return apollo client instance
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
};
