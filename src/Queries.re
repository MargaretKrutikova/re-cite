open Types;

module GetCollection = [%graphql
  {|
  query($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) @bsRecord {
      id
      name
      slug
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

module GetAllCollectionSlugs = [%graphql
  {|
  query {
    collections {
      slug
    }
  }
|}
];
