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
      position(`fixed),
      top(px(0)),
      right(px(0)),
      backgroundColor(`ModalBg |> Styles.color),
      height(pct(100.0)),
      padding2(~v=`md |> Styles.space, ~h=`lg |> Styles.space),
      width(pct(100.0)),
      overflowY(auto),
      maxWidth(px(400)),
      unsafe("WebkitOverflowScrolling", "touch"),
    ]);

  let header = style([marginBottom(`md |> Styles.space)]);
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
  React.useEffect1(
    () => {
      Styles.toggleBodyScroll(~disableScroll=shouldRender);
      None;
    },
    [|shouldRender|],
  );

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
