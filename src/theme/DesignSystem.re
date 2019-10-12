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
  ];

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
    | `xs => (`px(15), `px(18))
    | `sm => (`px(18), `px(22))
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
      | `xxs => 8
      | `xs => 16
      | `sm => 24
      | `md => 32
      | `lg => 48
      | `xl => 64
      | `xxl => 96
      | `xxxl => 160
      }
    | `Custom(multiplier) => multiplier * baseLineGridPx;

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

  let color = (token: Tokens.color) => `hex(token |> Theme.color);

  let useGlobal = () => {
    Css.global(
      "body",
      [
        Css.backgroundColor(color(`BodyBg)),
        Css.color(color(`BodyText)),
        ...font(`base),
      ],
    );
  };
};
