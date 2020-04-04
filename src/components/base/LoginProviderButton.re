let getProviderClass = (provider: ReactNetlifyIdentity.provider) =>
  switch (provider) {
  | Google => "providerGoogle"
  | GitHub => "providerGitHub"
  | GitLab => "providerGitLab"
  | Bitbucket => "providerBitbucket"
  };

[@react.component]
let make = (~provider, ~className="") => {
  let identity = ReactNetlifyIdentity.useIdentityContextSimple();
  let handleClick = _ => identity.loginProvider(provider);

  let btnClassName =
    Css.merge(["providerButton", getProviderClass(provider), className]);
  <Button className=btnClassName onClick=handleClick fullWidth=true>
    {React.string(
       "Continue with " ++ ReactNetlifyIdentity.providerToString(provider),
     )}
  </Button>;
};
