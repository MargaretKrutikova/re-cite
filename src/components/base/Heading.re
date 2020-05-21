open DesignSystem;
open Css;

type level = [ | `h1 | `h2 | `h3];

module Classes = {
  let root = level => {
    switch (level) {
    | `h1 =>
      style([
        marginBottom(`sm |> Styles.space),
        fontWeight(`num(500)),
        media(Breakpoint.up(`sm), Styles.font(`xxl)),
        ...Styles.font(`xl),
      ])
    | `h2 =>
      style([
        marginBottom(`md |> Styles.space),
        fontWeight(`normal),
        ...Styles.font(`xl),
      ])
    | `h3 =>
      style([
        marginBottom(`sm |> Styles.space),
        fontWeight(`normal),
        ...Styles.font(`lg),
      ])
    };
  };
};

[@react.component]
let make = (~level=`h1, ~className as cn="", ~gutter=?, ~children, ()) => {
  let gutterCn =
    gutter->Belt.Option.mapWithDefault("", g =>
      style([Css.marginBottom(g |> Styles.space)])
    );
  let className = Css.merge([Classes.root(level), gutterCn, cn]);

  switch (level) {
  | `h1 => <h1 className> children </h1>
  | `h2 => <h2 className> children </h2>
  | `h3 => <h3 className> children </h3>
  };
};
