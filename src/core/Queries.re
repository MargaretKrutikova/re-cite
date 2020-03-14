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
