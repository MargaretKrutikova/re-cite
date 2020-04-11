[@bs.val] external location: string = "window.location.origin";

type collectionRoute =
  | Citations
  | RandomCitation
  | CitationById(string);

type t =
  | Home
  | CreateCollection
  | Collection(string, collectionRoute)
  | NotFound;

let fromUrl =
  fun
  | [] => Home
  | ["collections", "new"] => CreateCollection
  | [slug, "citations"] => Collection(slug, Citations)
  | [slug, "citation", id] => Collection(slug, CitationById(id))
  | [slug, "random-citation"] => Collection(slug, RandomCitation)
  | _ => NotFound;

let toUrl =
  fun
  | Home => "/"
  | CreateCollection => "/collections/new"
  | Collection(slug, Citations) => "/" ++ slug ++ "/citations"
  | Collection(slug, CitationById(id)) => "/" ++ slug ++ "/citation/" ++ id
  | Collection(slug, RandomCitation) => "/" ++ slug ++ "/random-citation"
  | NotFound => "/404";

let toAbsoluteUrl = url => location ++ url;

let push = route => route |> toUrl |> ReasonReactRouter.push;

let isActive = (url: ReasonReactRouter.url, route) => {
  let activeRoute = url.path |> fromUrl;
  route == activeRoute;
};
