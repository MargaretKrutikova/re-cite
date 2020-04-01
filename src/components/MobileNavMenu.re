open DesignSystem;

module Classes = {
  let menuItem = isActive =>
    Css.(
      style([
        fontWeight(`num(isActive ? 500 : 400)),
        justifyContent(`center),
        textTransform(`uppercase),
        borderBottom(px(1), `solid, `Border |> Styles.useColor),
        paddingTop(Styles.space(`sm)),
        paddingBottom(Styles.space(`sm)),
        lastChild([borderWidth(px(0))]),
        ...Styles.font(`sm),
      ])
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
  let make = (~onClose, ~slug) => {
    let menuRef = ClickOutside.use(_ => onClose());
    let url = ReasonReactRouter.useUrl();
    let isActive = route => {
      let activeRoute = url.path |> Route.fromUrl;
      route == activeRoute;
    };

    <div className={Classes.menu()} ref={menuRef->ReactDOMRe.Ref.domRef}>
      <Menu.MenuItem
        className={Classes.menuItem(false)} onClick={_ => onClose()}>
        <ReactFeather.LoginIcon className={Classes.menuIcon()} />
        {React.string("Log in")}
      </Menu.MenuItem>
      {NavMenu.getMenuItems(slug)
       ->Belt.Array.mapWithIndex((ind, {route, mobileText}) =>
           <Menu.MenuItem
             key={ind |> string_of_int}
             dense=false
             className={Classes.menuItem(isActive(route))}
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
       ->React.array}
    </div>;
  };
};

[@react.component]
let make = (~slug) => {
  let (menuIsOpen, setMenuIsOpen) = React.useState(_ => false);
  let toggle = _ => setMenuIsOpen(open_ => !open_);

  <>
    <Button
      icon=true
      variant=`Text
      color=`Default
      onClick=toggle
      className=Utils.Display.hideDesktop>
      {menuIsOpen ? <ReactFeather.CloseIcon /> : <ReactFeather.MenuIcon />}
    </Button>
    {menuIsOpen ? <Menu slug onClose=toggle /> : React.null}
  </>;
};
