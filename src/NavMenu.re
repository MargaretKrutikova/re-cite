type menuItem = {
  route: Route.t,
  desktopText: string,
  mobileText: string,
};

type t = array(menuItem);

let getMenuItems = (slug): array(menuItem) => [|
  {
    desktopText: "All",
    mobileText: "All citations",
    route: Route.Collection(slug, Citations),
  },
  {
    desktopText: "Random",
    mobileText: "Random citation",
    route: Route.Collection(slug, RandomCitation),
  },
|];
