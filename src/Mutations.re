module EditCitation = [%graphql
  {|
  mutation ($text: String!, $collectionId: uuid!, $authorName: String!, $date: date!) {
    insert_citations(objects: {
      text: $text,
      collectionId: $collectionId,
      added: $date,
      author: {
        data: {
          name: $authorName,
          collectionId: $collectionId,
        },
        on_conflict: {
          constraint: authors_name_collectionId_key,
          update_columns: name
        }
      }
    }) {
      returning {
        id
        text
        author {
          id
          name
        }
      }
    }
  }
|}
];
