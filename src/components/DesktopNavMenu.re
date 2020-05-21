open DesignSystem;

module Classes = {
  let menuItem = () =>
    Css.(
      style([
        justifyContent(`flexStart),
        borderBottom(px(1), `solid, `Border |> Styles.useColor),
        lastChild([borderWidth(px(0))]),
        maxWidth(px(250)),
        ...Styles.font(`sm),
      ])
    );
  let userName =
    Css.(
      style([
        textOverflow(`ellipsis),
        overflow(`hidden),
        whiteSpace(`nowrap),
        display(`inlineBlock),
      ])
    );
  let linkItem = isActive =>
    Css.(
      merge([menuItem(), style([fontWeight(`num(isActive ? 500 : 400))])])
    );

  let link = Css.(style([textDecoration(`none), width(pct(100.0))]));
  let menuIcon = () =>
    Css.(
      style([
        marginRight(`xs |> Styles.space),
        color(`Secondary |> Styles.useColor),
        flexShrink(0.0),
        width(Styles.space(`custom(5))),
      ])
    );

  let userIcon = () =>
    Css.(merge([menuIcon(), style([color(`Primary |> Styles.useColor)])]));
};

module LinkMenuItem = {
  [@react.component]
  let make = (~route, ~toggle, ~children) => {
    let url = ReasonReactRouter.useUrl();
    let isActive = Route.isActive(url, route);

    <Menu.MenuItem
      className={Classes.linkItem(isActive)} onClick={_ => toggle()}>
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

let buildCollectionMenuItems =
    (
      ~menuItemClass,
      ~menuIconClass,
      ~toggle,
      ~data: HeaderModel.collectionHeaderData,
    ) =>
  NavMenu.getNavLinks(data.slug)
  ->Belt.Array.mapWithIndex((index, {route, desktopText}) =>
      <LinkMenuItem toggle route key={index |> string_of_int}>
        {React.string(desktopText)}
      </LinkMenuItem>
    )
  ->Belt.Array.concat([|
      <Menu.MenuItem
        className=menuItemClass
        key="Settings"
        onClick={_ => {
          data.onEditSettings();
          toggle();
        }}>
        <ReactFeather.SettingsIcon className=menuIconClass />
        {React.string("Settings")}
      </Menu.MenuItem>,
    |]);

[@react.component]
let make = (~user: User.t, ~onLogout, ~headerType: HeaderModel.t) => {
  let hasMenuItems =
    user |> User.isLoggedIn || HeaderModel.isCollection(headerType);

  let menuItemClass = Classes.menuItem();
  let menuIconClass = Classes.menuIcon();
  let userIconClass = Classes.userIcon();

  hasMenuItems
    ? <Flex className=Utils.Display.hideMobile>
        <Menu
          align=`Right
          renderTrigger={(toggle, menuIsOpen) =>
            <Button icon=true variant=`Text color=`Default onClick=toggle>
              {menuIsOpen
                 ? <ReactFeather.CloseIcon /> : <ReactFeather.MenuIcon />}
            </Button>
          }
          renderOptions={toggle => {
            <>
              {(
                 switch (headerType) {
                 | Collection(data) =>
                   buildCollectionMenuItems(
                     ~menuItemClass,
                     ~menuIconClass,
                     ~toggle,
                     ~data,
                   )
                 | Default => [||]
                 }
               )
               |> React.array}
              {switch (user) {
               | User.LoggedInUser({email}) =>
                 <>
                   <Menu.MenuItem className=menuItemClass>
                     <ReactFeather.UserIcon className=userIconClass />
                     <div className=Classes.userName>
                       {React.string(email)}
                     </div>
                   </Menu.MenuItem>
                   <Menu.MenuItem
                     className=menuItemClass
                     onClick={_ => {
                       onLogout();
                       toggle();
                     }}>
                     <ReactFeather.LogoutIcon className=menuIconClass />
                     {React.string("Log out")}
                   </Menu.MenuItem>
                 </>
               | _ => React.null
               }}
            </>
          }}
        />
      </Flex>
    : React.null;
};
