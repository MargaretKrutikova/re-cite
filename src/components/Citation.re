open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let citationText =
    style([
      marginBottom(`sm |> Styles.space),
      unsafe("wordBreak", "break-word"),
      whiteSpace(`preWrap),
      ...Styles.font(`base),
    ]);

  let secondaryText = () =>
    style([color(`SecondaryText |> Styles.useColor), ...Styles.font(`sm)]);
};

[@react.component]
let make = (~text, ~author, ~date) => {
  <Card>
    <div className=Classes.citationText> {str(text)} </div>
    <Flex justify=`spaceBetween align=`end_>
      <span className={Classes.secondaryText()}> {str(author)} </span>
      <span className={Classes.secondaryText()}> {str(date)} </span>
    </Flex>
  </Card>;
};
