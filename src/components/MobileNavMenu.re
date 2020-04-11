open DesignSystem;

module Classes = {
  let menuItem = () =>
    Css.(
      style([
        justifyContent(`center),
        textTransform(`uppercase),
        borderBottom(px(1), `solid, `Border |> Styles.useColor),
        lastChild([borderWidth(px(0))]),
        ...Styles.font(`sm),
      ])
    );
  let linkItem = isActive =>
    Css.(
      merge([menuItem(), style([fontWeight(`num(isActive ? 500 : 400))])])
    );
  let link = Css.(style([textDecoration(`none)]));

  let menu = () =>
    Css.(
      style([
        position(`absolute),
        width(pct(100.0)),
        top(px(64)), // header height
        left(px(0)),
        zIndex(1),
        borderBottom(px(1), `solid, `Primary |> Styles.useColor),
      ])
    );

  let menuIcon = () =>
    Css.(
      style([
        marginRight(`xs |> Styles.space),
        color(`Primary |> Styles.useColor),
        flexShrink(0.0),
      ])
    );
};

module Menu = {
  [@react.component]
  let make = (~onClose, ~onLogin, ~slug=?, ~user: User.t, ~onLogout) => {
    let menuRef = ClickOutside.use(_ => onClose());
    let url = ReasonReactRouter.useUrl();
    let isActive = Route.isActive(url);

    let iconClass = Classes.menuIcon();
    let menuItemClass = Classes.menuItem();

    <div className={Classes.menu()} ref={menuRef->ReactDOMRe.Ref.domRef}>
      {!User.isLoggedIn(user)
         ? <Menu.MenuItem
             className={Classes.linkItem(false)}
             onClick={_ => {
               onLogin();
               onClose();
             }}>
             <ReactFeather.LoginIcon className=iconClass />
             {React.string("Login / Sign up")}
           </Menu.MenuItem>
         : React.null}
      {slug
       ->Belt.Option.map(slug =>
           NavMenu.getNavLinks(slug)
           ->Belt.Array.mapWithIndex((ind, {route, mobileText}) =>
               <Menu.MenuItem
                 key={ind |> string_of_int}
                 dense=false
                 className={Classes.linkItem(isActive(route))}
                 onClick={_ => onClose()}>
                 <RouteLink
                   href={Route.toUrl(route)}
                   color=`Secondary
                   className=Classes.link
                   isActive={isActive(route)}>
                   {React.string(mobileText)}
                 </RouteLink>
               </Menu.MenuItem>
             )
         )
       ->Belt.Option.getWithDefault([||])
       ->React.array}
      {switch (user) {
       | User.LoggedInUser({email}) =>
         <>
           <Menu.MenuItem className=menuItemClass>
             <ReactFeather.UserIcon className=iconClass />
             {React.string(email)}
           </Menu.MenuItem>
           <Menu.MenuItem
             className=menuItemClass
             onClick={_ => {
               onLogout();
               onClose();
             }}>
             <ReactFeather.LogoutIcon className=iconClass />
             {React.string("Log out")}
           </Menu.MenuItem>
         </>
       | _ => React.null
       }}
    </div>;
  };
};

[@react.component]
let make = (~slug=?, ~user: User.t, ~onLogout, ~onLogin) => {
  let (menuIsOpen, setMenuIsOpen) = React.useState(_ => false);
  let toggle = _ => setMenuIsOpen(open_ => !open_);

  let hasMenuItems = user |> User.isLoggedIn || Belt.Option.isSome(slug);

  hasMenuItems
    ? <>
        <Button
          icon=true
          variant=`Text
          color=`Default
          onClick=toggle
          className=Utils.Display.hideDesktop>
          {menuIsOpen ? <ReactFeather.CloseIcon /> : <ReactFeather.MenuIcon />}
        </Button>
        {menuIsOpen
           ? <Menu ?slug onClose=toggle onLogin onLogout user /> : React.null}
      </>
    : React.null;
};
