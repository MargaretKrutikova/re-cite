open DesignSystem;

module Classes = {
  open Css;

  let root = () => {
    style([
      display(`inline),
      cursor(`pointer),
      borderStyle(`none),
      textDecoration(`underline),
      color(`PrimaryQuiet |> Styles.useColor),
      transition(~duration=200, "color"),
      hover([color(`Primary |> Styles.useColor)]),
      active([opacity(0.5)]),
    ]);
  };
};

[@react.component]
let make = (~href, ~onClick=ignore, ~newTab=false, ~children) => {
  <a
    href
    onClick
    className={Classes.root()}
    target={newTab ? "_blank" : "_self"}
    rel="noopener noreferrer">
    children->React.string
  </a>;
};
