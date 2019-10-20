open Types;

let parseId = id => id->Js.Json.decodeString->Belt.Option.getWithDefault("");

module GetCollection = [%graphql
  {|
  query($collectionName: String!) {
    collections(where: {name: {_eq: $collectionName}}) @bsRecord {
      id @bsDecoder(fn: "parseId")
      name
      authors @bsRecord {
        name
        id
      }
      citations @bsRecord {
        id
        text
        added @bsDecoder(fn: "Js.Json.decodeString")
        author @bsRecord {
          name
        }
      }
    }
  }
|}
];
