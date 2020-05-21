[%bs.raw {|require("./assets/reset.css")|}];
[%bs.raw {|require("./assets/login-provider.css")|}];
[%bs.raw {|require("react-toastify/dist/ReactToastify.css")|}];
[%bs.raw {|require("./assets/overrides.css")|}];

let client = GraphqlClient.makeApolloClient();

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client>
    <ReasonApolloHooks.ApolloProvider client>
      <ReactNetlifyIdentity.IdentityContextProvider
        url="https://recite.netlify.app/">
        <Root />
      </ReactNetlifyIdentity.IdentityContextProvider>
    </ReasonApolloHooks.ApolloProvider>
  </ReasonApollo.Provider>,
  "root",
);
