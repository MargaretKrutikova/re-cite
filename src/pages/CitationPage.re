open Types;
open DesignSystem;

let str = React.string;

module GetCitationById = [%graphql
  {|
  query ($slug: String!, $id: Int!) {
    citations(where: {id: {_eq: $id}, collection: {slug: {_eq: $slug}}}) @bsRecord {
      id
      text
      added @bsDecoder(fn: "Js.Json.decodeString")
      author @bsRecord {
        id
        name
      }
    }
  }
|}
];

module PageQuery = ReasonApolloHooks.Query.Make(GetCitationById);

module Classes = {
  open Css;

  let bigQuote = () =>
    style([
      borderLeft(`xxs |> Styles.space, `solid, `Primary |> Styles.useColor),
      marginBottom(`xl |> Styles.space),
      paddingLeft(`lg |> Styles.space),
      marginTop(`lg |> Styles.space),
      media(
        Breakpoint.up(`sm),
        [
          marginBottom(`xxl |> Styles.space),
          paddingLeft(`xl |> Styles.space),
        ],
      ),
    ]);
  let citation = () =>
    style([color(`SecondaryText |> Styles.useColor), ...Styles.font(`md)]);
};

module BigCitation = {
  [@react.component]
  let make = (~citation) => {
    <div className={Classes.bigQuote()}>
      <Heading level=`h2> {str(citation.text)} </Heading>
      <div className={Classes.citation()}> {str(citation.author.name)} </div>
    </div>;
  };
};

[@react.component]
let make = (~slug, ~id) => {
  let variables = GetCitationById.make(~slug, ~id, ())##variables;
  let (simple, _) = PageQuery.use(~variables, ());

  switch (simple) {
  | NoData => React.null
  | Error(e) =>
    Js.log(e);
    <p> {React.string("Error")} </p>;
  | Loading => <p> {React.string("Loading...")} </p>
  | Data(data) =>
    switch (data##citations) {
    | [||] => <Text> {React.string("No citation found!")} </Text>
    | [|citation|] => <BigCitation citation />
    | _ => React.string("Multiple citations exist under the same id")
    }
  };
};
