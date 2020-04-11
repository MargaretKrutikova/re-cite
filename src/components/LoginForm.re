open DesignSystem;

module Classes = {
  open Css;
  let root =
    style([display(`flex), flexDirection(column), textAlign(`center)]);
  let header =
    style([
      marginBottom(`md |> Styles.space),
      fontWeight(`light),
      marginBottom(`md |> Styles.space),
      ...Styles.font(`md),
    ]);

  let gutter = style([marginBottom(`md |> Styles.space)]);
};

[@react.component]
let make = () => {
  let identity = User.useIdentityContext();

  <div className=Classes.root>
    <div className=Classes.header> {React.string("Login / Signup")} </div>
    <Text size=`Small variant=`Secondary>
      {React.string(
         "Login to upvote citations and connect to your collections",
       )}
    </Text>
    <div id="providers">
      {identity.settings.providers
       ->Belt.Array.map(provider =>
           <LoginProviderButton
             key={ReactNetlifyIdentity.providerToString(provider)}
             provider
             onLogin={identity.loginProvider}
             className=Classes.gutter
           />
         )
       |> React.array}
    </div>
  </div>;
};
