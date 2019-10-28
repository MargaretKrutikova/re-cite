// input with type date accepts yyyy-MM-dd
let prependZero = str => str |> Js.String.length < 2 ? "0" ++ str : str;

let toInputDateFormat = date => {
  let str = value => string_of_int @@ Js.Math.floor @@ value;

  let month = date |> Js.Date.getMonth |> (+.)(1.0) |> str |> prependZero;
  let day = date |> Js.Date.getDate |> str |> prependZero;
  let year = date |> Js.Date.getFullYear |> str;

  year ++ "-" ++ month ++ "-" ++ day;
};

let getInputValue = (e): string => ReactEvent.Form.target(e)##value;

let slugify = (str: string) => {
  let a = {j|àáâäæãåāăąçćčđďèéêëēėęěğǵḧîïíīįìłḿñńǹňôöòóœøōõṕŕřßśšşșťțûüùúūǘůűųẃẍÿýžźż·/_,:;|j};
  let b = {j|aaaaaaaaaacccddeeeeeeeegghiiiiiilmnnnnooooooooprrsssssttuuuuuuuuuwxyyzzz------|j};

  let replaceSpecialCharacters: (string, string, string) => string = [%bs.raw
    {|
    function (a, b, str) {
      const p = new RegExp(a.split('').join('|'), 'g');
      return str.replace(p, c => b.charAt(a.indexOf(c)));
    } |}
  ];

  str
  |> Js.String.toLowerCase
  |> Js.String.trim
  |> replaceSpecialCharacters(a, b)
  |> Js.String.replaceByRe([%re "/\\s+/g"], "-")  // Replace spaces with -
  |> Js.String.replaceByRe([%re "/&/g"], "-and-")  // Replace & with 'and'
  |> Js.String.replaceByRe([%re "/[^\\w\\-]+/g"], "")  // Remove all non-word characters
  |> Js.String.replaceByRe([%re "/\\-\\-+/g"], "-")  // Replace multiple - with single -
  |> Js.String.replaceByRe([%re "/^-+/"], "")  // Trim - from start of text
  |> Js.String.replaceByRe([%re "/-+$/"], ""); // Trim - from end of text
};
