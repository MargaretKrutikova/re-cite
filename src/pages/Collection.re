open Queries;
open DesignSystem;
open Types;

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
  | Idle;

type state = {status};

let shouldShowSidebar =
  fun
  | UpdatingCitation(_)
  | AddingCitation => true
  | _ => false;

type action =
  | RequestEditCitation(citation)
  | RequestAddCitation
  | SidebarClosed;

let reducer = (_, action) => {
  switch (action) {
  | RequestEditCitation(citationUnderEdit) => {
      status: UpdatingCitation(citationUnderEdit),
    }
  | RequestAddCitation => {status: AddingCitation}
  | SidebarClosed => {status: Idle}
  };
};

let initialState = {status: Idle};

module PageQuery = ReasonApolloHooks.Query.Make(GetCollectionBySlug);

[@react.component]
let make = (~route, ~slug) => {
  let variables = GetCollectionBySlug.make(~slug, ())##variables;

  let (simple, full) = PageQuery.use(~variables, ());

  let (state, dispatch) = React.useReducer(reducer, initialState);

  let canAdd = full.data->Belt.Option.isSome;
  let onAdd = _ => dispatch(RequestAddCitation);

  let header = Header.Collection({slug, canAdd, onAdd});

  let refetchCitationsQuery =
    ReasonApolloHooks.Utils.toQueryObj(GetCitations.make(~slug, ()));

  <div className={Classes.root()}>
    <Header header />
    <main className={Css.merge([Container.Styles.root, Classes.main])}>
      {switch (route) {
       | Route.Citations =>
         <CitationsPage
           slug
           onEdit={citation => dispatch(RequestEditCitation(citation))}
         />
       | Route.CitationById(stringId) =>
         switch (int_of_string(stringId)) {
         | exception _ =>
           <Text> {React.string("The citation is not found")} </Text>
         | id => <CitationPage slug id />
         }
       | Route.RandomCitation => <RandomCitation slug />
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
                  onSaved={() => dispatch(SidebarClosed)}
                  refetchQueries={_ => [|refetchCitationsQuery|]}
                />
              | UpdatingCitation(citation) =>
                <UpdateCitation
                  citation
                  collection
                  onSaved={() => dispatch(SidebarClosed)}
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
