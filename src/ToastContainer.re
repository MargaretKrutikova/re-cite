open Css;
open DesignSystem;

[@react.component]
let make = () => {
  let toastStyles =
    style([
      Styles.borderRadius(`base) |> important,
      `xxl |> Styles.space |> minHeight |> important,
      backgroundColor(`Primary |> Styles.useColor) |> important,
      color(Colors.White.main) |> important,
      textAlign(center),
      fontWeight(`num(300)),
      padding2(~v=`xs |> Styles.space, ~h=`lg |> Styles.space) |> important,
      ...Styles.font(`base)->Belt.List.map(rule => rule |> important),
    ]);

  let showAnimate =
    keyframes([(0, [opacity(0.0)]), (100, [opacity(1.0)])]);
  let hideAnimate =
    keyframes([(0, [opacity(1.0)]), (100, [opacity(0.0)])]);

  <ReactToastify.ToastContainer
    transition={ReactToastify.cssTransition({
      "enter": Css.style([animation(showAnimate)]),
      "exit": Css.style([animation(hideAnimate)]),
      "duration": 300,
    })}
    closeButton=false
    autoClose=1000
    hideProgressBar=true
    position="bottom-right"
    toastClassName=toastStyles
    className={style([
      textAlign(center),
      media(Breakpoint.up(`sm), [width(auto) |> important]),
    ])}
  />;
};
