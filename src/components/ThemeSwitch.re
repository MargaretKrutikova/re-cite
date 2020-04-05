[@react.component]
let make = (~className="") => {
  let (theme, toggleTheme) = ThemeContext.useTheme();

  let activeSide =
    switch (theme) {
    | ThemeContext.Light => Switch.Right
    | Dark => Left
    };

  <div className>
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
