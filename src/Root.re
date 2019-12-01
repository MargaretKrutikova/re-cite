open Css;
open Dom.Storage2;
open ThemeContext;
open DesignSystem;

let themeStorageKey = "theme";

[@react.component]
let make = () => {
  let savedTheme = localStorage->getItem(themeStorageKey);
  let (theme, setTheme) =
    React.useState(() =>
      savedTheme->Belt.Option.mapWithDefault(
        ThemeContext.Light,
        themeFromString,
      )
    );

  let toggleTheme = () => {
    setTheme(current => {
      let newTheme =
        switch (current) {
        | Light => Dark
        | Dark => Light
        };

      localStorage->setItem(themeStorageKey, newTheme |> themeToString);
      newTheme;
    });
  };

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

  <ThemeContext.Provider value=(theme, toggleTheme)>
    <Page />
    <ReactToastify.ToastContainer
      transition=ReactToastify.flip
      closeButton=false
      autoClose=900
      hideProgressBar=true
      position="bottom-right"
      toastClassName=toastStyles
      className={style([
        textAlign(center),
        media(Breakpoint.up(`sm), [width(auto) |> important]),
      ])}
    />
  </ThemeContext.Provider>;
};
