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
  let make = (~href, ~children) => {
    <li className=Classes.menuItem>
      <RouteLink color=`Secondary href className=Classes.link>
        children
      </RouteLink>
    </li>;
  };
};

[@react.component]
let make = (~slug) => {
  <Flex>
    <MenuItem href={Route.toUrl(Collection(slug, Citations))}>
      {React.string("All")}
    </MenuItem>
    <MenuItem href={Route.toUrl(Collection(slug, RandomCitation))}>
      {React.string("Random")}
    </MenuItem>
  </Flex>;
};
