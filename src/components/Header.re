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

[@react.component]
let make = (~header) => {
  let (state, dispatch) = React.useReducer(reducer, initState);

  let identity = User.useIdentityContext();
  let user = User.make(identity);

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

  let toggleLoginSidebar = _ => dispatch(ToggleLoginSidebarVisibility);

  <header className={Classes.root()}>
    <Sidebar show={state.shouldShowLoginSidebar} onClose=toggleLoginSidebar>
      <LoginForm />
    </Sidebar>
    <Container className=Classes.container>
      <Logo />
      <ThemeSwitch className=Classes.themeSwitch />
      {switch (header) {
       | Default =>
         <>
           <DesktopNavMenu user onLogout=handleLogout />
           {!User.isLoggedIn(user)
              ? <Button
                  variant=`Outlined color=`Primary onClick=toggleLoginSidebar>
                  {React.string("Log in")}
                </Button>
              : <MobileNavMenu
                  user
                  onLogin=toggleLoginSidebar
                  onLogout=handleLogout
                />}
         </>
       | Collection({onAdd, canAdd, slug}) =>
         <>
           <DesktopNavMenu slug user onLogout=handleLogout />
           <MobileNavMenu
             slug
             user
             onLogin=toggleLoginSidebar
             onLogout=handleLogout
           />
           {!User.isLoggedIn(user)
              ? <Button
                  className={Css.merge([
                    Utils.Display.hideMobile,
                    Classes.loginButton,
                  ])}
                  variant=`Outlined
                  color=`Primary
                  onClick={_ => toggleLoginSidebar()}>
                  {React.string("Log in")}
                </Button>
              : React.null}
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
