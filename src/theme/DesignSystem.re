module Tokens = {
  type color = [
    | `Primary
    | `Secondary
    | `BodyBg
    | `HeaderBg
    | `InputBg
    | `NeutralBorder
    | `ModalBg
    | `CardBg
    | `PrimaryText
    | `SecondaryText
  ];

  type fontVariant = [ | `xs | `sm | `md | `lg | `xl | `xxl | `base];

  type fontFamily = [ | `base];

  type spacingScale = [
    | `xxs
    | `xs
    | `sm
    | `md
    | `lg
    | `xl
    | `xxl
    | `xxxl
    | `custom(int)
  ];

  type transitions = [ | `Modal];
};

module DarkBlue = {
  let main = "4a5568";
  let darker = "353d4a";
  let lighter = "667590";
  let extraLight = "f0f1f4";
};

module Green = {
  let main = "449582";
  let lighter = "9fd3c7";
};

module White = {
  let main = "fff";
};

module Theme = {
  // base values
  let baseFontSizePx = 20; // Dont touch
  let baseLineHeight = 1.4; // 28px
  let baseLineGridPx = 4;

  let headingLineHeight = 1.2;
  let fontScale = 1.2;

  let borderRadius = 4;

  let fontSize =
    ThemeUtils.genFontSize(~baseFontSize=baseFontSizePx, ~fontScale);

  let fontVariant =
    fun
    | `xs => (fontSize(-2.0), baseLineHeight)
    | `sm => (fontSize(-1.0), baseLineHeight)
    | `base => (fontSize(0.0), baseLineHeight)
    | `md => (fontSize(1.0), baseLineHeight)
    | `lg => (fontSize(2.0), headingLineHeight)
    | `xl => (fontSize(3.0), headingLineHeight)
    | `xxl => (fontSize(4.0), headingLineHeight);

  let space =
    fun
    | `xxs => baseLineGridPx
    | `xs => baseLineGridPx * 2
    | `sm => baseLineGridPx * 3
    | `md => baseLineGridPx * 4
    | `lg => baseLineGridPx * 6
    | `xl => baseLineGridPx * 8
    | `xxl => baseLineGridPx * 10
    | `xxxl => baseLineGridPx * 12
    | `custom(multiplier) => multiplier * baseLineGridPx;

  let color = (token: Tokens.color) =>
    switch (token) {
    | `Primary => Green.main // "#7d0f0f" // 916a70
    | `Secondary => "9fd3c7"
    | `HeaderBg => White.main
    | `BodyBg => DarkBlue.extraLight // dark: "1f364d"
    | `CardBg => White.main //"274059"
    | `InputBg => White.main
    | `NeutralBorder => "dcdcdc"
    | `ModalBg => DarkBlue.extraLight
    | `PrimaryText => DarkBlue.darker //"fff"
    | `SecondaryText => DarkBlue.lighter
    };

  let fontFamily =
    fun
    | `base => "Rubik, serif";

  type transition = {
    duration: int,
    fn: Css_Types.TimingFunction.t,
  };
  let transition =
    fun
    | `Modal => {duration: 300, fn: Css.cubicBesier(0.77, 0.0, 0.175, 1.0)};
};

module Styles = {
  let font = (variant: Tokens.fontVariant) =>
    switch (variant |> Theme.fontVariant) {
    | (font_size, line_height) =>
      Css.[
        fontSize(`px(font_size)),
        lineHeight(`abs(line_height)),
        fontFamily(Theme.fontFamily(`base)),
      ]
    };

  let space = (token: Tokens.spacingScale) => `px(token |> Theme.space);

  let color = (token: Tokens.color) => `hex(token |> Theme.color);

  let borderRadius = () => Css.borderRadius(`px(Theme.borderRadius));

  let paddingV = (token: Tokens.spacingScale) => [
    token |> space |> Css.paddingTop,
    token |> space |> Css.paddingBottom,
  ];

  let paddingH = (token: Tokens.spacingScale) => [
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
