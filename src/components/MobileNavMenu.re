open DesignSystem;

module Classes = {
  let menuItem = () =>
    Css.(
      style([
        fontWeight(`num(500)),
        justifyContent(`center),
        textTransform(`uppercase),
        borderBottom(px(1), `solid, `Border |> Styles.useColor),
        lastChild([borderWidth(px(0))]),
        ...Styles.font(`sm),
      ])
    );
  let link = Css.(style([textDecoration(`none)]));
};

[@react.component]
let make = (~slug) => {
  let url = ReasonReactRouter.useUrl();
  let isActive = route => {
    let activeRoute = url.path |> Route.fromUrl;
    route == activeRoute;
  };

  <Menu
    hasOverlay=true
    className=Utils.Display.hideDesktop
    align=`Center
    renderTrigger={toggle =>
      <Button
        icon=true
        variant=`Text
        color=`Default
        onClick=toggle
        className=Utils.Display.hideDesktop>
        <ReactFeather.MenuIcon />
      </Button>
    }
    renderOptions={toggle =>
      <>
        {NavMenu.getMenuItems(slug)
         ->Belt.Array.mapWithIndex((ind, {route, mobileText}) =>
             <Menu.MenuItem
               key={ind |> string_of_int}
               className={Classes.menuItem()}
               onClick=toggle>
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
      </>
    }
  />;
};
