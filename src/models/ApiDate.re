type t = Js.Json.t;

let fromDate = date => date |> Js.Date.toISOString |> Js.Json.string;

let toDisplayString = date =>
  date
  ->Js.Json.decodeString
  ->Belt.Option.mapWithDefault("", str =>
      str |> Js.Date.fromString |> Js.Date.toLocaleString
    );

let dateFromString = dateStr => {
  let date = dateStr |> Js.Date.fromString;
  if (!Utils.isDateValid(date)) {
    None;
  } else {
    Some(date);
  };
};

let toDate = apiDate =>
  apiDate->Js.Json.decodeString->Belt.Option.flatMap(dateFromString);
