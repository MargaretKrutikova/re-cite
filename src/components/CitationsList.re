let perPage = 20;

module Document = {
  type element;
  let window: element = [%bs.raw "window"];
  let innerHeight: int = [%bs.raw "window.innerHeight"];

  [@bs.send.pipe: element]
  external addEventListener: (string, unit => unit) => unit =
    "addEventListener";

  [@bs.send.pipe: element]
  external removeEventListener: (string, unit => unit) => unit =
    "removeEventListener";
};

let getDocumentElement = () =>
  Webapi.Dom.document
  |> Webapi.Dom.Document.documentElement
  |> Webapi.Dom.HtmlElement.ofElement;

let getOffsetHeight = () => {
  switch (getDocumentElement()) {
  | Some(el) => Webapi.Dom.HtmlElement.offsetHeight(el)
  | None => 0
  };
};

let getScrollTop = () => {
  switch (getDocumentElement()) {
  | Some(el) => Webapi.Dom.HtmlElement.scrollTop(el)
  | None => 0.0
  };
};

let isNearBottom = () => {
  let scrolledFromTop =
    (Document.innerHeight |> float_of_int) +. getScrollTop();
  (getOffsetHeight() |> float_of_int) -. scrolledFromTop < 100.0;
};

[@react.component]
let make = (~citations, ~slug, ~onEdit, ~fetchMore) => {
  React.useEffect1(
    () => {
      let handleScroll = () =>
        if (isNearBottom()) {
          fetchMore();
        };
      Document.window |> Document.addEventListener("scroll", handleScroll);
      Some(
        () =>
          Document.window
          |> Document.removeEventListener("scroll", handleScroll),
      );
    },
    [|fetchMore|]
  );

  citations
  ->Belt.Array.map(citationObj => Queries.toCitation(citationObj))
  ->Belt.Array.map(citation =>
      <CitationListItem
        slug
        key={citation.id |> string_of_int}
        text={citation.text}
        author={citation.author.name}
        date={citation.added |> ApiDate.toDisplayString}
        id={citation.id}
        upvoteUserIds={citation.upvoteUserIds}
        upvoteCount={citation.numberOfUpvotes}
        onEdit={() => onEdit(citation)}
      />
    )
  |> React.array;
};
