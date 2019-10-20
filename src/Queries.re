open Types;

module GetAllCitations = [%graphql
  {|
    query($collectionName: String!) {
      citations(where: {collection: {name: {_eq: $collectionName}}}) @bsRecord {
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
