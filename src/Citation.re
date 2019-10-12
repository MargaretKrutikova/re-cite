open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let citationText =
    style([
      marginBottom(`Layout(`xs) |> Styles.space),
      fontWeight(`light),
      ...Styles.font(`md),
    ]);

  // TODO: create flex container component?
  let infoContainer =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      alignItems(`flexEnd),
    ]);

  let author = style([fontWeight(`semiBold), ...Styles.font(`sm)]);
  let date = style(`sm |> Styles.font);
};

[@react.component]
let make = (~text, ~author, ~date, ~className=?) => {
  <div ?className>
    <div className=Classes.citationText> {str(text)} </div>
    <div className=Classes.infoContainer>
      <span className=Classes.author> {str("-" ++ author)} </span>
      <span className=Classes.date> {str(date)} </span>
    </div>
  </div>;
};
