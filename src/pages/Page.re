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
  GlobalCss.injectGlobal();
  let url = ReasonReactRouter.useUrl();
  Styles.useToggleBodyTheme();

  switch (url.path |> Route.fromUrl) {
  | Collection(slug, route) => <Collection slug route />
  | other =>
    <>
      <Header type_=HeaderModel.Default />
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
