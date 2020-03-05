open DesignSystem;

type activeSide =
  | Left
  | Right;

module Classes = {
  let root = isActive =>
    Css.(
      style([
        display(`flex),
        border(px(2), solid, `BodyText |> Styles.useColor),
        position(relative),
        Styles.borderRadius(`xl),
        before([
          unsafe("content", "''"),
          position(absolute),
          left(px(0)),
          backgroundColor(`Secondary |> Styles.useColor),
          borderRadius(pct(50.0)),
          width(pct(50.0)),
          height(pct(100.0)),
          "transform" |> Styles.transition(`component),
          transform((isActive == Left ? px(0) : pct(100.0)) |> translateX),
        ]),
      ])
    );

  let button = isActive =>
    Css.(
      style([
        position(relative),
        borderRadius(pct(50.0)),
        cursor(isActive ? `default : `pointer),
      ])
    );
};

module Button = {
  [@react.component]
  let make = (~children, ~isActive) => {
    <div className={Classes.button(isActive)}> children </div>;
  };
};

[@react.component]
let make = (~children, ~activeSide) => {
  <div className={Classes.root(activeSide)}> children </div>;
};
