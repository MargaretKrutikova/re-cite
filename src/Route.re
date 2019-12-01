[@bs.val] external location: string = "window.location.origin";

type collectionRoute =
  | Citations
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
  | _ => NotFound;

let toUrl =
  fun
  | Home => "/"
  | CreateCollection => "/collections/new"
  | Collection(collectionName, Citations) =>
    "/" ++ collectionName ++ "/citations"
  | Collection(collectionName, CitationById(id)) =>
    "/" ++ collectionName ++ "/citation/" ++ id
  | NotFound => "/404";

let toAbsoluteUrl = url => location ++ url;

let push = route => route |> toUrl |> ReasonReactRouter.push;
