module Mutation = ReasonApolloHooks.Mutation.Make(Mutations.AddCitation);

let getNewCitation = (): CitationForm.state => {
  text: "",
  authorName: "",
  date: Js.Date.make(),
};

[@react.component]
let make = (~collection, ~onSaved, ~refetchQueries) => {
  let (mutation, _simple, full) = Mutation.use(~refetchQueries, ());

  let save = (formState: CitationForm.state) => {
    let variables =
      Mutations.AddCitation.makeVariables(
        ~collectionId=collection##id,
        ~text=formState.text,
        ~authorName=formState.authorName,
        ~date=formState.date |> Utils.toApiDate,
        (),
      );

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

  let authors = collection##authors;
  <CitationForm
    authors
    citation={getNewCitation()}
    onSave=save
    isSaving={full.loading}
  />;
};
