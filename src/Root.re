open Dom.Storage2;
open ThemeContext;

let themeStorageKey = "theme";

let themeToString =
  fun
  | Dark => "Dark"
  | Light => "Light";

let themeFromString =
  fun
  | "Dark" => Dark
  | "Light" => Light
  | unknownTheme => Js.Exn.raiseError("Unknown theme: " ++ unknownTheme);

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

  <ThemeContext.Provider value=(theme, toggleTheme)>
    <Page />
  </ThemeContext.Provider>;
};
