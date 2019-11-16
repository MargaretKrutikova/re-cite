open Jest;
open Expect;

describe("Slugify", () => {
  test("Transforms to lowercase", () => {
    let input = "ABCDEF";
    let slug = "abcdef";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Trims whitespaces", () => {
    let input = "   abcdef     ";
    let slug = "abcdef";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Replaces diacritic characters correctly", () => {
    let input = {j|àáâäæãåāăąçćčđďèéêëēėęěğǵḧîïíīįìłḿñńǹňôöòóœøōõṕŕřßśšşșťțûüùúūǘůűųẃẍÿýžźż|j};
    let slug = {j|aaaaaaaaaacccddeeeeeeeegghiiiiiilmnnnnooooooooprrsssssttuuuuuuuuuwxyyzzz|j};

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Replaces delimiter symbols with -", () => {
    let input = {j|"a·b/c_d,e:f;g"|j};
    let slug = "a-b-c-d-e-f-g";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Replaces spaces with -", () => {
    let input = "aa bb          cc";
    let slug = "aa-bb-cc";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Replaces & with 'and'", () => {
    let input = "a&b";
    let slug = "a-and-b";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Removes all non-word characters", () => {
    let input = "a#!@$%^*()+='b";
    let slug = "ab";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Replaces multiple - with single -", () => {
    let input = "a-----b-c";
    let slug = "a-b-c";

    input |> Slug.make |> expect |> toBe(slug);
  });

  test("Trims - from start and end of text", () => {
    let input = "----abcdef------";
    let slug = "abcdef";

    input |> Slug.make |> expect |> toBe(slug);
  });
});
