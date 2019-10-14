open DesignSystem;

module Classes = {
  open Css;

  let root = style([display(`flex), flexDirection(column)]);

  let header =
    style([
      marginBottom(`Layout(`xs) |> Styles.space),
      fontWeight(`light),
      ...Styles.font(`md),
    ]);

  let gutter = style([marginBottom(`Layout(`sm) |> Styles.space)]);
};

let getInputValue = (e): string => ReactEvent.Form.target(e)##value;

[@react.component]
let make = () => {
  let (date, setDate) =
    React.useState(() => Js.Date.make() |> Utils.toInputDateFormat);

  <form className=Classes.root>
    <div className=Classes.header>
      {React.string("Someone said something cool?")}
    </div>
    <TextField label="Citation" placeholder="What was it?" multiline=true />
    <TextField label="Author" placeholder="Who was it?" />
    <TextField
      value=date
      onChange={e => setDate(_ => e |> getInputValue)}
      label="Date"
      type_="date"
      placeholder="When was it?"
      className=Classes.gutter
    />
    <Button fullWidth=true variant=`Primary type_="submit">
      {React.string("Save citation")}
    </Button>
  </form>;
};
