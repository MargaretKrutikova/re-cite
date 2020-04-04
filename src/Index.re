[%bs.raw {|require("./reset.css")|}];
[%bs.raw {|require("./login-provider.css")|}];
[%bs.raw {|require("react-toastify/dist/ReactToastify.css")|}];

let client = GraphqlClient.makeApolloClient();

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client>
    <ReasonApolloHooks.ApolloProvider client>
      <ReactNetlifyIdentity.IdentityContextProvider
        url="https://bs-react-netlify-identity.netlify.com/">
        <Root />
      </ReactNetlifyIdentity.IdentityContextProvider>
    </ReasonApolloHooks.ApolloProvider>
  </ReasonApollo.Provider>,
  "root",
);
