open DesignSystem;

let injectGlobal = () => {
  Css.global(
    "body",
    [
      Styles.transition(`theme, "background-color, color"),
      ...Styles.font(`base),
    ],
  );

  Css.global(
    ".dark-theme",
    [
      Css.backgroundColor(Styles.color(`BodyBg1, Dark)),
      Css.color(Styles.color(`BodyText, Dark)),
    ],
  );

  Css.global(
    ".light-theme",
    [
      Css.backgroundColor(Styles.color(`BodyBg1, Light)),
      Css.color(Styles.color(`BodyText, Light)),
    ],
  );

  Css.(
    global(
      ".block-scroll",
      [width(pct(100.0)), height(pct(100.0)), overflow(hidden)],
    )
  );

  Css.(
    global(
      ".Toastify__toast-container",
      [
        media(
          Breakpoint.down(`sm),
          [
            width(auto) |> important,
            maxWidth(px(200)),
            margin2(~v=px(0), ~h=auto) |> important,
          ],
        ),
      ],
    )
  );
};
