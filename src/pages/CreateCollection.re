open DesignSystem;
open Queries;

module Classes = {
  open Css;
  let root = style([textAlign(center)]);
  let textField =
    style([marginBottom(px(0)), marginLeft(`md |> Styles.space)]);

  let textFieldContainer = style([marginBottom(`md |> Styles.space)]);
  let warningText =
    style([media(Breakpoint.up(`sm), [width(pct(80.0))])]);

  let errorMessage = style([height(`custom(10) |> Styles.space)]);

  let warning = style([position(absolute)]);
  let btn = style([alignSelf(`flexEnd)]);
};

module GetAlllugsQuery = ReasonApolloHooks.Query.Make(GetAllCollectionSlugs);

module CreateCollectionMutation =
  ReasonApolloHooks.Mutation.Make(Mutations.CreateCollection);

type state = {
  canEdit: bool,
  collectionName: string,
};

type action =
  | CollectionNameSet(string)
  | RequestNameEdit;

let reducer = (state, action) => {
  switch (action) {
  | CollectionNameSet(collectionName) => {...state, collectionName}
  | RequestNameEdit => {...state, canEdit: true}
  };
};

let initState = () => {
  collectionName: "test", //Utils.generateRandomCollectionName(),
  canEdit: false,
};

[@react.component]
let make = () => {
  let (collectionsResult, _) = GetAlllugsQuery.use();
  let (mutation, mutationResult, _) =
    CreateCollectionMutation.use(
      ~refetchQueries=
        _ => {
          let query = GetAllCollectionSlugs.make();
          [|ReasonApolloHooks.Utils.toQueryObj(query)|];
        },
      (),
    );

  let create = collectionName => {
    let slug = collectionName |> Slug.make;
    let variables =
      Mutations.CreateCollection.make(~name=collectionName, ~slug, ())##variables;

    mutation(~variables, ())
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

  let (state, dispatch) = React.useReducer(reducer, initState());

  let nameIsValid = state.collectionName |> Slug.make != "";
  let nameIsAvailable =
    switch (nameIsValid, collectionsResult) {
    | (true, Data(data)) =>
      let slug = state.collectionName |> Slug.make;
      !data##collections->Belt.Array.some(c => c##slug == slug);
    | _ => true
    };

  let updateName = e => {
    let name = e |> Utils.getInputValue;
    dispatch(CollectionNameSet(name));
  };

  let regenerateName = () => {
    let generatedName = Utils.generateRandomCollectionName();
    dispatch(CollectionNameSet(generatedName));
  };

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
    <Flex direction=`column>
      <Flex align=`center className=Classes.textFieldContainer>
        <Button color=`Primary icon=true onClick={_ => regenerateName()}>
          <ReactFeather.RefreshIcon />
        </Button>
        <TextField
          value={state.collectionName}
          onChange=updateName
          placeholder="Collection name"
          error={!nameIsAvailable}
          className=Classes.textField
          readOnly={!state.canEdit}
          highlight={state.canEdit}
        />
      </Flex>
      <div className=Classes.errorMessage>
        {nameIsValid && !nameIsAvailable
           ? <Text size=`Small variant=`Error gutter={`custom(0)}>
               {React.string("The name you entered is already occupied.")}
             </Text>
           : React.null}
      </div>
    </Flex>
    <Flex align=`center justify=`center>
      <Text
        className=Classes.warningText
        gutter=`xl
        size=`Small
        variant=`Secondary>
        <span> {React.string("Alternatively, ")} </span>
        <span
          className={Link.Classes.root(`Link, `Primary, ~isActive=false)}
          onClick={_ => dispatch(RequestNameEdit)}>
          {React.string("edit")}
        </span>
        <span>
          {React.string(
             " the name yourself. Don't include any personal details, since the link is public and can be accessed.",
           )}
        </span>
      </Text>
    </Flex>
    <Hr gutter=`xl />
    <Button
      variant=`Contained
      color=`Primary
      className=Classes.btn
      disabled={!nameIsValid || !nameIsAvailable || mutationResult == Loading}
      onClick={_ => create(state.collectionName)}
      gutter=`xxl>
      {React.string("Create collection")}
    </Button>
  </Flex>;
};
