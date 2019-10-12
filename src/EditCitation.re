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
};

[@react.component]
let make = () => {
  <form className=Classes.root>
    <div className=Classes.header>
      {React.string("Someone said something cool?")}
    </div>
    <TextField label="Citation" placeholder="What was it?" multiline=true />
    <TextField label="Author" placeholder="Who was it?" />
    <TextField label="Date" placeholder="When was it?" />
    <Button fullWidth=true variant=`Primary>
      {React.string("Add citation")}
    </Button>
  </form>;
};
