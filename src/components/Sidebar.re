open DesignSystem;

module Classes = {
  open Css;

  let showAnimate =
    keyframes([
      (0, [transform(pct(100.0) |> translateX)]),
      (100, [transform(pct(0.0) |> translateX)]),
    ]);

  let hideAnimate =
    keyframes([
      (0, [transform(pct(0.0) |> translateX)]),
      (100, [transform(pct(100.0) |> translateX)]),
    ]);

  let root = show =>
    style([
      Styles.animation(`Modal, show ? showAnimate : hideAnimate),
      position(`absolute),
      top(px(0)),
      right(px(0)),
      backgroundColor(`BodyBg |> Styles.color),
      height(pct(100.0)),
      padding(px(20)),
      width(pct(100.0)),
      maxWidth(px(400)),
      borderLeft(px(2), `solid, `Secondary |> Styles.color),
    ]);
};

[@react.component]
let make = (~show, ~onClose, ~children) => {
  let ref = ClickOutside.use(_ => onClose());

  let (shouldRender, onAnimationEnd) = RenderAnimate.use(~show);

  shouldRender
    ? <>
        <Overlay show />
        <aside
          onAnimationEnd
          ref={ref->ReactDOMRe.Ref.domRef}
          className={Classes.root(show)}>
          <button onClick={_ => onClose()}> {React.string("x")} </button>
          children
        </aside>
      </>
    : React.null;
};
