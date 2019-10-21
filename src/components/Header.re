open DesignSystem;

module Classes = {
  let container =
    Css.(
      style([
        display(`flex),
        justifyContent(`spaceBetween),
        alignItems(`center),
        width(pct(100.0)),
        height(pct(100.0)),
      ])
    );
  let root =
    Css.(
      style([
        height(`custom(16) |> Styles.space),
        borderBottom(px(2), `solid, `Primary |> Styles.color),
        backgroundColor(`HeaderBg |> Styles.color),
      ])
    );
  let logo = Css.(style([fontWeight(`num(500)), ...Styles.font(`lg)]));
};

module Collection = {
  [@react.component]
  let make = (~onAddClick, ~canAdd) => {
    <header className=Classes.root>
      <Container className=Classes.container>
        <div className=Classes.logo> {React.string("ReCite.")} </div>
        <Button disabled={!canAdd} variant=`Primary onClick=onAddClick>
          {React.string("Add")}
        </Button>
      </Container>
    </header>;
  };
};

[@react.component]
let make = () => {
  <header className=Classes.root>
    <Container className=Classes.container>
      <div className=Classes.logo> {React.string("ReCite.")} </div>
    </Container>
  </header>;
};
