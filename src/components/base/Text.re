open DesignSystem;

type variant = [ | `Primary | `Secondary | `Error];

type size = [ | `Medium | `Small];

let toFontSize =
  fun
  | `Medium => `base
  | `Small => `sm;

let toTextColor =
  fun
  | `Primary => `BodyText
  | `Secondary => `SecondaryText
  | `Error => `Error;

[@react.component]
let make =
    (
      ~children,
      ~variant=`Primary,
      ~gutter=`lg,
      ~size as sz=`Medium,
      ~className as cn="",
    ) => {
  let className =
    Css.(
      merge([
        style([
          variant |> toTextColor |> Styles.useColor |> color,
          marginBottom(gutter |> Styles.space),
          ...sz |> toFontSize |> Styles.font,
        ]),
        cn,
      ])
    );

  <p className> children </p>;
};
