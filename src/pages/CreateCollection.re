open Queries;
open ApolloHooks;

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

let refetchSlugs = GetAllCollectionSlugs.make() |> toQueryObj;

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initState());

  let (collectionsResult, _) = useQuery(GetAllCollectionSlugs.definition);
  let (mutation, mutationResult, _) =
    useMutation(Mutations.CreateCollection.definition, ~refetchQueries=_ =>
      [|refetchSlugs|]
    );

  let slugs =
    switch (collectionsResult) {
    | Data(data) => data##collections
    | _ => [||]
    };

  let handleSubmit = () => {
    switch (collectionsResult, mutationResult) {
    | (_, ApolloHooks.Mutation.Loading) => ignore()
    | (ApolloHooks.Query.Data(data), _) =>
      let error =
        CollectionName.toValidationError(data##collections, state.name);
      switch (error) {
      | Some(_) => dispatch(CollectionNameChange({name: state.name, error}))
      | None =>
        let slug = state.name |> Slug.make;
        let variables =
          Mutations.CreateCollection.make(~name=state.name, ~slug, ())##variables;

        mutation(~variables, ())
        |> Js.Promise.(
             then_(((simple, _full)) => {
               switch (simple) {
               | ApolloHooks.Mutation.Errors(_) => Js.log("error occured")
               | Data(_) => Route.push(Collection(slug, Citations))
               | _ => ignore()
               };
               resolve();
             })
           )
        |> ignore;
      };
    | _ => ignore()
    };
  };

  let disableSave =
    mutationResult == Loading
    || collectionsResult == Loading
    || state.error->Belt.Option.isSome;

  <Flex direction=`column className=Classes.root>
    <Heading level=`h2 gutter=`xl>
      {React.string("Generate collection name")}
    </Heading>
    <Text gutter=`lg>
      {React.string(
         "Create a unique link for you collection from its name,
          that only you will know.
          The link will be public, so you can share it with others.",
       )}
    </Text>
    <Text gutter=`xxl>
      {React.string(
         "Use this random name generator to find a good name!
         Alternatively, edit the field and set the name you prefer.",
       )}
    </Text>
    <CollectionName
      slugs
      name={state.name}
      readOnly=false
      error={state.error}
      onChange={output => dispatch(CollectionNameChange(output))}
    />
    <Flex align=`center justify=`center>
      <Text
        className=Classes.warningText
        gutter=`xl
        size=`Small
        variant=`Secondary>
        {React.string(
           "Please keep in mind that the link is public and your collection can be accessed
          just by its name. Don't include any personal details in the name.",
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
