open DesignSystem;

type color = [ | `Primary | `Secondary];

type variant = [ | `Link | `Text];

module Classes = {
  open Css;

  let root = (variant, linkColor, ~isActive) => {
    let variantStyles =
      switch (variant) {
      | `Link => [
          textDecoration(`underline),
          transition(~duration=200, "color"),
          active([opacity(0.5)]),
          ...switch (linkColor) {
             | `Primary => [
                 color(
                   (isActive ? `Primary : `PrimaryQuiet) |> Styles.useColor,
                 ),
                 hover([color(`Primary |> Styles.useColor)]),
               ]
             | `Secondary => [
                 color(
                   (isActive ? `BodyText : `SecondaryText) |> Styles.useColor,
                 ),
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
      ~isActive=false,
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
    className={Css.merge([
      Classes.root(variant, color, ~isActive),
      className,
    ])}
    target={newTab ? "_blank" : "_self"}
    rel="noopener noreferrer">
    children
  </a>;
};
