open DesignSystem;
type color = [ | `Primary | `Secondary | `Default];

type variant = [ | `Contained | `Text | `Outlined | `None];

type size = [ | `Small | `Medium | `Large];

module Classes = {
  open Css;

  let variantStyles = (variant, color) => {
    let mainColor =
      switch (color) {
      | `Primary => `Primary |> Styles.useColor
      | `Secondary => `Secondary |> Styles.useColor
      | `Default => `BodyText |> Styles.useColor
      };

    let bg_color =
      switch (variant) {
      | `Contained => mainColor
      | _ => `transparent
      };

    let text_color =
      switch (variant) {
      | `None => `BodyText |> Styles.useColor
      | `Contained => Colors.White.main
      | `Outlined => mainColor
      | `Text => mainColor
      };

    let hover_bg =
      switch (variant) {
      | `None => `transparent
      | `Contained => mainColor |> Styles.withOpacity(0.9)
      | `Outlined => mainColor |> Styles.withOpacity(0.2)
      | `Text => mainColor |> Styles.withOpacity(0.2)
      };

    let border_color =
      switch (variant) {
      | `Outlined => Some(mainColor)
      | _ => None
      };

    let borderStyle =
      Belt.Option.mapWithDefault(border_color, [], color =>
        [border(px(1), `solid, color)]
      );
    [
      backgroundColor(bg_color),
      Css.color(text_color),
      selector(":hover:enabled", [backgroundColor(hover_bg)]),
      ...borderStyle,
    ];
  };

  let sizeStyles = size => {
    let (padding_v, padding_h, font_css) =
      switch (size) {
      | `Small => (Styles.space(`xxs), Styles.space(`xs), Styles.font(`xs))
      | `Medium => (Styles.space(`xs), Styles.space(`sm), Styles.font(`sm))
      | `Large => (Styles.space(`sm), Styles.space(`md), Styles.font(`md))
      };

    [padding2(~h=padding_h, ~v=padding_v), ...font_css];
  };

  let iconSizeStyle = size => {
    let size_css =
      switch (size) {
      | `Small => `lg |> Styles.space
      | `Medium => `xl |> Styles.space
      | `Large => `custom(12) |> Styles.space
      };

    [height(size_css), width(size_css), flexGrow(0.0), flexShrink(0.0)];
  };

  let commonStyles = (~icon, ~fullWidth, ~gutter) => [
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
    Styles.transition(`component, "all"),
    disabled([
      backgroundColor(`Disabled |> Styles.useColor),
      cursor(`notAllowed),
    ]),
    ...gutter->Belt.Option.mapWithDefault([], size =>
         [marginBottom(size |> Styles.space)]
       ),
  ];

  let iconContainer = style([display(`flex)]);

  let button = (~variant, ~color, ~size, ~icon, ~fullWidth, ~gutter) =>
    commonStyles(~icon, ~fullWidth, ~gutter)
    ->List.append(icon ? iconSizeStyle(size) : sizeStyles(size))
    ->List.append(variantStyles(variant, color))
    |> style;
};

[@react.component]
let make =
    (
      ~variant=`Text,
      ~color=`Default,
      ~size=`Medium,
      ~onClick=?,
      ~disabled=?,
      ~children,
      ~className="",
      ~icon=false,
      ~fullWidth=false,
      ~type_=?,
      ~gutter=?,
    ) => {
  let styles =
    Css.merge([
      Classes.button(~variant, ~color, ~size, ~icon, ~fullWidth, ~gutter),
      className,
    ]);

  <button ?type_ ?onClick ?disabled className=styles>
    {icon ? <span className=Classes.iconContainer> children </span> : children}
  </button>;
};
