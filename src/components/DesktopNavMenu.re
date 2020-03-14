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
  let link = Css.(style([textDecoration(`none), fontWeight(`num(500))]));
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

type item = {
  route: Route.t,
  text: string,
};

[@react.component]
let make = (~items, ~className="") => {
  <Flex className>
    {items
     ->Belt.Array.map(({route, text}) =>
         <MenuItem route> {React.string(text)} </MenuItem>
       )
     ->React.array}
  </Flex>;
};
