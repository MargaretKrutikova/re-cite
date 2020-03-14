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
|}];
