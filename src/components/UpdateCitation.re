open Types;

module CitationMutation =
  ReasonApolloHooks.Mutation.Make(Mutations.UpdateCitation);

let getCitationToUpdate = ({text, added, author}): CitationForm.state => {
  text,
  date: added->Belt.Option.getWithDefault(""),
  authorName: author.name,
};

[@react.component]
let make = (~citation: Types.citation, ~collection, ~onSaved) => {
  let (mutation, _simple, full) = CitationMutation.use();

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
    citation={getCitationToUpdate(citation)}
    onSave=save
    isSaving={full.loading}
  />;
};
