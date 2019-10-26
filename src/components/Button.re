open DesignSystem;

type variant = [ | `Primary | `Secondary | `Ghost];

type size = [ | `Small | `Medium];

module Classes = {
  open Css;

  let variantStyles = variant => {
    let (bg_color, text_color) =
      switch (variant) {
      | `Primary => (`Primary |> Styles.color, `hex("fff"))
      | `Ghost => (`transparent, `PrimaryText |> Styles.color)
      | `Secondary => (
          `Secondary |> Styles.color,
          `PrimaryText |> Styles.color,
        )
      };

    [backgroundColor(bg_color), color(text_color)];
  };

  let sizeStyles = size => {
    let (padding_v, padding_h, font_css) =
      switch (size) {
      | `Small => (Styles.space(`sm), Styles.space(`xs), Styles.font(`xs))
      | `Medium => (Styles.space(`xs), Styles.space(`sm), Styles.font(`sm))
      };

    [padding2(~h=padding_h, ~v=padding_v), ...font_css];
  };

  let iconSizeStyle = size => {
    let size_css =
      switch (size) {
      | `Small => `lg |> Styles.space
      | `Medium => `xl |> Styles.space
      };

    [height(size_css), width(size_css), flexGrow(0.0), flexShrink(0.0)];
  };

  let commonStyles = (~icon, ~fullWidth) => [
    borderWidth(px(0)),
    icon ? borderRadius(pct(50.0)) : Styles.borderRadius(`base),
    textAlign(`center),
    textTransform(`uppercase),
    letterSpacing(`rem(0.07)),
    textDecoration(`none),
    whiteSpace(`nowrap),
    fontFamily("inherit"),
    display(`flex),
    padding(px(0)),
    alignItems(`center),
    justifyContent(`center),
    fullWidth ? width(pct(100.0)) : width(auto),
    transition(~duration=100, "background-color"),
    disabled([opacity(0.7)]),
  ];

  let iconContainer = style([display(`flex)]);

  let button = (~variant, ~size, ~icon, ~fullWidth) =>
    commonStyles(~icon, ~fullWidth)
    ->List.append(icon ? iconSizeStyle(size) : sizeStyles(size))
    ->List.append(variantStyles(variant))
    |> style;
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
      ~icon=false,
      ~fullWidth=false,
      ~type_=?,
    ) => {
  let styles =
    Css.merge([
      Classes.button(~variant, ~size, ~icon, ~fullWidth),
      className,
    ]);

  <button ?type_ ?onClick ?disabled className=styles>
    {icon ? <span className=Classes.iconContainer> children </span> : children}
  </button>;
};
