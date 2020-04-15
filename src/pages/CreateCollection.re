open Queries;

module Classes = {
  open Css;
  let root = style([textAlign(center)]);

  let warningText =
    style([media(Breakpoint.up(`sm), [width(pct(80.0))])]);
  let btn = style([alignSelf(`flexEnd)]);
};

type state = {
  canEdit: bool,
  error: option(CollectionName.validationError),
  name: string,
};

type action =
  | CollectionNameChange(CollectionName.output)
  | RequestNameEdit;

let reducer = (state, action) => {
  switch (action) {
  | CollectionNameChange({name, error}) => {...state, name, error}
  | RequestNameEdit => {...state, canEdit: true}
  };
};

let initState = () => {
  name: Utils.generateRandomCollectionName(),
  error: None,
  canEdit: true,
};

module GetAllSlugsQuery = ReasonApolloHooks.Query.Make(GetAllCollectionSlugs);

module CreateCollectionMutation =
  ReasonApolloHooks.Mutation.Make(Mutations.CreateCollection);

let refetchSlugs =
  GetAllCollectionSlugs.make() |> ReasonApolloHooks.Utils.toQueryObj;

let createCollection = (save: CreateCollectionMutation.mutation, name) => {
  let slug = name |> Slug.make;
  let variables =
    Mutations.CreateCollection.make(~name, ~slug, ())##variables;

  save(~variables, ())
  |> Js.Promise.(
       then_(result => {
         switch (result) {
         | ReasonApolloHooks.Mutation.Data(_) =>
           Route.push(Collection(slug, Citations))
         | _ => ignore()
         };
         resolve();
       })
     )
  |> ignore;
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initState());

  let (collectionsResult, _) = GetAllSlugsQuery.use();
  let (mutation, mutationResult, _) =
    CreateCollectionMutation.use(~refetchQueries=_ => [|refetchSlugs|], ());

  let slugs =
    switch (collectionsResult) {
    | Data(data) => data##collections
    | _ => [||]
    };

  let handleSubmit = () => {
    switch (collectionsResult, mutationResult) {
    | (_, ReasonApolloHooks.Mutation.Loading) => ignore()
    | (ReasonApolloHooks.Query.Data(data), _) =>
      let error =
        CollectionName.toValidationError(data##collections, state.name);
      switch (error) {
      | Some(_) => dispatch(CollectionNameChange({name: state.name, error}))
      | None => createCollection(mutation, state.name)
      };
    | _ => ignore()
    };
  };

  let disableSave =
    mutationResult == Loading
    || collectionsResult == Loading
    || state.error->Belt.Option.isSome;

  <Flex direction=`column className=Classes.root>
    <Heading level=`h2> {React.string("Generate collection name")} </Heading>
    <Text gutter=`sm>
      {React.string(
         "You will get a unique link for you collection from its name,
          that only you will know.
          The link will be public, so you can share it with others.",
       )}
    </Text>
    <Text gutter=`xxl>
      {React.string("Use this random name generator to find a good name!")}
    </Text>
    <CollectionName
      slugs
      name={state.name}
      readOnly={!state.canEdit}
      error={state.error}
      onChange={output => dispatch(CollectionNameChange(output))}
    />
    <Flex align=`center justify=`center>
      <Text
        className=Classes.warningText
        gutter=`xl
        size=`Small
        variant=`Secondary>
        {React.string("Alternatively, ")}
        <span
          className={Link.Classes.root(`Link, `Primary, ~isActive=false)}
          onClick={_ => dispatch(RequestNameEdit)}>
          {React.string("edit")}
        </span>
        {React.string(
           " the name yourself. Don't include any personal details,
           since the link is public and can be accessed.",
         )}
      </Text>
    </Flex>
    <Hr gutter=`xl />
    <Button
      variant=`Contained
      color=`Primary
      className=Classes.btn
      disabled=disableSave
      onClick={_ => handleSubmit()}
      gutter=`xxl>
      {React.string("Create collection")}
    </Button>
  </Flex>;
};
