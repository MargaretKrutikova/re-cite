module Mutation = ReasonApolloHooks.Mutation.Make(Mutations.AddCitation);

[@react.component]
let make = (~collection, ~onSaved, ~refetchQueries) => {
  let (mutation, _simple, full) = Mutation.use(~refetchQueries, ());

  let save = (formState: CitationForm.state) => {
    let variables =
      Mutations.AddCitation.makeVariables(
        ~collectionId=collection##id,
        ~text=formState.text,
        ~authorName=formState.authorName,
        ~date=formState.date |> Js.Json.string,
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
    operation=CitationForm.Adding
    onSave=save
    isSaving={full.loading}
  />;
};
