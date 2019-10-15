open Webapi.Dom;

let getBodyClasses = () =>
  (document |> Document.asHtmlDocument)
  ->Belt.Option.flatMap(doc => doc |> HtmlDocument.body)
  ->Belt.Option.flatMap(body => Some(body |> Element.classList));

let hasClass = (className, classes) =>
  classes |> DomTokenList.contains(className);

let addBodyClass = className => {
  switch (getBodyClasses()) {
  | Some(classes) =>
    if (!(classes |> hasClass(className))) {
      classes |> DomTokenList.add(className);
    }
  | _ => ignore()
  };
};

let removeBodyClass = className => {
  switch (getBodyClasses()) {
  | Some(classes) =>
    if (classes |> hasClass(className)) {
      classes |> DomTokenList.remove(className);
    }
  | _ => ignore()
  };
};
