// input with type date accepts yyyy-MM-dd
let prependZero = str => str |> Js.String.length < 2 ? "0" ++ str : str;

let floatToStr = value => string_of_int @@ Js.Math.floor @@ value;

let getMonth = date => (+.)(1.0) @@ Js.Date.getMonth @@ date;

let toDisplayDate = date => {
  let month = date |> getMonth |> floatToStr |> prependZero;
  let day = date |> Js.Date.getDate |> floatToStr |> prependZero;
  let year = date |> Js.Date.getFullYear |> floatToStr;

  year ++ "-" ++ month ++ "-" ++ day;
};

let toInputDateTimeFormat = date => {
  let month = date |> getMonth |> floatToStr |> prependZero;
  let day = date |> Js.Date.getDate |> floatToStr |> prependZero;
  let year = date |> Js.Date.getFullYear |> floatToStr;

  let hours = date |> Js.Date.getHours |> floatToStr |> prependZero;
  let minutes = date |> Js.Date.getMinutes |> floatToStr |> prependZero;

  year ++ "-" ++ month ++ "-" ++ day ++ "T" ++ hours ++ ":" ++ minutes;
};

let isDateValid = date => date |> Js.Date.toDateString !== "Invalid Date";

let isDateStringValid = dateStr =>
  dateStr |> Js.Date.fromString |> isDateValid;
