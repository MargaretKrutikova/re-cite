open Types;
open Fragments;

module GetCitationById = [%graphql
  {|
  query ($slug: String!, $id: Int!, $loggedInUserId: String) {
    citations(where: {id: {_eq: $id}, collection: {slug: {_eq: $slug}}}) {
      ...CitationFragment.Citation @bsField(name: "base")

      upvotes(where: {userId: {_eq: $loggedInUserId}}) {
        userId
      }
    }
  }
|}
];

module GetCitations = [%graphql
  {|
  query($slug: String!, $loggedInUserId: String) {
    collections(where: {slug: {_eq: $slug}}) {
      citations(order_by: {added: desc, id: desc}) {
         ...CitationFragment.Citation @bsField(name: "base")

        upvotes(where: {userId: {_eq: $loggedInUserId}}) {
          userId
        }
      }
    }
  }
|}
];

module GetRandomCitation = [%graphql
  {|
  query($slug: String!, $loggedInUserId: String) {
    get_random_citation_by_slug(args: {collectionslug: $slug}) {
       ...CitationFragment.Citation @bsField(name: "base")

        upvotes(where: {userId: {_eq: $loggedInUserId}}) {
          userId
        }
    }
  }
|}
];

module GetCollectionBySlug = [%graphql
  {|
  query($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      id
      slug
      authors @bsRecord {
        id
        name
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

let toCitation = (data): Types.citation => {
  let base = data##base;
  let numberOfUpvotes =
    base##upvotes_aggregate##aggregate
    ->Belt.Option.flatMap(d => d##count)
    ->Belt.Option.getWithDefault(0);

  let hasUserUpvoted = data##upvotes->Belt.Array.length > 0;

  {
    id: base##id,
    text: base##text,
    added: base##added,
    author: {
      id: base##author##id,
      name: base##author##name,
    },
    numberOfUpvotes,
    hasUserUpvoted,
  };
};
