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
