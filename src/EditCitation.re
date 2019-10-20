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

module CitationMutation =
  ReasonApolloHooks.Mutation.Make(Mutations.EditCitation);

type state = {
  text: string,
  authorName: string,
  date: string,
};

type action =
  | UpdateText(string)
  | UpdateAuthor(string)
  | UpdateDate(string);

let reducer = (state, action) => {
  switch (action) {
  | UpdateText(text) => {...state, text}
  | UpdateAuthor(authorName) => {...state, authorName}
  | UpdateDate(date) => {...state, date}
  };
};

let getInitialState = citation =>
  citation->Belt.Option.mapWithDefault(
    {text: "", authorName: "", date: Js.Date.make() |> toInputDateFormat},
    ({text, added, author}: Types.citation) =>
    {
      text,
      date: added->Belt.Option.getWithDefault(""),
      authorName: author.name,
    }
  );

let isValid = state =>
  state.text != "" && state.authorName != "" && state.date != "";

[@react.component]
let make =
    (
      ~citation,
      ~authors: array(Types.author),
      ~collectionId,
      ~collectionName,
      ~onSaved,
    ) => {
  let (state, dispatch) =
    React.useReducer(reducer, getInitialState(citation));

  let (mutation, _simple, full) =
    CitationMutation.use(
      ~refetchQueries=
        _ => {
          let query = Queries.GetCollection.make(~collectionName, ());
          [|ReasonApolloHooks.Utils.toQueryObj(query)|];
        },
      (),
    );

  let save = () => {
    let variables =
      Mutations.EditCitation.make(
        ~collectionId,
        ~text=state.text,
        ~authorName=state.authorName,
        ~date=state.date |> Js.Json.string,
        (),
      )##variables;

    mutation(~variables, ())
    |> Js.Promise.(
         then_(result => {
           switch (result) {
           | ReasonApolloHooks.Mutation.Data(_) => onSaved()
           | _ => ignore()
           };
           resolve();
         })
       )
    |> ignore;
  };

  <form className=Classes.root>
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
      value={state.date}
      onChange={e => dispatch(UpdateDate(getInputValue(e)))}
      label="Date"
      type_="date"
      placeholder="When was it?"
      className=Classes.gutter
    />
    <Button
      fullWidth=true
      variant=`Primary
      type_="submit"
      onClick={_ => save()}
      disabled={!isValid(state) || full.loading}>
      {React.string("Save citation")}
    </Button>
  </form>;
};
