type collectionRoute =
  | Citations;

type t =
  | Home
  | Collection(string, collectionRoute)
  | NotFound;

let fromUrl =
  fun
  | [] => Home
  | [collectionName, "citations"] => Collection(collectionName, Citations)
  | _ => NotFound;

let toUrl =
  fun
  | Home => "/"
  | Collection(collectionName, Citations) =>
    "/" ++ collectionName ++ "/citations"
  | NotFound => "/404";

let push = route => route |> toUrl |> ReasonReactRouter.push;
