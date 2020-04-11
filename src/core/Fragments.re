open Types;

module CitationFragment = [%graphql
  {|
  fragment Citation on citations @bsRecord {
    id
      text
      added @bsDecoder(fn: "Js.Json.decodeString")
      author @bsRecord {
        id
        name
      }
    }
|}
];

// module CitationFragment2 = [%graphql
//   {|
//   fragment Citation on citations @argumentDefinitions(loggedInUserId: {type: "Int"}) {
//       id
//       text
//       added @bsDecoder(fn: "Js.Json.decodeString")
//       author {
//         id
//         name
//       }
//       upvotes(where: {userId: {_eq: $loggedInUserId}}) {
//         userId
//       }
//       upvotes_aggregate {
//         aggregate {
//           count
//         }
//       }
//     }
// |}
// ];
