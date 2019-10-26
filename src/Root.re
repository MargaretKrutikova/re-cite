[@react.component]
let make = () => {
  let (theme, setTheme) = React.useState(() => ThemeContext.Light);
  let toggleTheme = () =>
    setTheme(current =>
      switch (current) {
      | Light => Dark
      | Dark => Light
      }
    );

  <ThemeContext.Provider value=(theme, toggleTheme)>
    <Page />
  </ThemeContext.Provider>;
};
