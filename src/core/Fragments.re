module CitationFragment = [%graphql
  {|
  fragment Citation on citations {
      id
      text
      added @bsDecoder(fn: "Js.Json.decodeString")
      author  {
        id
        name
      }
      upvotes_aggregate {
        aggregate {
          count
        }
      }
      upvotes {
        userId
      }
    }
|}
];
