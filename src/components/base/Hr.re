open DesignSystem;

module Classes = {
  open Css;

  let root = gutter => {
    style([
      borderWidth(px(0)),
      height(px(1)),
      backgroundColor(`Neutral |> Styles.useColor),
      width(pct(100.0)),
      ...gutter->Belt.Option.mapWithDefault([], size =>
           [marginBottom(size |> Styles.space)]
         ),
    ]);
  };
};

[@react.component]
let make = (~gutter=?) => {
  <hr className={Classes.root(gutter)} />;
};
