// input with type date accepts yyyy-MM-dd
let prependZero = str => str |> Js.String.length < 2 ? "0" ++ str : str;

let toInputDateFormat = date => {
  let str = value => string_of_int @@ Js.Math.floor @@ value;

  let month = date |> Js.Date.getMonth |> str |> prependZero;
  let day = date |> Js.Date.getDate |> str |> prependZero;
  let year = date |> Js.Date.getFullYear |> str;

  year ++ "-" ++ month ++ "-" ++ day;
};

let getInputValue = (e): string => ReactEvent.Form.target(e)##value;
