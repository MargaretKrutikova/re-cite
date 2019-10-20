open DesignSystem;

module Classes = {
  let main =
    Css.(style([paddingTop(`xl |> Styles.space), textAlign(center)]));
};

[@react.component]
let make = () => {
  Styles.injectGlobal();
  let url = ReasonReactRouter.useUrl();

  <>
    {switch (url.path |> Route.fromUrl) {
     | Collection(name, route) => <Collection name route />
     | other =>
       <>
         <Header />
         <main className=Classes.main>
           {switch (other) {
            | Home =>
              <div> {React.string({j|Not implemented yet 🙂|j})} </div>
            | _ => <div> {React.string("Not found!")} </div>
            }}
         </main>
       </>
     }}
  </>;
};
