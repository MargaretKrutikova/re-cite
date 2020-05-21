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

type apiStatus =
  | NotAsked
  | InProgress
  | Error(string)
  | Success;

type state = {
  shouldShowLoginSidebar: bool,
  logoutStatus: apiStatus,
};

let initState = {shouldShowLoginSidebar: false, logoutStatus: NotAsked};

type action =
  | RequestLogout
  | LogoutFailed(string)
  | LogoutSuccess
  | ToggleLoginSidebarVisibility;

let reducer = (state, action) => {
  switch (action) {
  | RequestLogout => {...state, logoutStatus: InProgress}
  | LogoutFailed(error) => {...state, logoutStatus: Error(error)}
  | LogoutSuccess => {...state, logoutStatus: Success}
  | ToggleLoginSidebarVisibility => {
      ...state,
      shouldShowLoginSidebar: !state.shouldShowLoginSidebar,
    }
  };
};

module CollectionHeader = {
  [@react.component]
  let make = (~onLogout, ~onLogin, ~data: HeaderModel.collectionHeaderData) => {
    let identity = User.useIdentityContext();
    let user = User.make(identity);
    <>
      <DesktopNavMenu user onLogout headerType={Collection(data)} />
      <MobileNavMenu user onLogin onLogout headerType={Collection(data)} />
      {!User.isLoggedIn(user)
         ? <Button
             className={Css.merge([
               Utils.Display.hideMobile,
               Classes.loginButton,
             ])}
             variant=`Outlined
             color=`Primary
             onClick={_ => onLogin()}>
             {React.string("Log in")}
           </Button>
         : React.null}
      <Button
        className=Classes.addButton
        disabled={!data.canAdd}
        variant=`Contained
        color=`Primary
        onClick={_ => data.onAdd()}>
        {React.string("Add")}
      </Button>
    </>;
  };
};

module DefaultHeader = {
  [@react.component]
  let make = (~onLogout: unit => unit, ~onLogin: unit => unit) => {
    let identity = User.useIdentityContext();
    let user = User.make(identity);
    <>
      <DesktopNavMenu user onLogout headerType=Default />
      {!User.isLoggedIn(user)
         ? <Button variant=`Outlined color=`Primary onClick={_ => onLogin()}>
             {React.string("Log in")}
           </Button>
         : <MobileNavMenu user onLogin onLogout headerType=Default />}
    </>;
  };
};

type renderMenu =
  (~onLogin: unit => unit, ~onLogout: unit => unit) => React.element;

[@react.component]
let make = (~type_: HeaderModel.t) => {
  let (state, dispatch) = React.useReducer(reducer, initState);

  let identity = User.useIdentityContext();

  let handleLogout = _ => {
    dispatch(RequestLogout);
    identity.logoutUser()
    |> Js.Promise.then_(_ => {
         dispatch(LogoutSuccess);
         ReactToastify.toast("You are logged out!") |> Js.Promise.resolve;
       })
    |> Js.Promise.catch(error =>
         Utils.promiseErrorToJsObj(error)##message->LogoutFailed
         |> dispatch
         |> Js.Promise.resolve
       )
    |> ignore;
  };

  let toggleLoginSidebar = () => dispatch(ToggleLoginSidebarVisibility);

  <header className={Classes.root()}>
    <Sidebar show={state.shouldShowLoginSidebar} onClose=toggleLoginSidebar>
      <LoginForm />
    </Sidebar>
    <Container className=Classes.container>
      <Logo />
      <ThemeSwitch className=Classes.themeSwitch />
      {switch (type_) {
       | Collection(data) =>
         <CollectionHeader
           data
           onLogin=toggleLoginSidebar
           onLogout=handleLogout
         />
       | Default =>
         <DefaultHeader onLogin=toggleLoginSidebar onLogout=handleLogout />
       }}
    </Container>
  </header>;
};
