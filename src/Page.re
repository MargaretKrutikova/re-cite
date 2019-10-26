open DesignSystem;

module Classes = {
  let main =
    Css.(
      style([
        media(Breakpoint.up(`sm), [paddingTop(`md |> Styles.space)]),
        paddingTop(`sm |> Styles.space),
        textAlign(center),
      ])
    );
};

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
      <main className=Classes.main>
        {switch (other) {
         | Home => <div> {React.string({j|Not implemented yet 🙂|j})} </div>
         | _ => <div> {React.string("Not found!")} </div>
         }}
      </main>
    </>
  };
};
