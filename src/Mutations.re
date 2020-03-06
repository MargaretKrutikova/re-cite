module AddCitation = [%graphql
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
        added
        author {
          id
          name
        }
      }
    }
  }
|}
];

module UpdateCitation = [%graphql
  {|
mutation ($id: Int!, $text: String!, $collectionId: uuid!, $authorName: String!, $date: date!) {
  insert_citations(objects: {
    id: $id,
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
  },
  on_conflict:{
    constraint: citations_pkey,
    update_columns: [id, text, authorId, collectionId, added]
  }) {
    returning {
      id
      text
      added
      author {
        id
        name
      }
    }
  }
}
|}
];

module CreateCollection = [%graphql
  {|
  mutation ($name: String!, $slug: String!) {
    insert_collections(objects: {name: $name, slug: $slug}) {
      returning {
        id
        name
        slug
      }
    }
  }
  |}
];
