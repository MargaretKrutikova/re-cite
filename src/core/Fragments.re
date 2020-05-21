module CitationFragment = [%graphql
  {|
  fragment Citation on citations {
      id
      text
      added
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
