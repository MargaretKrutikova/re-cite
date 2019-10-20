[%bs.raw {|require("./reset.css")|}];

let client = GraphqlClient.makeApolloClient();

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client>
    <ReasonApolloHooks.ApolloProvider client>
      <Root />
    </ReasonApolloHooks.ApolloProvider>
  </ReasonApollo.Provider>,
  "root",
);
