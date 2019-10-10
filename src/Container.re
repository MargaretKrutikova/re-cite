module Styles = {
  let root =
    Css.(
      style([
        maxWidth(`px(600)),
        padding2(~h=`px(20), ~v=`px(0)),
        margin2(~v=`px(0), ~h=`auto),
      ])
    );
};

[@react.component]
let make = (~children, ~className="") => {
  <div className={Cn.make([Styles.root, className])}> children </div>;
};
