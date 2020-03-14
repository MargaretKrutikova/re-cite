open DesignSystem;
open Types;

module Classes = {
  open Css;

  let citationText =
    style([
      lineHeight(`abs(1.4)),
      unsafe("wordBreak", "break-word"),
      whiteSpace(`preWrap),
    ]);

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
    <Heading level=`h2 className=Classes.citationText>
      {React.string(citation.text)}
    </Heading>
    <div className={Classes.citation()}>
      {React.string(citation.author.name)}
    </div>
  </div>;
};
