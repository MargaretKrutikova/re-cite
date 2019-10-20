open DesignSystem;

type variant = [ | `Primary | `Secondary];

type size = [ | `Small | `Medium];

module Classes = {
  open Css;

  let variantStyles = variant => {
    let (bg_color, text_color) =
      switch (variant) {
      | `Primary => (`Primary |> Theme.color, `BodyText |> Theme.color)
      | `Secondary => (`Secondary |> Theme.color, "fff")
      };

    [backgroundColor(`hex(bg_color)), color(`hex(text_color))];
  };

  let sizeStyles = size => {
    let (height_css, padding_css, font_css) =
      switch (size) {
      | `Small => (Styles.space(`lg), Styles.space(`xs), Styles.font(`xs))
      | `Medium => (
          Styles.space(`xxl),
          Styles.space(`sm),
          Styles.font(`sm),
        )
      };

    [padding2(~h=padding_css, ~v=px(0)), height(height_css), ...font_css];
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
    icon ? borderRadius(pct(50.0)) : borderRadius(px(0)),
    textAlign(`center),
    textTransform(`uppercase),
    textDecoration(`none),
    whiteSpace(`nowrap),
    fontFamily("inherit"),
    fontWeight(`medium),
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
