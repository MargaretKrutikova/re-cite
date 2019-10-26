[@react.component]
let make = (~align=`stretch, ~justify=`stretch, ~className="", ~children) => {
  let styles =
    Css.(
      style([display(`flex), alignItems(align), justifyContent(justify)])
    );
  <div className={Css.merge([styles, className])}> children </div>;
};
