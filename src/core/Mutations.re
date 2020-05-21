open Fragments;

module AddCitation = [%graphql
  {|
  mutation ($text: String!, $collectionId: uuid!, $authorName: String!, $date: timestamptz!) {
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
mutation ($id: Int!, $text: String!, $collectionId: uuid!, $authorName: String!, $date: timestamptz!) {
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

module UpdateCollection = [%graphql
  {|
  mutation ($collectionId: uuid!, $name: String!, $slug: String!) {
    update_collections(where: {id: {_eq: $collectionId}}, _set: {name: $name, slug: $slug}) {
      returning {
        id
        name
        slug
      }
    }
  }
  |}
];

module UpvoteCitation = [%graphql
  {|
  mutation UpvoteCitation($citationId: Int!, $userId: String!) {
    insert_citation_upvotes(objects: {citationId: $citationId, userId: $userId},
    on_conflict: {
      constraint: citation_upvotes_userId_citationId_key,
      update_columns: userId
    }) {
      returning {
        citation {
          ...CitationFragment.Citation
        }
      }
    }
  }
|}
];

module RemoveUpvoteCitation = [%graphql
  {|
  mutation RemoveUpvoteCitation($citationId: Int!, $userId: String!) {
    delete_citation_upvotes(where: {_and: {citationId: {_eq: $citationId}, userId: {_eq: $userId}}}) {
      returning {
        citation {
          ...CitationFragment.Citation
        }
      }
    }
  }
|}
];
