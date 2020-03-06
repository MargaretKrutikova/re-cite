open DesignSystem;

module Classes = {
  open Css;

  let card = () =>
    style([
      backgroundColor(`CardBg |> Styles.useColor),
      marginBottom(`md |> Styles.space),
      padding2(~v=`md |> Styles.space, ~h=`md |> Styles.space),
      position(`relative),
      media(
        Breakpoint.up(`sm),
        [padding2(~v=`lg |> Styles.space, ~h=`lg |> Styles.space)],
      ),
      boxShadow(
        Shadow.box(~x=px(0), ~y=px(2), ~blur=px(5), Styles.useBoxShadow()),
      ),
      Styles.borderRadius(`base),
    ]);
};

[@react.component]
let make = (~children) => {
  <div className={Classes.card()}> children </div>;
};
