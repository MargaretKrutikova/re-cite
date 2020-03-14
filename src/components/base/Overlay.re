open DesignSystem;

module Classes = {
  open Css;

  let showAnimate =
    keyframes([(0, [opacity(0.0)]), (100, [opacity(1.0)])]);
  let hideAnimate =
    keyframes([(0, [opacity(1.0)]), (100, [opacity(0.0)])]);

  let root = show =>
    style([
      zIndex(1),
      Styles.animation(`modal, show ? showAnimate : hideAnimate),
      position(`fixed),
      top(px(0)),
      left(px(0)),
      right(px(0)),
      left(px(0)),
      width(pct(100.0)),
      height(pct(100.0)),
      backgroundColor(`Overlay |> Styles.useColor),
    ]);
};

[@react.component]
let make = (~show) => {
  let (shouldRender, onAnimationEnd) = RenderAnimate.use(~show);

  shouldRender
    ? <div className={Classes.root(show)} onAnimationEnd /> : React.null;
};
