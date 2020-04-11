[%bs.raw {|require("./assets/reset.css")|}];
[%bs.raw {|require("./assets/login-provider.css")|}];
[%bs.raw {|require("react-toastify/dist/ReactToastify.css")|}];

let client = GraphqlClient.makeApolloClient();

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client>
    <ReasonApolloHooks.ApolloProvider client>
      <Utils.MockReactNetlifyIdentity.Provider
        value={
          ...Utils.MockReactNetlifyIdentity.mockContextValue,
          url: "https://recite.netlify.com/.netlify/identity",
        }>
        <Root />
      </Utils.MockReactNetlifyIdentity.Provider>
    </ReasonApolloHooks.ApolloProvider>
  </ReasonApollo.Provider>,
  "root",
);
