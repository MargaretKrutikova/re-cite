open DesignSystem;

module Classes = {
  let menuItem = isActive =>
    Css.(
      style([
        fontWeight(`num(isActive ? 500 : 400)),
        justifyContent(`center),
        borderBottom(px(1), `solid, `Border |> Styles.useColor),
        lastChild([borderWidth(px(0))]),
        ...Styles.font(`sm),
      ])
    );

  let link = Css.(style([textDecoration(`none)]));
};

module MenuItem = {
  [@react.component]
  let make = (~route, ~toggle, ~children) => {
    let url = ReasonReactRouter.useUrl();
    let isActive = Route.isActive(url, route);

    <Menu.MenuItem
      className={Classes.menuItem(isActive)} onClick={_ => toggle()}>
      <RouteLink
        isActive
        color=`Secondary
        href={Route.toUrl(route)}
        className=Classes.link>
        children
      </RouteLink>
    </Menu.MenuItem>;
  };
};

[@react.component]
let make = (~slug) => {
  <Flex className=Utils.Display.hideMobile>
    <Menu
      align=`Right
      renderTrigger={(toggle, menuIsOpen) =>
        <Button icon=true variant=`Text color=`Default onClick=toggle>
          {menuIsOpen ? <ReactFeather.CloseIcon /> : <ReactFeather.MenuIcon />}
        </Button>
      }
      renderOptions={toggle =>
        NavMenu.getNavLinks(slug)
        ->Belt.Array.mapWithIndex((index, {route, desktopText}) =>
            <MenuItem toggle route key={index |> string_of_int}>
              {React.string(desktopText)}
            </MenuItem>
          )
        ->React.array
      }
    />
  </Flex>;
};
