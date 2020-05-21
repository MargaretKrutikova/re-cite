CREATE OR REPLACE FUNCTION public.get_latest_citation
(collectionid uuid)
 RETURNS SETOF citations
 LANGUAGE sql
 STABLE
AS $function$

SELECT *
FROM citations
WHERE "collectionId" = collectionid
ORDER BY "id" DESC
LIMIT 1

$function$

CREATE
OR REPLACE
FUNCTION public.get_citations_after_id
(collectionid uuid, lastcitationid integer) RETURNS SETOF citations LANGUAGE sql STABLE AS $ function $
SELECT
  *
FROM
  citations
WHERE
  "collectionId" = collectionid
  AND "id" > lastcitationid
ORDER BY
  "id" DESC
$ function $
