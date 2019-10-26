open DesignSystem;

module Classes = {
  open Css;

  let root =
    style([
      display(`flex),
      flexDirection(column),
      position(`relative),
      marginBottom(`sm |> Styles.space),
      width(pct(100.0)),
    ]);

  let input =
    style([
      width(pct(100.0)),
      unsafe("appearance", "none"),
      margin(px(0)),
      Styles.borderRadius(`base),
      outlineWidth(px(0)),
      borderWidth(px(0)),
      boxSizing(`borderBox),
      backgroundColor(`InputBg |> Styles.color),
      color(`PrimaryText |> Styles.color),
      border(px(1), `solid, `Neutral |> Styles.color),
      transition(~duration=300, "all"),
      padding2(~v=`sm |> Styles.space, ~h=`sm |> Styles.space),
      focus([borderColor(`Primary |> Styles.color)]),
      ...Styles.font(`base),
    ]);

  let label =
    style([
      display(`block),
      marginBottom(`custom(1) |> Styles.space),
      color(`SecondaryText |> Styles.color),
      ...Styles.font(`sm),
    ]);
};

module InputContainer = {
  [@react.component]
  let make = (~label=?, ~className="", ~children) => {
    <div className={Css.merge([Classes.root, className])}>
      {label->Belt.Option.mapWithDefault(React.null, labelText =>
         <label className=Classes.label> {React.string(labelText)} </label>
       )}
      children
    </div>;
  };
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
  <InputContainer ?label className>
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
  </InputContainer>;
};

module NativeSelect = {
  [@react.component]
  let make =
      (
        ~value=?,
        ~className="",
        ~onChange=?,
        ~multiline=false,
        ~placeholder=?,
        ~label=?,
        ~children,
      ) => {
    <InputContainer ?label className>
      <select ?value ?onChange ?placeholder className=Classes.input>
        children
      </select>
    </InputContainer>;
  };
};
