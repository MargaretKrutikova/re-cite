type t = Js.Json.t;

let fromDate = date => date |> Js.Date.toISOString |> Js.Json.string;

let removeSeconds = dateStr =>
  dateStr
  |> Js.String.substring(~from=0, ~to_=(dateStr |> Js.String.length) - 3);

let toDisplayStringWithTime = date =>
  date
  ->Js.Json.decodeString
  ->Belt.Option.mapWithDefault("", str =>
      str |> Js.Date.fromString |> Js.Date.toLocaleString |> removeSeconds
    );

let toDisplayString = date =>
  date
  ->Js.Json.decodeString
  ->Belt.Option.mapWithDefault("", str =>
      str |> Js.Date.fromString |> DateUtils.toDisplayDate
    );

let dateFromString = dateStr => {
  let date = dateStr |> Js.Date.fromString;
  if (!DateUtils.isDateValid(date)) {
    None;
  } else {
    Some(date);
  };
};

let toDate = apiDate =>
  apiDate->Js.Json.decodeString->Belt.Option.flatMap(dateFromString);
