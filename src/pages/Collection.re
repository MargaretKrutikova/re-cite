open DesignSystem;
open Types;

module GetPageData = [%graphql
  {|
  query($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      ...EditCitation.Fragment.Collection
    }
  }
|}
];

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

module PageQuery = ReasonApolloHooks.Query.Make(GetPageData);

[@react.component]
let make = (~route, ~slug) => {
  let variables = GetPageData.make(~slug, ())##variables;

  let (simple, full) = PageQuery.use(~variables, ());

  let (state, dispatch) = React.useReducer(reducer, initialState);
  let canAdd = full.data->Belt.Option.isSome;

  let header =
    Header.Collection({canAdd, onAdd: _ => dispatch(OpenSidebar(None))});

  <div className={Classes.root()}>
    <Header header />
    <main className={Css.merge([Container.Styles.root, Classes.main])}>
      {switch (simple) {
       | Data(data) =>
         switch (data##collections) {
         | [|collection|] =>
           <>
             <Sidebar
               show={state.showSidebar} onClose={_ => dispatch(CloseSidebar)}>
               <EditCitation
                 citation={state.citationUnderEdit}
                 collection
                 onSaved={() => dispatch(CloseSidebar)}
                 refetchQueries={_ =>
                   [|
                     ReasonApolloHooks.Utils.toQueryObj(
                       CitationsPage.GetCitations.make(~slug, ()),
                     ),
                   |]
                 }
               />
             </Sidebar>
           </>
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
