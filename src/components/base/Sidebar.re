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
      zIndex(1),
      Styles.animation(`modal, show ? showAnimate : hideAnimate),
      position(`fixed),
      top(px(0)),
      right(px(0)),
      backgroundColor(`BodyBg2 |> Styles.useColor),
      height(pct(100.0)),
      width(pct(100.0)),
      overflowY(auto),
      maxWidth(px(400)),
      unsafe("WebkitOverflowScrolling", "touch"),
      media(Breakpoint.up(`sm), Styles.paddingH(`lg)),
      ...Styles.paddingH(`md),
    ]);

  let header = style(Styles.paddingV(`sm));
  let closeButton = style([marginLeft(`auto)]);
};

module SidebarHeader = {
  [@react.component]
  let make = (~onClose) => {
    <div className=Classes.header>
      <Button
        className=Classes.closeButton
        variant=`Text
        onClick={_ => onClose()}
        icon=true>
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

  let sidebarStyle = Classes.root(show);

  shouldRender
    ? <>
        <Overlay show />
        <aside
          onAnimationEnd
          ref={ref->ReactDOMRe.Ref.domRef}
          className=sidebarStyle>
          <SidebarHeader onClose />
          children
        </aside>
      </>
    : React.null;
};
