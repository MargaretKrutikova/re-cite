open DesignSystem;

module Classes = {
  open Css;

  let root =
    style([
      marginTop(`xl |> Styles.space),
      media(
        Breakpoint.up(`sm),
        [padding(px(0)), marginTop(`xxl |> Styles.space)],
      ),
      ...Styles.paddingH(`xxs),
    ]);
};

[@react.component]
let make = () => {
  Styles.injectGlobal();
  let url = ReasonReactRouter.useUrl();
  let (theme, toggleTheme) = ThemeContext.useTheme();
  Styles.useToggleBodyTheme();

  switch (url.path |> Route.fromUrl) {
  | Collection(slug, route) => <Collection slug route />
  | other =>
    <>
      <Header toggleTheme theme header=Header.Default />
      <main className=Container.Styles.root>
        <div className=Classes.root>
          {switch (other) {
           | Home => <Home />
           | CreateCollection => <CreateCollection />
           | _ => <div> {React.string("Not found!")} </div>
           }}
        </div>
      </main>
    </>
  };
};
