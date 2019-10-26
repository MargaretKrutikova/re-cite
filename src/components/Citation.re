open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let card = () =>
    style([
      backgroundColor(`CardBg |> Styles.useColor),
      marginBottom(`md |> Styles.space),
      padding2(~v=`md |> Styles.space, ~h=`md |> Styles.space),
      media(
        Breakpoint.up(`sm),
        [padding2(~v=`lg |> Styles.space, ~h=`lg |> Styles.space)],
      ),
      boxShadow(
        Shadow.box(
          ~x=px(0),
          ~y=px(2),
          ~blur=px(5),
          rgba(19, 41, 104, 0.2) // TODO: put in design system
        ),
      ),
      Styles.borderRadius(`base),
    ]);

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
  <div className={Classes.card()}>
    <div className=Classes.citationText> {str(text)} </div>
    <Flex justify=`spaceBetween align=`end_>
      <span className={Classes.secondaryText()}> {str(author)} </span>
      <span className={Classes.secondaryText()}> {str(date)} </span>
    </Flex>
  </div>;
};
