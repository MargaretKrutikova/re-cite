open DesignSystem;

module Classes = {
  open Css;
  let root = style([display(`flex), flexDirection(column)]);
  let header =
    style([
      marginBottom(`md |> Styles.space),
      fontWeight(`light),
      textAlign(`center),
      ...Styles.font(`md),
    ]);

  let gutter = style([marginBottom(`lg |> Styles.space)]);
};

[@react.component]
let make = () => {
  <div className=Classes.root>
    <div className=Classes.header> {React.string("Login / Signup")} </div>
    <div id="providers">
      {[|NetlifyProvider.GitHub, NetlifyProvider.Google|]
       ->Belt.Array.map(provider =>
           <LoginProviderButton
             key={ReactNetlifyIdentity.providerToString(provider)}
             provider
             className=""
           />
         )
       |> React.array}
    </div>
  </div>;
};
