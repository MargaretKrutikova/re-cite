module DateDecoder = {
  let parse = Js.Json.decodeString;
  let serialize = (val_: Js.Json.t) => val_ |> Obj.magic;
  type t = string;
};

[%graphql
  {|
    fragment Citation on citations {
      id
      text
      added @ppxDecoder(module: "DateDecoder")
      author {
        id
        name
      }
    }

  fragment CitationTest on citations @argumentDefinitions(loggedInUserId: {type: "String!"}) {
      id
      text
      added
      author {
        id
        name
      }
      upvotes(where: {userId: {_eq: $loggedInUserId}}) {
        userId
      }
      upvotes_aggregate {
        aggregate {
          count
        }
      }
  }

  query GetCitationsTest($slug: String!, $loggedInUserId: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      citations(order_by: {added: desc, id: desc}) {
        ...CitationTest @arguments(loggedInUserId: $loggedInUserId)
      }
    }
  }

  query GetCitationById ($slug: String!, $id: Int!) {
    citations(where: {id: {_eq: $id}, collection: {slug: {_eq: $slug}}}) {
      ...Citation
    }
  }

  query GetCitations($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      citations(order_by: {added: desc, id: desc}) {
        ...Citation
      }
    }
  }

  query GetRandomCitation($slug: String!) {
    get_random_citation_by_slug(args: {collectionslug: $slug}) {
      ... Citation
    }
  }

  query GetCollectionBySlug($slug: String!) {
    collections(where: {slug: {_eq: $slug}}) {
      id
      slug
      authors  {
        id
        name
      }
    }
  }

  query GetAllCollectionSlugs{
    collections {
      slug
    }
  }
|};
  {inline: true}
];
