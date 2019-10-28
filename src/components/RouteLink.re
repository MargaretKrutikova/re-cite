let shouldPreventDefault = e =>
  !ReactEvent.Mouse.metaKey(e) && !ReactEvent.Mouse.ctrlKey(e);

let handleClick = (href, event) =>
  if (!ReactEvent.Mouse.defaultPrevented(event)
      && shouldPreventDefault(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

[@react.component]
let make = (~href, ~children) => {
  <Link href onClick={handleClick(href)}> children </Link>;
};
