open Types;

module GetCollection = [%graphql
  {|
  query($collectionName: String!) {
    collections(where: {name: {_eq: $collectionName}}) @bsRecord {
      id
      name
      authors @bsRecord {
        id
        name
      }
      citations(order_by: {added: desc}) @bsRecord {
        id
        text
        added @bsDecoder(fn: "Js.Json.decodeString")
        author @bsRecord {
          id
          name
        }
      }
    }
  }
|}
];
