type collectionRoute =
  | Citations;

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
  | _ => NotFound;

let toUrl =
  fun
  | Home => "/"
  | CreateCollection => "/collections/new"
  | Collection(collectionName, Citations) =>
    "/" ++ collectionName ++ "/citations"
  | NotFound => "/404";

let push = route => route |> toUrl |> ReasonReactRouter.push;
