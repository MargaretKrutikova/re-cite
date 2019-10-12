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
      padding2(
        ~v=`Layout(`xs) |> Styles.space,
        ~h=`Layout(`sm) |> Styles.space,
      ),
      width(pct(100.0)),
      maxWidth(px(400)),
    ]);

  let header = style([marginBottom(`Layout(`xs) |> Styles.space)]);
  let closeButton = style([marginLeft(`auto)]);
};

module SidebarHeader = {
  [@react.component]
  let make = (~onClose) => {
    <div className=Classes.header>
      <Button className=Classes.closeButton onClick={_ => onClose()} icon=true>
        <ReactFeather.CloseIcon />
      </Button>
    </div>;
  };
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
          <SidebarHeader onClose />
          children
        </aside>
      </>
    : React.null;
};
