open DesignSystem;

module Classes = {
  let main = Css.(style([paddingTop(`xl |> Styles.space)]));
};

[@react.component]
let make = () => {
  Styles.injectGlobal();
  let (showSidebar, setShowSidebar) = React.useState(_ => false);

  <>
    <Header onAddClick={_ => setShowSidebar(prev => !prev)} />
    <Sidebar show=showSidebar onClose={_ => setShowSidebar(_ => false)}>
      <EditCitation />
    </Sidebar>
    <main className={Css.merge([Container.Styles.root, Classes.main])}>
      <CitationsPage />
    </main>
  </>;
};
