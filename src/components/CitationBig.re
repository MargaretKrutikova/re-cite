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
      position(`relative),
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

  let date = () =>
    style([
      color(`SecondaryText |> Styles.useColor),
      ...Styles.font(`base),
    ]);

  let menu = style([position(`absolute), top(px(0)), right(px(0))]);
};

[@react.component]
let make = (~citation: Types.citation, ~slug, ~onEdit, ~className="") => {
  <div className={Css.merge([Classes.bigQuote(), className])}>
    <div className=Classes.menu>
      <CitationMenu
        slug
        id={citation.id |> string_of_int}
        onEdit={() => onEdit(citation)}
      />
    </div>
    <Heading level=`h2 className=Classes.citationText>
      {React.string(citation.text)}
    </Heading>
    <Flex justify=`spaceBetween align=`center>
      <div className={Classes.citation()}>
        {React.string(citation.author.name)}
      </div>
      <Flex align=`center>
        <div className={Classes.date()}>
          {React.string(citation.added |> ApiDate.toDisplayString)}
        </div>
        <UpvoteButton
          size=`Large
          upvoteCount={citation.numberOfUpvotes}
          upvoteUserIds={citation.upvoteUserIds}
          citationId={citation.id}
        />
      </Flex>
    </Flex>
  </div>;
};
