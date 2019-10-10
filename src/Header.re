open DesignSystem;

[@react.component]
let make = () => {
  <header
    className=Css.(
      style([
        height(`Custom(14) |> Styles.space),
        borderBottom(`px(2), `solid, `Secondary |> Styles.color),
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
          style([textTransform(`uppercase), ...`md |> Styles.font])
        )>
        {React.string("Re-cite")}
      </div>
      <Button variant=`Secondary> {React.string("Log in")} </Button>
    </Container>
  </header>;
};
