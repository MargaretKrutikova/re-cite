open DesignSystem;

module Classes = {
  open Css;

  let root =
    style([
      display(`flex),
      flexDirection(column),
      position(`relative),
      marginBottom(`xs |> Styles.space),
      width(pct(100.0)),
    ]);

  let focusBorder =
    style([
      position(`absolute),
      bottom(px(0)),
      left(pct(50.0)),
      width(px(0)),
      height(px(2)),
      transition(~duration=300, "all"), // TODO: design system
      backgroundColor(`Primary |> Styles.color),
    ]);

  let focusBorderVisible = [width(pct(100.0)), left(px(0))];

  let input =
    style([
      width(pct(100.0)),
      unsafe("appearance", "none"),
      margin(px(0)),
      borderRadius(px(0)),
      outlineWidth(px(0)),
      borderWidth(px(0)),
      backgroundColor(`InputBg |> Styles.color),
      borderBottom(px(1), `solid, `NeutralBorder |> Styles.color),
      transition(~duration=300, "all"),
      padding2(~v=`xs |> Styles.space, ~h=`xs |> Styles.space),
      focus([selector("~ ." ++ focusBorder, focusBorderVisible)]),
      ...Styles.font(`base),
    ]);

  let label =
    style([
      display(`block),
      marginBottom(`custom(1) |> Styles.space),
      color(`Label |> Styles.color),
      ...Styles.font(`xs),
    ]);
};

[@react.component]
let make =
    (
      ~value=?,
      ~className="",
      ~onChange=?,
      ~multiline=false,
      ~placeholder=?,
      ~label=?,
      ~type_=?,
    ) => {
  <div className={Emotion.cx([|Classes.root, className|])}>
    {label->Belt.Option.mapWithDefault(React.null, labelText =>
       <label className=Classes.label> {React.string(labelText)} </label>
     )}
    {multiline
       ? <textarea
           ?type_
           ?placeholder
           ?value
           ?onChange
           rows=3
           className=Classes.input
         />
       : <input ?type_ ?placeholder ?value ?onChange className=Classes.input />}
    <span className=Classes.focusBorder />
  </div>;
};
