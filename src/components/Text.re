open DesignSystem;

[@react.component]
let make = (~children, ~className as cn="") => {
  let className =
    Css.(
      merge([
        style([marginBottom(`lg |> Styles.space), ...Styles.font(`base)]),
        cn,
      ])
    );

  <p className> children </p>;
};
