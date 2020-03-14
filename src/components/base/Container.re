open DesignSystem;

module Styles = {
  let root =
    Css.(
      style([
        maxWidth(px(650)),
        margin2(~v=px(0), ~h=`auto),
        media(Breakpoint.up(`sm), Styles.paddingH(`md)),
        ...Styles.paddingH(`sm),
      ])
    );
};

[@react.component]
let make = (~children, ~className="") => {
  <div className={Css.merge([Styles.root, className])}> children </div>;
};
