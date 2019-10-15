let use = (~show) => {
  let (shouldRender, setRender) = React.useState(_ => show);

  React.useLayoutEffect1(
    () => {
      if (show) {
        setRender(_ => true);
      };
      None;
    },
    [|show|],
  );

  let onAnimationEnd = _ =>
    if (!show) {
      setRender(_ => false);
    };

  (shouldRender || show, onAnimationEnd);
};
