open DesignSystem;

[@react.component]
let make = () => {
  Styles.injectGlobal();
  let url = ReasonReactRouter.useUrl();
  let (theme, toggleTheme) = ThemeContext.useTheme();
  Styles.useToggleBodyTheme();

  switch (url.path |> Route.fromUrl) {
  | Collection(name, route) => <Collection name route />
  | other =>
    <>
      <Header toggleTheme theme header=Header.Default />
      <main className=Container.Styles.root>
        {switch (other) {
         | Home => <Home />
         | _ => <div> {React.string("Not found!")} </div>
         }}
      </main>
    </>
  };
};
