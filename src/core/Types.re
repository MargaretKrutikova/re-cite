type author = {
  id: int,
  name: string,
};

type citation = {
  id: int,
  text: string,
  added: ApiDate.t,
  author,
  numberOfUpvotes: int,
  upvoteUserIds: array(string),
};

type collection = {
  id: Js.Json.t,
  name: string,
  slug: string,
  authors: array(author),
  citations: array(citation),
};
