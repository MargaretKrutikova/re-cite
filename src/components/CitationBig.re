open DesignSystem;
open Types;

module Classes = {
  open Css;

  let citationText =
    style([
      lineHeight(`abs(Theme.baseLineHeight)) |> important,
      unsafe("wordBreak", "break-word"),
      whiteSpace(`preWrap),
      media(Breakpoint.down(`md), Styles.font(`lg)),
    ]);

  let bigQuote = () =>
    style([
      borderLeft(`xxs |> Styles.space, `solid, `Primary |> Styles.useColor),
      marginTop(`lg |> Styles.space),
      paddingLeft(`lg |> Styles.space),
      media(
        Breakpoint.up(`sm),
        [
          marginBottom(`lg |> Styles.space),
          paddingLeft(`xl |> Styles.space),
        ],
      ),
    ]);
  let citation = () =>
    style([
      color(`SecondaryText |> Styles.useColor),
      media(Breakpoint.down(`md), [fontSize(px(20))]),
      ...Styles.font(`md),
    ]);
};

[@react.component]
let make = (~citation: Types.citation, ~className="") => {
  let (state, setState) = React.useState(_ => false);
  let toggleActive = _ => setState(s => !s);

  <div className={Css.merge([Classes.bigQuote(), className])}>
    <Heading level=`h2 className=Classes.citationText>
      {React.string(citation.text)}
    </Heading>
    <Flex justify=`spaceBetween align=`center>
      <div className={Classes.citation()}>
        {React.string(citation.author.name)}
      </div>
      <UpvoteButton
        size=`Large
        upvoteCount=45
        isActive=state
        onClick=toggleActive
      />
    </Flex>
  </div>;
};
