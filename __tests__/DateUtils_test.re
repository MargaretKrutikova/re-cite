open Jest;
open Expect;
open! Expect.Operators;

describe("DateUtils", () =>
  test("toInputDateFormat returns date in format yyyy-MM-ddThh:mm", () => {
    let inputs = [|
      "2020-07-16T17:20:30",
      "2000-01-23T03:00:30",
      "1990-12-02T13:09:30",
    |];
    let expected = [|
      "2020-07-16T17:20",
      "2000-01-23T03:00",
      "1990-12-02T13:09",
    |];

    let actual =
      inputs->Belt.Array.map(d =>
        DateUtils.toInputDateTimeFormat @@ Js.Date.fromString @@ d
      );
    // deep equal
    expect(actual) == expected;
  })
);
