let genFontSize = (~baseFontSize, ~fontScale, factor) =>
  fontScale ** factor |> ( *. )(baseFontSize |> float_of_int) |> int_of_float;
