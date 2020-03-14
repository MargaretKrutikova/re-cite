open DesignSystem;
open Types;

module Classes = {
  open Css;

  let bigQuote = () =>
    style([
      borderLeft(`xxs |> Styles.space, `solid, `Primary |> Styles.useColor),
      marginBottom(`xl |> Styles.space),
      paddingLeft(`lg |> Styles.space),
      marginTop(`lg |> Styles.space),
      media(
        Breakpoint.up(`sm),
        [
          marginBottom(`xxl |> Styles.space),
          paddingLeft(`xl |> Styles.space),
        ],
      ),
    ]);
  let citation = () =>
    style([color(`SecondaryText |> Styles.useColor), ...Styles.font(`md)]);
};

[@react.component]
let make = (~citation) => {
  <div className={Classes.bigQuote()}>
    <Heading level=`h2> {React.string(citation.text)} </Heading>
    <div className={Classes.citation()}>
      {React.string(citation.author.name)}
    </div>
  </div>;
};
