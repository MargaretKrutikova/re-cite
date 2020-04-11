let getProviderClass = (provider: ReactNetlifyIdentity.provider) =>
  switch (provider) {
  | Google => "providerGoogle"
  | GitHub => "providerGitHub"
  | GitLab => "providerGitLab"
  | Bitbucket => "providerBitbucket"
  };

[@react.component]
let make = (~provider, ~onLogin, ~className="") => {
  let btnClassName =
    Css.merge(["providerButton", getProviderClass(provider), className]);
  <Button
    className=btnClassName onClick={_ => onLogin(provider)} fullWidth=true>
    {React.string(
       "Continue with " ++ ReactNetlifyIdentity.providerToString(provider),
     )}
  </Button>;
};
