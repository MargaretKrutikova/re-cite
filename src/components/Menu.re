open DesignSystem;

let str = ReasonReact.string;

type alignType = [ | `Left | `Right | `Center];

module Styles = {
  open Css;

  let triangleWidthPx = 9;
  let alignShiftPx = 6;
  let optionsTopPx = Theme.space(`sm);
  let minWidthPx = 150;

  let getOptionsAlign = (align: alignType) =>
    switch (align) {
    | `Center => [
        left(pct(50.0)),
        transform(`translate((pct(-50.0), px(0)))),
      ]
    | `Left => [left(px(- alignShiftPx))]
    | `Right => [right(px(- alignShiftPx))]
    };

  let menu =
    style([
      position(relative),
      display(inlineFlex),
      flexDirection(column),
      userSelect(`none),
    ]);

  let optionsContainer = style([position(relative)]);

  let options = (align: alignType) =>
    merge([
      style([
        position(absolute),
        top(px(0)),
        minWidth(px(minWidthPx)),
        padding2(~h=px(0), ~v=`sm |> Styles.space),
        border(px(1), solid, `Border |> Styles.useColor),
        background(`BodyBg1 |> Styles.useColor),
        marginTop(px(optionsTopPx)),
        borderRadius(px(4)),
        boxShadow(
          Shadow.box(
            ~x=px(0),
            ~y=px(3),
            ~blur=px(12),
            Styles.useBoxShadow(),
          ),
        ),
        zIndex(1),
      ]),
      style(getOptionsAlign(align)),
    ]);

  let triangle = () =>
    merge([
      style([
        width(pct(100.0)),
        position(absolute),
        top(px(0)),
        marginTop(px(optionsTopPx + 1)),
        zIndex(2),
        before([
          position(absolute),
          left(pct(50.0)),
          transform(`translate((pct(-50.0), px(0)))),
          top(px(- triangleWidthPx * 2)),
          display(`inlineBlock),
          contentRule(""),
          border(px(triangleWidthPx), solid, `transparent),
          borderBottomColor(`Border |> Styles.useColor),
        ]),
        after([
          position(absolute),
          top(px(- (triangleWidthPx * 2 - 2))),
          left(`calc((`add, pct(50.0), px(0)))),
          transform(`translate((pct(-50.0), px(0)))),
          display(`inlineBlock),
          contentRule(""),
          border(px(triangleWidthPx - 1), solid, `transparent),
          borderBottomColor(`BodyBg1 |> Styles.useColor),
        ]),
      ]),
    ]);
};

type state = {isOpen: bool};

type action =
  | Open
  | Close
  | Toggle;

let reducer = (state, action) => {
  switch (action) {
  | Open => {isOpen: true}
  | Close => {isOpen: false}
  | Toggle => {isOpen: !state.isOpen}
  };
};

[@react.component]
let make = (~renderTrigger, ~renderOptions, ~align=`Center) => {
  let (state, dispatch) = React.useReducer(reducer, {isOpen: false});

  let menuRef = ClickOutside.use(_ => dispatch(Close));
  let toggleOpen = _ => dispatch(Toggle);

  let optionsStyle = Styles.options(align);
  let triangleStyles = Styles.triangle();

  <div className=Styles.menu ref={ReactDOMRe.Ref.domRef(menuRef)}>
    {renderTrigger(toggleOpen)}
    {state.isOpen
       ? <div className=Styles.optionsContainer>
           <div className=triangleStyles />
           <div className=optionsStyle> {renderOptions()} </div>
         </div>
       : ReasonReact.null}
  </div>;
};
