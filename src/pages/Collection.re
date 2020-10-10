open Queries;
open DesignSystem;
open Types;
open ApolloHooks;

module Classes = {
  let main =
    Css.(
      style([
        media(Breakpoint.up(`sm), [paddingTop(`xl |> Styles.space)]),
        ...Styles.paddingV(`lg),
      ])
    );
  let root = () =>
    Css.(
      style([
        backgroundColor(`BodyBg2 |> Styles.useColor),
        minHeight(vh(100.0)),
      ])
    );
};

type status =
  | UpdatingCitation(citation)
  | AddingCitation
  | EditingSettings
  | Idle;

type state = {status};

let shouldShowSidebar =
  fun
  | Idle => false
  | _ => true;

type action =
  | RequestEditCitation(citation)
  | RequestAddCitation
  | RequestEditSettings
  | SidebarClosed;

let reducer = (_, action) => {
  switch (action) {
  | RequestEditCitation(citationUnderEdit) => {
      status: UpdatingCitation(citationUnderEdit),
    }
  | RequestAddCitation => {status: AddingCitation}
  | RequestEditSettings => {status: EditingSettings}
  | SidebarClosed => {status: Idle}
  };
};

let initialState = {status: Idle};

[@react.component]
let make = (~route, ~slug) => {
  let variables = GetCollectionBySlug.make(~slug, ())##variables;

  let (simple, full) = useQuery(GetCollectionBySlug.definition, ~variables);

  let (state, dispatch) = React.useReducer(reducer, initialState);

  let canAdd = full.data->Belt.Option.isSome;

  let onAdd = _ => dispatch(RequestAddCitation);
  let onEditSettings = _ => dispatch(RequestEditSettings);
  let onSidebarClosed = () => dispatch(SidebarClosed);
  let onEdit = citation => dispatch(RequestEditCitation(citation));

  let refetchCitationsQuery = toQueryObj(GetCitations.make(~slug, ()));

  <div className={Classes.root()}>
    <Header
      type_={HeaderModel.Collection({slug, canAdd, onAdd, onEditSettings})}
    />
    <main className={Css.merge([Container.Styles.root, Classes.main])}>
      {switch (route) {
       | Route.Citations => <CitationsPage slug onEdit />
       | Route.CitationById(stringId) =>
         switch (int_of_string(stringId)) {
         | exception _ =>
           <Text> {React.string("The citation is not found")} </Text>
         | id => <CitationPage slug id onEdit />
         }
       | Route.RandomCitation => <RandomCitation slug onEdit />
       }}
      {switch (simple) {
       | Data(data) =>
         switch (data##collections) {
         | [|collection|] =>
           <Sidebar
             show={shouldShowSidebar(state.status)}
             onClose={_ => dispatch(SidebarClosed)}>
             {switch (state.status) {
              | Idle => React.null
              | AddingCitation =>
                <AddCitation
                  collection
                  onSaved=onSidebarClosed
                  refetchQueries={_ => [|refetchCitationsQuery|]}
                />
              | UpdatingCitation(citation) =>
                <UpdateCitation citation collection onSaved=onSidebarClosed />
              | EditingSettings =>
                <SettingsForm
                  collectionId={collection##id}
                  onClose=onSidebarClosed
                />
              }}
           </Sidebar>
         | _ => React.null // Should never happen :)
         }
       | NoData
       | Loading => React.null
       | Error(e) =>
         Js.log(e);
         React.null;
       }}
    </main>
  </div>;
};
