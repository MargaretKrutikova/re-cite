open DesignSystem;

module Classes = {
  let container =
    Css.(
      style([
        display(`flex),
        justifyContent(`spaceBetween),
        alignItems(`center),
        width(pct(100.0)),
        height(pct(100.0)),
      ])
    );
  let root = () =>
    Css.(
      style([
        height(`custom(16) |> Styles.space),
        borderBottom(px(1), `solid, `Primary |> Styles.useColor),
        backgroundColor(`BodyBg1 |> Styles.useColor),
      ])
    );
  let logo =
    Css.(
      style([
        fontWeight(`num(500)),
        cursor(`pointer),
        ...Styles.font(`lg),
      ])
    );
  let addButton =
    Css.(
      style([
        marginLeft(`sm |> Styles.space),
        media(Breakpoint.up(`sm), [marginLeft(`md |> Styles.space)]),
      ])
    );

  let loginButton = Css.(style([marginLeft(`sm |> Styles.space)]));
  let themeSwitch =
    Css.(style([marginRight(auto), marginLeft(`sm |> Styles.space)]));
};

module Logo = {
  [@react.component]
  let make = () => {
    <a
      className=Classes.logo
      onClick={RouteLink.handleClick(Route.toUrl(Home))}>
      {React.string("ReCite.")}
    </a>;
  };
};

type collectionHeader = {
  slug: string,
  canAdd: bool,
  onAdd: unit => unit,
};

type header =
  | Default
  | Collection(collectionHeader);

[@react.component]
let make = (~header) => {
  let (showLogin, setShowLogin) = React.useState(() => false);

  let toggleLoginSidebar = () => setShowLogin(show => !show);

  <header className={Classes.root()}>
    <Sidebar show=showLogin onClose={_ => toggleLoginSidebar()}>
      <LoginForm />
    </Sidebar>
    <Container className=Classes.container>
      <Logo />
      <ThemeSwitch className=Classes.themeSwitch />
      {switch (header) {
       | Default => React.null
       | Collection({onAdd, canAdd, slug}) =>
         <>
           <DesktopNavMenu slug />
           <MobileNavMenu slug onLogin=toggleLoginSidebar />
           <Button
             className={Css.merge([
               Utils.Display.hideMobile,
               Classes.loginButton,
             ])}
             variant=`Outlined
             color=`Primary
             onClick={_ => toggleLoginSidebar()}>
             {React.string("Log in")}
           </Button>
           <Button
             className=Classes.addButton
             disabled={!canAdd}
             variant=`Contained
             color=`Primary
             onClick={_ => onAdd()}>
             {React.string("Add")}
           </Button>
         </>
       }}
    </Container>
  </header>;
};
