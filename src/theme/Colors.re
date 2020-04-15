module DarkBlue = {
  let main = `rgb((74, 85, 104));

  let dark1 = `rgb((53, 61, 74));
  let dark2 = `rgb((39, 44, 54));
  let dark3 = `rgb((32, 36, 44));

  let light1 = `rgb((102, 117, 144));
  let light2 = `rgb((130, 144, 166));
  let light3 = `rgb((150, 161, 181));
  let light4 = `rgb((180, 188, 202));
  let light5 = `rgb((240, 241, 244));
};

module Green = {
  let main = `rgb((27, 179, 143));
  let dark1 = `rgb((18, 124, 99));

  let light1 = `rgb((32, 209, 167));
};

module White = {
  let main = `rgb((255, 255, 255));
};

module Red = {
  let main = `rgb((244, 67, 54));
};

module Yellow = {
  let main = `rgb((255, 152, 15));
};

module Gray = {
  let main = `rgb((200, 200, 200));

  let light1 = `rgb((220, 220, 220));
  let light2 = `rgb((242, 242, 242));

  let dark1 = `rgb((164, 164, 164));
  let dark2 = `rgb((120, 120, 120));
};

module Overlay = {
  let light = `rgba((255, 255, 255, 0.2));
  let dark = `rgba((0, 0, 0, 0.2));
};

let toString =
  fun
  | `rgb(r, g, b) =>
    "rgba("
    ++ string_of_int(r)
    ++ ", "
    ++ string_of_int(g)
    ++ ","
    ++ string_of_int(b)
    ++ ")"

  | `rgba(r, g, b, a) =>
    "rgba("
    ++ string_of_int(r)
    ++ ", "
    ++ string_of_int(g)
    ++ ","
    ++ string_of_int(b)
    ++ ","
    ++ Js.Float.toString(a)
    ++ ")";
