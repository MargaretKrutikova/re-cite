open Jest;
open Expect;
open! Expect.Operators;

describe("Utils", () =>
  test("toInputDateFormat returns date in format YYYY-MM-dd", () => {
    let inputs = [|"2017/10/09", "2000/01/23", "1990/12/30"|];
    let expected = [|"2017-10-09", "2000-01-23", "1990-12-30"|];

    let actual =
      inputs->Belt.Array.map(d =>
        Utils.toInputDateFormat @@ Js.Date.fromString @@ d
      );
    // deep equal
    expect(actual) == expected;
  })
);
