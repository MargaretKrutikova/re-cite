type citation = {
  id: int,
  text: string,
  added: option(string),
  author: citationAuthor,
}
and citationAuthor = {name: string};

type author = {
  id: int,
  name: string,
};

type collection = {
  id: string,
  name: string,
  authors: array(author),
  citations: array(citation),
};
