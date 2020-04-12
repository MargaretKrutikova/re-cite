open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let citationText =
    style([
      marginBottom(`sm |> Styles.space),
      paddingTop(`xs |> Styles.space),
      media(Breakpoint.up(`sm), [paddingTop(px(0))]),
      unsafe("wordBreak", "break-word"),
      whiteSpace(`preWrap),
      ...Styles.font(`base),
    ]);

  let secondaryText = () =>
    style([color(`SecondaryText |> Styles.useColor), ...Styles.font(`sm)]);

  let menu =
    style([
      position(`absolute),
      top(`xxs |> Styles.space),
      right(`xs |> Styles.space),
    ]);
  let card = style([important(paddingRight(px(8)))]);
};

[@react.component]
let make =
    (~text, ~author, ~date, ~slug, ~upvoteCount, ~upvoteUserIds, ~id, ~onEdit) => {
  <Card className=Classes.card>
    <div className=Classes.citationText> {str(text)} </div>
    <Flex justify=`spaceBetween align=`center>
      <span className={Classes.secondaryText()}> {str(author)} </span>
      <Flex align=`center>
        <div className={Classes.secondaryText()}> {str(date)} </div>
        <UpvoteButton upvoteCount upvoteUserIds citationId=id />
      </Flex>
    </Flex>
    <div className=Classes.menu>
      <CitationMenu slug id={id |> string_of_int} onEdit />
    </div>
  </Card>;
};
