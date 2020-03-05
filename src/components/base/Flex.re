[@react.component]
let make =
    (
      ~align=`stretch,
      ~justify=`stretch,
      ~className="",
      ~direction as dr=`row,
      ~children,
    ) => {
  let styles =
    Css.(
      style([
        display(`flex),
        alignItems(align),
        justifyContent(justify),
        flexDirection(dr),
      ])
    );
  <div className={Css.merge([styles, className])}> children </div>;
};
