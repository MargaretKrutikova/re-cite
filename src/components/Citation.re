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

  // TODO: create flex container component?
  let infoContainer =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      alignItems(`flexEnd),
    ]);

  let author =
    style([color(`SecondaryText |> Styles.color), ...Styles.font(`sm)]);

  let date =
    style([color(`SecondaryText |> Styles.color), ...`sm |> Styles.font]);
};

[@react.component]
let make = (~text, ~author, ~date, ~className=?) => {
  <div
    className=Css.(
      style([
        backgroundColor(`CardBg |> Styles.color),
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
            rgba(19, 41, 104, 0.2),
          ),
        ),
        Styles.borderRadius(),
      ])
    )>
    <div className=Classes.citationText> {str(text)} </div>
    <div className=Classes.infoContainer>
      <span className=Classes.author> {str(author)} </span>
      <span className=Classes.date> {str(date)} </span>
    </div>
  </div>;
};
