let regexFromCharacters = str =>
  str
  |> Js.String.split("")
  |> Js.Array.joinWith("|")
  |> Js.Re.fromStringWithFlags(~flags="g");

let replaceCharacters = (~characters, ~replacements, str) => {
  let regex = characters |> regexFromCharacters;

  str
  |> Js.String.unsafeReplaceBy0(regex, (match, _, _) =>
       switch (Js.String.indexOf(match, characters)) {
       | (-1) => ""
       | index => Js.String.charAt(index, replacements)
       }
     );
};

let make = str => {
  let diacritics = {j|àáâäæãåāăąçćčđďèéêëēėęěğǵḧîïíīįìłḿñńǹňôöòóœøōõṕŕřßśšşșťțûüùúūǘůűųẃẍÿýžźż|j};
  let replacements = {j|aaaaaaaaaacccddeeeeeeeegghiiiiiilmnnnnooooooooprrsssssttuuuuuuuuuwxyyzzz|j};

  let delimiterRegex = regexFromCharacters("·/_,:;");

  str
  |> Js.String.toLowerCase
  |> Js.String.trim
  |> replaceCharacters(~characters=diacritics, ~replacements)  // Replace diacritic marks
  |> Js.String.replaceByRe(delimiterRegex, "-")  // Replace delimiters with -
  |> Js.String.replaceByRe([%re "/\\s+/g"], "-")  // Replace spaces with -
  |> Js.String.replaceByRe([%re "/&/g"], "-and-")  // Replace & with 'and'
  |> Js.String.replaceByRe([%re "/[^\\w\\-]+/g"], "")  // Remove all non-word characters
  |> Js.String.replaceByRe([%re "/\\-\\-+/g"], "-")  // Replace multiple - with single -
  |> Js.String.replaceByRe([%re "/^-+/"], "")  // Trim - from start of text
  |> Js.String.replaceByRe([%re "/-+$/"], ""); // Trim - from end of text
};
