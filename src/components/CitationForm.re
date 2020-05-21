open DesignSystem;
open Utils;

module Classes = {
  open Css;
  let root = style([display(`flex), flexDirection(column)]);
  let header =
    style([
      marginBottom(`md |> Styles.space),
      fontWeight(`light),
      ...Styles.font(`md),
    ]);

  let gutter = style([marginBottom(`lg |> Styles.space)]);
};

type state = {
  text: string,
  authorName: string,
  date: Js.Date.t,
};

type action =
  | UpdateText(string)
  | UpdateAuthor(string)
  | UpdateDate(string);

let reducer = (state, action) => {
  switch (action) {
  | UpdateText(text) => {...state, text}
  | UpdateAuthor(authorName) => {...state, authorName}
  | UpdateDate(dateStr) =>
    if (dateStr |> DateUtils.isDateStringValid) {
      {...state, date: Js.Date.fromString(dateStr)};
    } else {
      state;
    }
  };
};

let isValid = state => state.text != "" && state.authorName != "";

[@react.component]
let make = (~citation, ~authors, ~onSave, ~isSaving) => {
  let (state, dispatch) = React.useReducer(reducer, citation);

  let displayDate = state.date |> DateUtils.toInputDateTimeFormat;

  <form
    className=Classes.root onSubmit={e => ReactEvent.Form.preventDefault(e)}>
    <div className=Classes.header>
      {React.string("Someone said something cool?")}
    </div>
    <TextField
      label="Citation"
      placeholder="What was it?"
      multiline=true
      value={state.text}
      onChange={e => dispatch(UpdateText(getInputValue(e)))}
    />
    <AuthorPicker
      authors
      authorName={state.authorName}
      onChange={e => dispatch(UpdateAuthor(getInputValue(e)))}
    />
    <TextField
      value=displayDate
      onChange={e => dispatch(UpdateDate(getInputValue(e)))}
      label="Date"
      type_="datetime-local"
      placeholder="When was it?"
      className=Classes.gutter
    />
    <Button
      fullWidth=true
      variant=`Contained
      color=`Primary
      type_="button"
      onClick={_ => onSave(state)}
      disabled={!isValid(state) || isSaving}>
      {React.string("Save citation")}
    </Button>
  </form>;
};
