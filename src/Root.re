open DesignSystem;

let s = React.string;

module Classes = {
  open Css;

  let main = style([paddingTop(`Layout(`md) |> Styles.space)]);

  let citation =
    style([
      marginBottom(`Layout(`sm) |> Styles.space),
      borderBottom(px(1), `solid, `hex("dcdcdc")),
      paddingBottom(`Layout(`xs) |> Styles.space),
    ]);
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
    <main className={Emotion.cx([|Container.Styles.root, Classes.main|])}>
      <Citation
        text={j|Någon annan får granska det. Det är inte mitt jobb att granska min egen kod!|j}
        author="Erik T"
        date="2019-05-10"
        className=Classes.citation
      />
      <Citation
        text={j|Vi behöver inte vara så konstruktiva.|j}
        author="Erik T"
        className=Classes.citation
        date="2019-05-10"
      />
      <Citation
        text={j|Jag skulle kunna, om jag vill, definiera varje cell som en person. För att det är en individ.|j}
        author="Erik T"
        date="2019-05-10"
        className=Classes.citation
      />
    </main>
  </>;
};
