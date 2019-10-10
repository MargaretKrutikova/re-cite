module Tokens = {
  type color =
    | Primary
    | Secondary
    | Neutral
    | BodyBg
    | BodyText;

  type fontVariant = [ | `xs | `sm | `md | `lg | `xl | `xxl | `base];

  type fontFamily = [ | `base];

  type spacingScale = [ | `xxs | `xs | `sm | `md | `lg | `xl | `xxl | `xxxl];

  type spacingType = [
    | `Component(spacingScale)
    | `Layout(spacingScale)
    | `Custom(int)
  ];
};

module Theme = {
  // base values
  let baseFontSizePx = 20;
  let baseLineHeight = 1.4; // 28px
  let baseLineGridPx = 4;
  let headingLineHeight = 1.2;

  let fontVariant =
    fun
    | `xs => (`px(14), `px(16))
    | `sm => (`px(17), `px(20))
    | `md => (`px(24), `px(32))
    | `lg => (`px(28), `px(34))
    | `xl => (`px(35), `px(40))
    | `xxl => (`px(44), `px(52))
    | `base => (`px(baseFontSizePx), `abs(baseLineHeight));

  let space =
    fun
    | `Component(scale) =>
      switch (scale) {
      | `xxs => 2
      | `xs => 4
      | `sm => 8
      | `md => 12
      | `lg => 16
      | `xl => 24
      | `xxl => 32
      | `xxxl => 40
      }
    | `Layout(scale) =>
      switch (scale) {
      | `xxs => 16
      | `xs => 24
      | `sm => 32
      | `md => 48
      | `lg => 64
      | `xl => 96
      | `xxl => 160
      | `xxxl => 224
      }
    | `Custom(multiplier) => multiplier * baseLineGridPx;

  let color = (token: Tokens.color) =>
    switch (token) {
    | Primary => "142d4c"
    | Secondary => "9fd3c7"
    | Neutral => ""
    | BodyBg => ""
    | BodyText => ""
    };

  let fontFamily =
    fun
    | `base => "Spectral, serif";
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

  let space = (token: Tokens.spacingType) => `px(token |> Theme.space);
};
