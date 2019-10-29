type theme =
  | Dark
  | Light;

let themeToString =
  fun
  | Dark => "Dark"
  | Light => "Light";

let themeFromString =
  fun
  | "Dark" => Dark
  | "Light" => Light
  | unknownTheme => Js.Exn.raiseError("Unknown theme: " ++ unknownTheme);

let context = React.createContext((Light, () => ignore()));
let useTheme = () => React.useContext(context);

module Provider = {
  let make = React.Context.provider(context);

  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
};
