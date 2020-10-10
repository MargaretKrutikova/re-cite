open DesignSystem;
open ApolloHooks;

module Classes = {
  open Css;
  let root = style([display(`flex), flexDirection(column)]);
  let header =
    style([
      marginBottom(`md |> Styles.space),
      fontWeight(`light),
      ...Styles.font(`md),
    ]);

  let warningIcon = () =>
    style([
      color(`Alert |> Styles.useColor),
      marginRight(`xs |> Styles.space),
    ]);
};

type state = {
  error: option(CollectionName.validationError),
  name: string,
};

type action =
  | CollectionNameChange(CollectionName.output);

let reducer = (_, action) => {
  switch (action) {
  | CollectionNameChange({name, error}) => {name, error}
  };
};

let initState = () => {
  name: Utils.generateRandomCollectionName(),
  error: None,
};

let updateCollectionName =
    (~updateMutation, ~name, ~collectionId: Js.Json.t, ~onClose) => {
  let slug = name |> Slug.make;
  let variables =
    Mutations.UpdateCollection.make(~name, ~slug, ~collectionId, ())##variables;

  updateMutation(~variables, ())
  |> Js.Promise.(
       then_(result => {
         switch (result) {
         | ApolloHooks.Mutation.Data(_) =>
           Route.push(Collection(slug, Citations))
         | _ => ignore()
         };
         onClose();
         resolve();
       })
     )
  |> ignore;
};

[@react.component]
let make = (~collectionId, ~onClose) => {
  let (state, dispatch) = React.useReducer(reducer, initState());

  let (collectionsResult, _) =
    useQuery(Queries.GetAllCollectionSlugs.definition);
  let (updateMutation, mutationResult, _) =
    useMutation(Mutations.UpdateCollection.definition);

  let handleSubmit = () => {
    switch (collectionsResult, mutationResult) {
    | (_, Loading) => ignore()
    | (Data(data), _) =>
      let error =
        CollectionName.toValidationError(data##collections, state.name);

      switch (error) {
      | Some(_) => dispatch(CollectionNameChange({name: state.name, error}))
      | None =>
        let slug = state.name |> Slug.make;
        let variables =
          Mutations.UpdateCollection.make(
            ~name=state.name,
            ~slug,
            ~collectionId,
            (),
          )##variables;

        updateMutation(~variables, ())
        |> Js.Promise.(
             then_(((simple, _full)) => {
               switch (simple) {
               | ApolloHooks.Mutation.Errors(_) => ignore()
               | Data(_) => Route.push(Collection(slug, Citations))
               | NoData => ignore()
               };
               onClose();
               resolve();
             })
           )
        |> ignore;
      };

    | _ => ignore()
    };
  };

  let slugs =
    switch (collectionsResult) {
    | Data(data) => data##collections
    | _ => [||]
    };

  let disableSave =
    mutationResult == Loading
    || collectionsResult == Loading
    || state.error->Belt.Option.isSome;

  <form
    className=Classes.root onSubmit={e => ReactEvent.Form.preventDefault(e)}>
    <div className=Classes.header>
      {React.string("Change collection name")}
    </div>
    <Flex align=`center justify=`center>
      <Text gutter=`md size=`Small variant=`Secondary>
        {React.string(
           "Edit your collection's name or anonymize it with our random name generator.",
         )}
      </Text>
    </Flex>
    <CollectionName
      slugs
      name={state.name}
      readOnly=false
      error={state.error}
      onChange={output => dispatch(CollectionNameChange(output))}
    />
    <Flex align=`center justify=`center>
      <Text gutter=`xl size=`Small variant=`Secondary>
        <span className={Classes.warningIcon()}>
          <ReactFeather.AlertIcon />
        </span>
        {React.string(
           "Updating the name is irreversible and will generate a new link. Use
           it instead of the current one, since there is no automatic redirect.",
         )}
      </Text>
    </Flex>
    <Button
      fullWidth=true
      variant=`Contained
      color=`Primary
      type_="button"
      disabled=disableSave
      onClick={_ => handleSubmit()}>
      {React.string("Save")}
    </Button>
  </form>;
};
