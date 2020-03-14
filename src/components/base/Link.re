open DesignSystem;

type color = [ | `Primary | `Secondary];

type variant = [ | `Link | `Text];

module Classes = {
  open Css;

  let root = (variant, linkColor) => {
    let variantStyles =
      switch (variant) {
      | `Link => [
          textDecoration(`underline),
          transition(~duration=200, "color"),
          active([opacity(0.5)]),
          ...switch (linkColor) {
             | `Primary => [
                 color(`PrimaryQuiet |> Styles.useColor),
                 hover([color(`Primary |> Styles.useColor)]),
               ]
             | `Secondary => [
                 color(`SecondaryText |> Styles.useColor),
                 hover([color(`BodyText |> Styles.useColor)]),
               ]
             },
        ]

      | `Text => [
          textDecoration(`none),
          unsafe("color", "inherit"),
          hover([unsafe("color", "inherit")]),
        ]
      };

    style([
      display(`inlineFlex),
      alignItems(center),
      cursor(`pointer),
      borderStyle(`none),
      ...variantStyles,
    ]);
  };
};

[@react.component]
let make =
    (
      ~href,
      ~variant=`Link,
      ~color=`Primary,
      ~onClick=ignore,
      ~className="",
      ~newTab=false,
      ~children,
    ) => {
  <a
    href
    onClick
    className={Classes.root(variant, color) ++ " " ++ className}
    target={newTab ? "_blank" : "_self"}
    rel="noopener noreferrer">
    children
  </a>;
};
