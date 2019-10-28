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

module GetAllCollectionNames =
  ReasonApolloHooks.Query.Make(Queries.GetAllCollectionNames);

[@react.component]
let make = () => {
  let (collectionsResult, _) = GetAllCollectionNames.use();
  let (collectionName, setCollectionName) = React.useState(() => "");

  let nameIsValid = collectionName |> Utils.slugify != "";

  let nameIsAvailable =
    switch (nameIsValid, collectionsResult) {
    | (false, _) => true
    | (true, Data(data)) =>
      let slug = collectionName |> Utils.slugify;
      !data##collections->Belt.Array.some(c => c##name == slug);
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
                Make sure to include something that can identify your collection.",
              )}
           </Text>
         : React.null}
    </div>
    <Hr gutter=`md />
    <Button
      className=Classes.btn
      disabled={!nameIsValid || !nameIsAvailable}
      onClick={_ => Js.log(collectionName |> Utils.slugify)}
      gutter=`xxl>
      {React.string("Create collection")}
    </Button>
  </Flex>;
};
