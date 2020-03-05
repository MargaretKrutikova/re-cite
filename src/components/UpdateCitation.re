open Types;

module CitationMutation =
  ReasonApolloHooks.Mutation.Make(Mutations.UpdateCitation);

[@react.component]
let make = (~citation: Types.citation, ~collection, ~onSaved, ~refetchQueries) => {
  let (mutation, _simple, full) = CitationMutation.use(~refetchQueries, ());

  let save = (formState: CitationForm.state) => {
    let variables =
      Mutations.UpdateCitation.makeVariables(
        ~id=citation.id,
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
    operation={CitationForm.Updating(citation)}
    onSave=save
    isSaving={full.loading}
  />;
};
