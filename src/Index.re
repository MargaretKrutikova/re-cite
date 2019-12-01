[%bs.raw {|require("./reset.css")|}];
[%bs.raw {|require("react-toastify/dist/ReactToastify.css")|}];

let client = GraphqlClient.makeApolloClient();

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client>
    <ReasonApolloHooks.ApolloProvider client>
      <Root />
    </ReasonApolloHooks.ApolloProvider>
  </ReasonApollo.Provider>,
  "root",
);
