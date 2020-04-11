open DesignSystem;

type size = [ | `Medium | `Large];

module Classes = {
  open Css;

  let upvoteContainer = style([marginLeft(`lg |> Styles.space)]);

  let upvoteCount = size => {
    let (ml, fs) =
      switch (size) {
      | `Medium => (`xxs, 18)
      | `Large => (`xxs, 22)
      };
    style([marginLeft(ml |> Styles.space), fontSize(px(fs))]);
  };
  let upvoteButton = () => style([color(`BodyText |> Styles.useColor)]);
  let upvoteIcon = size => {
    let sizeStyles =
      switch (size) {
      | `Large => [width(px(30)), height(px(30))]
      | `Medium => []
      };
    style([unsafe("strokeWidth", "1px"), ...sizeStyles]);
  };

  let upvoteIconActive = () =>
    style([unsafe("fill", Styles.useColor(`Primary) |> Colors.toString)]);
};

[@react.component]
let make = (~upvoteCount, ~isActive, ~onClick, ~size: size=`Medium) => {
  let upvoteBtnStyle = Classes.upvoteButton();
  let upvoteActiveIconStyle = Classes.upvoteIconActive();

  <Flex align=`center className=Classes.upvoteContainer>
    <Button
      className=upvoteBtnStyle
      size
      color=`Primary
      icon=true
      onClick={_ => onClick()}>
      <ReactFeather.UpvoteIcon
        className={Css.merge([
          Classes.upvoteIcon(size),
          isActive ? upvoteActiveIconStyle : "",
        ])}
      />
    </Button>
    <div className={Classes.upvoteCount(size)}>
      {React.string(upvoteCount |> string_of_int)}
    </div>
  </Flex>;
};
