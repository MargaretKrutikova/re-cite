type t = [ | `sm | `md | `lg];

let toPx = (bp: t) =>
  switch (bp) {
  | `sm => 600
  | `md => 960
  | `lg => 1280
  };

let up = (bp: t) => "(min-width: " ++ string_of_int(toPx(bp)) ++ "px)";
let down = (bp: t) => "(max-width: " ++ string_of_int(toPx(bp)) ++ "px)";
