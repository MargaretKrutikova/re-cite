type author = {
  id: int,
  name: string,
};

type citation = {
  id: int,
  text: string,
  added: option(string),
  author,
};

type collection = {
  id: Js.Json.t,
  name: string,
  authors: array(author),
  citations: array(citation),
};
