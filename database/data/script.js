import { gql, GraphQLClient } from "graphql-request";
import collections from "./collections.json";
import authors from "./authors.json";
import citations from "./citations.json";
import upvotes from "./citation_upvotes.json";

const insertCollections = gql`
  mutation InsertCollections($name: String, $slug: String, $id: uuid) {
    insert_collections(objects: { name: $name, slug: $slug, id: $id }) {
      affected_rows
      returning {
        name
        id
        slug
      }
    }
  }
`;

const insertAuthors = gql`
  mutation InsertAuthors($name: String, $collectionId: uuid, $id: Int) {
    insert_authors(
      objects: { name: $name, collectionId: $collectionId, id: $id }
    ) {
      affected_rows
      returning {
        id
        name
        collectionId
      }
    }
  }
`;

const insertCitations = gql`
  mutation InsertCitations(
    $authorId: Int
    $text: String
    $collectionId: uuid
    $id: Int
    $added: timestamptz
  ) {
    insert_citations(
      objects: {
        authorId: $authorId
        text: $text
        collectionId: $collectionId
        id: $id
        added: $added
      }
    ) {
      affected_rows
      returning {
        authorId
        id
        text
        added
        collectionId
      }
    }
  }
`;

const insertUpvotes = gql`
  mutation InsertCitationUpvotes($citationId: Int, $userId: String, $id: Int) {
    insert_citation_upvotes(
      objects: { citationId: $citationId, userId: $userId, id: $id }
    ) {
      affected_rows
      returning {
        citationId
        id
        userId
      }
    }
  }
`;

const main = async () => {
  const graphQLClient = new GraphQLClient(
    "https://sirseszwtdwfowwgxjcc.nhost.run/v1/graphql",
    {
      headers: {
        "x-hasura-admin-secret": "",
      },
    }
  );

  collections.forEach(async (element) => {
    const results = await graphQLClient.request(insertCollections, {
      id: element.id,
      name: element.name,
      slug: element.slug,
    });
  });

  authors.forEach(async (element) => {
    const results = await graphQLClient.request(insertAuthors, {
      id: element.id,
      collectionId: element.collectionId,
      name: element.name,
    });
  });

  citations.forEach(async (element) => {
    const results = await graphQLClient.request(insertCitations, {
      id: element.id,
      authorId: element.authorId,
      collectionId: element.collectionId,
      text: element.text,
      added: element.added,
    });
  });

  upvotes.forEach(async (element) => {
    const results = await graphQLClient.request(insertUpvotes, {
      id: element.id,
      userId: element.userId,
      citationId: element.citationId,
    });
  });
};

await main();
// run script: node --experimental-json-modules script.js
