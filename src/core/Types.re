type author = {
  id: int,
  name: string,
};

type citation = {
  id: int,
  text: string,
  added: option(string),
  author,
  numberOfUpvotes: int,
  hasUserUpvoted: bool,
};

type collection = {
  id: Js.Json.t,
  name: string,
  slug: string,
  authors: array(author),
  citations: array(citation),
};
