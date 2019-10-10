open DesignSystem;

let str = React.string;

[@react.component]
let make = (~text, ~author, ~date, ~clr: string, ~className=?) => {
  <div ?className>
    <div
      className=Css.(
        style([
          marginBottom(`Layout(`xxs) |> Styles.space),
          fontWeight(`light),
          ...Styles.font(`md),
        ])
      )>
      <span> {str(text)} </span>
    </div>
    <div
      className=Css.(
        style([
          display(`flex),
          justifyContent(`spaceBetween),
          alignItems(`flexEnd),
        ])
      )>
      <span
        className=Css.(style([fontWeight(`semiBold), ...Styles.font(`sm)]))>
        {str("-" ++ author)}
      </span>
      <span className=Css.(style(Styles.font(`sm)))> {str(date)} </span>
    </div>
  </div>;
};
