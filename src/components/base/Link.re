open DesignSystem;

type variant = [ | `Link | `Text];

module Classes = {
  open Css;

  let root = variant => {
    let variantStyles =
      switch (variant) {
      | `Link => [
          textDecoration(`underline),
          color(`PrimaryQuiet |> Styles.useColor),
          transition(~duration=200, "color"),
          hover([color(`Primary |> Styles.useColor)]),
          active([opacity(0.5)]),
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
      ~onClick=ignore,
      ~className="",
      ~newTab=false,
      ~children,
    ) => {
  <a
    href
    onClick
    className={Classes.root(variant) ++ " " ++ className}
    target={newTab ? "_blank" : "_self"}
    rel="noopener noreferrer">
    children
  </a>;
};
