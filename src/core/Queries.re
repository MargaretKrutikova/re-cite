open Types;
open Fragments;

module GetCitationById = [%graphql
  {|
  query ($slug: String!, $id: Int!) {
    citations(where: {id: {_eq: $id}, collection: {slug: {_eq: $slug}}}) {
      ...CitationFragment.Citation
    }
  }
|}
];

module GetCitations = [%graphql
  {|
  query($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      citations(order_by: {added: desc, id: desc}) {
        ...CitationFragment.Citation
      }
    }
  }
|}
];

module GetRandomCitation = [%graphql
  {|
  query($slug: String!) {
    get_random_citation_by_slug(args: {collectionslug: $slug}) {
      ...CitationFragment.Citation
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
