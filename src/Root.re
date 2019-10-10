open DesignSystem;

let s = React.string;

[@react.component]
let make = () => {
  AppTheme.useGlobal();
  let citationStyles =
    Css.(
      style([
        marginBottom(`Layout(`xs) |> Styles.space),
        borderBottom(`px(1), `solid, `hex("eee")),
        paddingBottom(`Layout(`xxs) |> Styles.space),
      ])
    );
  <div>
    <Citation
      text={j|Någon annan får granska det. Det är inte mitt jobb att granska min egen kod!|j}
      author="Erik T"
      date="2019-05-10"
      className=citationStyles
      clr="a6e3e9"
    />
    <Citation
      text={j|Vi behöver inte vara så konstruktiva.|j}
      author="Erik T"
      className=citationStyles
      clr="cbf1f5"
      date="2019-05-10"
    />
    <Citation
      text={j|Jag skulle kunna, om jag vill, definiera varje cell som en person. För att det är en individ.|j}
      author="Erik T"
      date="2019-05-10"
      className=citationStyles
      clr="ffe6eb"
    />
  </div>;
};
