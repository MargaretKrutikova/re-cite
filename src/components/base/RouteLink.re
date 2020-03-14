let shouldPreventDefault = e =>
  !ReactEvent.Mouse.metaKey(e) && !ReactEvent.Mouse.ctrlKey(e);

let handleClick = (href, event) =>
  if (!ReactEvent.Mouse.defaultPrevented(event)
      && shouldPreventDefault(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

[@react.component]
let make = (~href, ~variant=`Link, ~color=`Primary, ~className="", ~children) => {
  <Link href variant color className onClick={handleClick(href)}>
    children
  </Link>;
};
