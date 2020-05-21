open DesignSystem;

module Classes = {
  open Css;

  let errorMessage =
    style([height(`custom(8) |> Styles.space), textAlign(`center)]);
  let textField =
    style([
      marginBottom(`xs |> Styles.space),
      marginLeft(`md |> Styles.space),
    ]);
};

type validationError =
  | NameIsInvalid
  | NameIsOccupied;

type output = {
  name: string,
  error: option(validationError),
};

let toValidationError = (slugs, name) => {
  switch (name |> Slug.make) {
  | "" => Some(NameIsInvalid)
  | slug when slugs->Belt.Array.some(c => c##slug == slug) =>
    Some(NameIsOccupied)
  | _ => None
  };
};

[@react.component]
let make = (~onChange, ~readOnly, ~slugs, ~name, ~error) => {
  let handleChange = name =>
    onChange({name, error: name |> toValidationError(slugs)});
  let updateName = e => e |> Utils.getInputValue |> handleChange;
  let regenerateName = () =>
    Utils.generateRandomCollectionName() |> handleChange;

  <Flex direction=`column>
    <Flex align=`center>
      <Button color=`Primary icon=true onClick={_ => regenerateName()}>
        <ReactFeather.RefreshIcon />
      </Button>
      <TextField
        value=name
        onChange=updateName
        placeholder="Collection name"
        error={error->Belt.Option.isSome}
        className=Classes.textField
        readOnly
        highlight={!readOnly}
      />
    </Flex>
    <div className=Classes.errorMessage>
      {error->Belt.Option.mapWithDefault(React.null, err =>
         <Text size=`Small variant=`Error gutter={`custom(0)}>
           {(
              switch (err) {
              | NameIsInvalid => "The name is invalid."
              | NameIsOccupied => "The name you entered is already occupied."
              }
            )
            |> React.string}
         </Text>
       )}
    </div>
  </Flex>;
};
