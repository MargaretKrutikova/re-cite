open DesignSystem;

[@react.component]
let make = (~onAddClick) => {
  <header
    className=Css.(
      style([
        height(`custom(16) |> Styles.space),
        borderBottom(px(2), `solid, `Primary |> Styles.color),
      ])
    )>
    <Container
      className=Css.(
        style([
          display(`flex),
          justifyContent(`spaceBetween),
          alignItems(`center),
          width(pct(100.0)),
          height(pct(100.0)),
        ])
      )>
      <div
        className=Css.(
          style([textTransform(`uppercase), ...Styles.font(`md)])
        )>
        {React.string("Re-cite")}
      </div>
      <Button variant=`Primary onClick=onAddClick>
        {React.string("Add")}
      </Button>
    </Container>
  </header>;
};
