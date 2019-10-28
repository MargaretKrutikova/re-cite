open DesignSystem;

type variant = [ | `Primary | `Secondary];

type size = [ | `Medium | `Small];

type gutter = [ | `Medium | `Large];

let toFontSize =
  fun
  | `Medium => `base
  | `Small => `sm;

let toTextColor =
  fun
  | `Primary => `BodyText
  | `Secondary => `SecondaryText;

let toMarginBottom =
  fun
  | `Medium => `lg
  | `Large => `xl;

[@react.component]
let make =
    (
      ~children,
      ~variant=`Primary,
      ~gutter=`Medium,
      ~size as sz=`Medium,
      ~className as cn="",
    ) => {
  let className =
    Css.(
      merge([
        style([
          gutter |> toMarginBottom |> Styles.space |> marginBottom,
          variant |> toTextColor |> Styles.useColor |> color,
          ...sz |> toFontSize |> Styles.font,
        ]),
        cn,
      ])
    );

  <p className> children </p>;
};
