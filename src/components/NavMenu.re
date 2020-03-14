open DesignSystem;

module Classes = {
  let menuItem =
    Css.(
      style([
        listStyleType(`none),
        margin2(~h=`xs |> Styles.space, ~v=px(0)),
        media(
          Breakpoint.up(`sm),
          [margin2(~h=`sm |> Styles.space, ~v=px(0))],
        ),
        ...Styles.font(`sm),
      ])
    );
  let link =
    Css.(
      style([textDecoration(`none) |> important, fontWeight(`num(500))])
    );
};

module MenuItem = {
  [@react.component]
  let make = (~route, ~children) => {
    let url = ReasonReactRouter.useUrl();
    let isActive = () => {
      let activeRoute = url.path |> Route.fromUrl;
      route == activeRoute;
    };

    <li className=Classes.menuItem>
      <RouteLink
        isActive={isActive()}
        color=`Secondary
        href={Route.toUrl(route)}
        className=Classes.link>
        children
      </RouteLink>
    </li>;
  };
};

[@react.component]
let make = (~slug) => {
  <Flex>
    <MenuItem route={Route.Collection(slug, Citations)}>
      {React.string("All")}
    </MenuItem>
    <MenuItem route={Route.Collection(slug, RandomCitation)}>
      {React.string("Random")}
    </MenuItem>
  </Flex>;
};
