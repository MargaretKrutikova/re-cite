module Tokens = {
  type backgroundColor = [
    | `BodyBg
    | `PrimaryBg
    | `SecondaryBg
    | `HeaderBg
    | `InputBg
    | `CardBg
  ];

  type textColor = [ | `PrimaryText | `SecondaryText];

  type color = [
    | `Primary
    | `Secondary
    | `Neutral
    | backgroundColor
    | textColor
  ];

  type fontVariant = [ | `xs | `sm | `md | `lg | `xl | `xxl | `base];

  type fontFamily = [ | `base | `heading];

  type spacing = [
    | `xxs
    | `xs
    | `sm
    | `md
    | `lg
    | `xl
    | `xxl
    | `custom(int)
  ];

  type transitions = [ | `modal | `component];

  type borderRadius = [ | `base | `lg | `xl];
};

module Theme = {
  open Colors;

  /** base values */
  let baseFontSizePx = 20;
  let baseLineHeight = 1.4; // 28px
  let headingLineHeight = 1.2;

  let baseLineGridPx = 4; // factor of 28px
  let fontScale = 1.2;

  let fontSize = factor =>
    Js.Math.pow_float(~base=fontScale, ~exp=factor |> float_of_int)
    *. (baseFontSizePx |> float_of_int)
    |> int_of_float;

  let lineHeight =
    fun
    | `body => baseLineHeight
    | `heading => headingLineHeight;

  let fontVariant = (token: Tokens.fontVariant) => {
    let variant = (factor, line) => (fontSize(factor), lineHeight(line));

    switch (token) {
    | `xs => variant(-2, `body)
    | `sm => variant(-1, `body)
    | `base => variant(0, `body)
    | `md => variant(1, `body)
    | `lg => variant(2, `heading)
    | `xl => variant(3, `heading)
    | `xxl => variant(4, `heading)
    };
  };

  let space =
    fun
    | `xxs => baseLineGridPx
    | `xs => baseLineGridPx * 2
    | `sm => baseLineGridPx * 3
    | `md => baseLineGridPx * 4
    | `lg => baseLineGridPx * 6
    | `xl => baseLineGridPx * 8
    | `xxl => baseLineGridPx * 10
    | `custom(multiplier) => multiplier * baseLineGridPx;

  let color = (token: Tokens.color) => {
    switch (token) {
    | `Primary => Green.main // "#7d0f0f" // 916a70
    | `Secondary => Gray.light1
    | `Neutral => Gray.light1
    | `HeaderBg => White.main
    | `BodyBg => DarkBlue.light5 // dark: "1f364d"
    | `PrimaryBg => DarkBlue.light5
    | `SecondaryBg => DarkBlue.light4
    | `CardBg => White.main //"274059"
    | `InputBg => White.main
    | `PrimaryText => DarkBlue.dark1 //"fff"
    | `SecondaryText => DarkBlue.light1
    };
  };

  let fontFamily =
    fun
    | `base => "Rubik, serif"
    | `heading => "Muli, system-ui, sans-serif";

  let borderRadius =
    fun
    | `base => 4
    | `lg => 8
    | `xl => 20;

  type transition = {
    duration: int,
    fn: Css_Types.TimingFunction.t,
  };

  let transition =
    fun
    | `modal => {duration: 300, fn: Css.cubicBesier(0.77, 0.0, 0.175, 1.0)}
    | `component => {duration: 150, fn: Css.easeInOut};
};

module Styles = {
  let font = variant =>
    switch (variant |> Theme.fontVariant) {
    | (font_size, line_height) =>
      Css.[
        fontSize(`px(font_size)),
        lineHeight(`abs(line_height)),
        fontFamily(Theme.fontFamily(`base)),
      ]
    };

  let space = (token: Tokens.spacing) => `px(token |> Theme.space);

  let color = (token: Tokens.color) => `hex(token |> Theme.color);

  let borderRadius = (token: Tokens.borderRadius) =>
    Css.borderRadius(`px(token |> Theme.borderRadius));

  let paddingV = token => [
    token |> space |> Css.paddingTop,
    token |> space |> Css.paddingBottom,
  ];

  let paddingH = token => [
    token |> space |> Css.paddingLeft,
    token |> space |> Css.paddingRight,
  ];

  let animation = (token, name) => {
    let transition = token |> Theme.transition;
    Css.animation(
      ~duration=transition.duration,
      ~timingFunction=transition.fn,
      name,
    );
  };

  let transition = (token, property) => {
    let value = token |> Theme.transition;
    Css.(
      transition(~duration=value.duration, ~timingFunction=value.fn, property)
    );
  };

  let injectGlobal = () => {
    Css.global(
      "body",
      [
        Css.backgroundColor(color(`BodyBg)),
        Css.color(color(`PrimaryText)),
        ...font(`base),
      ],
    );

    Css.(
      global(
        ".block-scroll",
        [width(pct(100.0)), height(pct(100.0)), overflow(hidden)],
      )
    );
  };

  let toggleBodyScroll = (~disableScroll) => {
    let toggle =
      disableScroll ? DomUtils.addBodyClass : DomUtils.removeBodyClass;
    toggle("block-scroll");
  };
};
