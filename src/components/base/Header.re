open DesignSystem;

module Classes = {
  let container =
    Css.(
      style([
        display(`flex),
        justifyContent(`spaceBetween),
        alignItems(`center),
        width(pct(100.0)),
        height(pct(100.0)),
      ])
    );
  let root = () =>
    Css.(
      style([
        height(`custom(16) |> Styles.space),
        borderBottom(px(1), `solid, `Primary |> Styles.useColor),
        backgroundColor(`BodyBg1 |> Styles.useColor),
      ])
    );
  let logo =
    Css.(
      style([
        fontWeight(`num(500)),
        cursor(`pointer),
        ...Styles.font(`lg),
      ])
    );
  let themeSwitch =
    Css.(style([marginRight(auto), marginLeft(`md |> Styles.space)]));
};

module ThemeSwitch = {
  [@react.component]
  let make = (~toggleTheme, ~theme) => {
    let activeSide =
      switch (theme) {
      | ThemeContext.Light => Switch.Right
      | Dark => Left
      };

    <div className=Classes.themeSwitch>
      <Switch activeSide>
        <Switch.Button isActive={theme == ThemeContext.Dark}>
          <Button variant=`None onClick={_ => toggleTheme()} icon=true>
            <ReactFeather.MoonIcon />
          </Button>
        </Switch.Button>
        <Switch.Button isActive={theme == ThemeContext.Light}>
          <Button variant=`None onClick={_ => toggleTheme()} icon=true>
            <ReactFeather.SunIcon />
          </Button>
        </Switch.Button>
      </Switch>
    </div>;
  };
};

module Logo = {
  [@react.component]
  let make = () => {
    <a
      className=Classes.logo
      onClick={RouteLink.handleClick(Route.toUrl(Home))}>
      {React.string("ReCite.")}
    </a>;
  };
};

type collectionHeader = {
  canAdd: bool,
  onAdd: unit => unit,
};

type header =
  | Default
  | Collection(collectionHeader);

[@react.component]
let make = (~header) => {
  let (theme, toggleTheme) = ThemeContext.useTheme();

  <header className={Classes.root()}>
    <Container className=Classes.container>
      <Logo />
      <ThemeSwitch toggleTheme theme />
      {switch (header) {
       | Default => React.null
       | Collection({onAdd, canAdd}) =>
         <Button
           disabled={!canAdd}
           variant=`Contained
           color=`Primary
           onClick={_ => onAdd()}>
           {React.string("Add")}
         </Button>
       }}
    </Container>
  </header>;
};
