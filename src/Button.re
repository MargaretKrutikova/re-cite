open DesignSystem;

type variant = [ | `Primary | `Secondary];

type size = [ | `Small | `Medium];

module Styles = {
  let variantStyles = variant => {
    let (bg_color, text_color) =
      switch (variant) {
      | `Primary => (`Primary |> Theme.color, "fff")
      | `Secondary => (`Secondary |> Theme.color, "000")
      };

    Css.[backgroundColor(`hex(bg_color)), color(`hex(text_color))];
  };

  let sizeStyles = size => {
    let (height_css, padding_css, font_css) =
      switch (size) {
      | `Small => (
          `Component(`xl) |> Styles.space,
          `Component(`sm) |> Styles.space,
          `xs |> Styles.font,
        )
      | `Medium => (
          `Component(`xxl) |> Styles.space,
          `Component(`md) |> Styles.space,
          `sm |> Styles.font,
        )
      };

    Css.[
      padding2(~h=padding_css, ~v=px(0)),
      height(height_css),
      ...font_css,
    ];
  };

  let commonStyles =
    Css.[
      borderWidth(px(0)),
      borderRadius(px(0)),
      textAlign(`center),
      textTransform(`uppercase),
      textDecoration(`none),
      whiteSpace(`nowrap),
      fontFamily("inherit"),
      fontWeight(`medium),
      display(`flex),
      alignItems(`center),
      justifyContent(`center),
      transition(~duration=100, "background-color"),
    ];

  let button = (~variant, ~size) =>
    sizeStyles(size)
    |> List.append(commonStyles)
    |> List.append(variantStyles(variant))
    |> Css.style;
};

[@react.component]
let make =
    (
      ~variant=`Primary,
      ~size=`Medium,
      ~onClick=?,
      ~disabled=?,
      ~children,
      ~className="",
    ) => {
  let styles = Cn.make([Styles.button(~variant, ~size), className]);
  <button ?onClick ?disabled className=styles> children </button>;
};
