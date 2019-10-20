open DesignSystem;
open Types;

module Classes = {
  let main = Css.(style([paddingTop(`xl |> Styles.space)]));
};

type state = {
  showSidebar: bool,
  citationUnderEdit: option(citation),
};

type action =
  | OpenSidebar(option(citation))
  | CloseSidebar;

let reducer = (_, action) => {
  switch (action) {
  | OpenSidebar(citationUnderEdit) => {showSidebar: true, citationUnderEdit}
  | CloseSidebar => {showSidebar: false, citationUnderEdit: None}
  };
};

let initialState = {showSidebar: false, citationUnderEdit: None};

module CollectionQuery = ReasonApolloHooks.Query.Make(Queries.GetCollection);

[@react.component]
let make = (~route, ~name) => {
  Styles.injectGlobal();
  let variables =
    Queries.GetCollection.make(~collectionName=name, ())##variables;
  let (simple, full) = CollectionQuery.use(~variables, ());

  let (state, dispatch) = React.useReducer(reducer, initialState);
  let canAdd = full.data->Belt.Option.isSome;

  <>
    <Header.Collection
      canAdd
      onAddClick={_ => dispatch(OpenSidebar(None))}
    />
    <main className={Css.merge([Container.Styles.root, Classes.main])}>
      {switch (simple) {
       | Loading => <p> {React.string("Loading...")} </p>
       | Data(data) =>
         switch (data##collections) {
         | [||] =>
           Route.push(NotFound);
           React.null;

         | [|collection|] =>
           <>
             <Sidebar
               show={state.showSidebar} onClose={_ => dispatch(CloseSidebar)}>
               <EditCitation
                 citation={state.citationUnderEdit}
                 collectionId={collection.id}
                 collectionName={collection.name}
                 onSaved={() => dispatch(CloseSidebar)}
               />
             </Sidebar>
             {switch (route) {
              | Route.Citations =>
                <Citations citations={collection.citations} />
              }}
           </>
         | _ => React.null // Should never happen :)
         }
       | NoData
       | Error(_) => <p> {React.string("Error")} </p>
       }}
    </main>
  </>;
};
