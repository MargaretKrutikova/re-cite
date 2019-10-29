open DesignSystem;

module Classes = {
  open Css;
  let root = style([textAlign(center)]);
  let textField = style([marginBottom(`sm |> Styles.space)]);
  let block =
    style([
      height(`custom(16) |> Styles.space),
      marginBottom(`xl |> Styles.space),
      position(relative),
    ]);

  let warning = style([position(absolute)]);
  let btn = style([alignSelf(`flexEnd)]);
};

module GetAllCollectionSlugs =
  ReasonApolloHooks.Query.Make(Queries.GetAllCollectionSlugs);

module CreateCollectionMutation =
  ReasonApolloHooks.Mutation.Make(Mutations.CreateCollection);

[@react.component]
let make = () => {
  let (collectionsResult, _) = GetAllCollectionSlugs.use();
  let (mutation, mutationResult, _) =
    CreateCollectionMutation.use(
      ~refetchQueries=
        _ => {
          let query = Queries.GetAllCollectionSlugs.make();
          [|ReasonApolloHooks.Utils.toQueryObj(query)|];
        },
      (),
    );

  let (collectionName, setCollectionName) = React.useState(() => "");

  let create = () => {
    let slug = collectionName |> Utils.slugify;
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

  let nameIsValid = collectionName |> Utils.slugify != "";
  let nameIsAvailable =
    switch (nameIsValid, collectionsResult) {
    | (false, _) => true
    | (true, Data(data)) =>
      let slug = collectionName |> Utils.slugify;
      Js.log(slug);
      !data##collections->Belt.Array.some(c => c##slug == slug);
    | _ => false
    };

  let updateName = e => {
    let name = e |> Utils.getInputValue;
    setCollectionName(_ => name);
  };

  <Flex direction=`column className=Classes.root>
    <Heading level=`h2>
      {React.string("Give your collection a nice name")}
    </Heading>
    <Text gutter=`xxl>
      {React.string(
         "Let's say you want to save jokes you hear at work,
      then the company's name would be a perfect fit for such a collection.",
       )}
    </Text>
    <TextField
      value=collectionName
      onChange=updateName
      placeholder="Collection name"
      error={!nameIsAvailable}
      className=Classes.textField
    />
    <div className=Classes.block>
      {nameIsValid && !nameIsAvailable
         ? <Text size=`Small variant=`Secondary>
             {React.string(
                "Sorry, but the name you entered is occupied.
                Make sure to include something that can uniquely identify your collection.",
              )}
           </Text>
         : React.null}
    </div>
    <Hr gutter=`md />
    <Button
      className=Classes.btn
      disabled={!nameIsValid || !nameIsAvailable || mutationResult == Loading}
      onClick={_ => create()}
      gutter=`xxl>
      {React.string("Create collection")}
    </Button>
  </Flex>;
};
