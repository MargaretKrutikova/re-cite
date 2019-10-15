module Tokens = {
  type color = [
    | `Primary
    | `Secondary
    | `Neutral
    | `BodyBg
    | `BodyText
    | `InputBg
    | `Label
    | `NeutralBorder
    | `ModalBg
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

module Theme = {
  // base values
  let baseFontSizePx = 20;
  let baseLineHeight = 1.4; // 28px
  let baseLineGridPx = 4;
  let headingLineHeight = 1.2;

  let fontVariant =
    fun
    | `xs => (`px(15), `px(18))
    | `sm => (`px(18), `px(22))
    | `md => (`px(24), `px(32))
    | `lg => (`px(28), `px(34))
    | `xl => (`px(35), `px(40))
    | `xxl => (`px(44), `px(52))
    | `base => (`px(baseFontSizePx), `abs(baseLineHeight));

  let space =
    fun
    | `xxs => 4
    | `xs => 8
    | `sm => 12
    | `md => 16
    | `lg => 24
    | `xl => 32
    | `xxl => 40
    | `xxxl => 48
    | `custom(multiplier) => multiplier * baseLineGridPx;

  let color = (token: Tokens.color) =>
    switch (token) {
    | `Primary => "9fd3c7"
    | `Secondary => "9fd3c7"
    | `Neutral => ""
    | `BodyBg => "fcfcfc"
    | `BodyText => "171717"
    | `InputBg => "fff"
    | `NeutralBorder => "ccc"
    | `Label => "555"
    | `ModalBg => "f3f3f3"
    };

  let fontFamily =
    fun
    | `base => "Spectral, serif";

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
        fontSize(font_size),
        lineHeight(line_height),
        fontFamily(Theme.fontFamily(`base)),
      ]
    };

  let space = (token: Tokens.spacingScale) => `px(token |> Theme.space);

  let color = (token: Tokens.color) => `hex(token |> Theme.color);

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
        Css.color(color(`BodyText)),
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
