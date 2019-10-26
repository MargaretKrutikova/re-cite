type theme =
  | Dark
  | Light;

let context = React.createContext((Light, () => ignore()));
let useTheme = () => React.useContext(context);

module Provider = {
  let make = React.Context.provider(context);

  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
};
