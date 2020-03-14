CREATE OR REPLACE FUNCTION get_random_citation
(collectionid uuid) 
RETURNS SETOF citations
LANGUAGE sql STABLE
AS $$

SELECT id, text, "authorId", "collectionId", added
FROM (
      SELECT *, ROW_NUMBER () OVER ()
    FROM citations
    WHERE "collectionId"=collectionid
    ) citations_with_rows
WHERE "collectionId"=collectionid AND ROW_NUMBER =
   (
        SELECT floor(random() * (
            SELECT COUNT(*)
        FROM citations
        WHERE "collectionId"=collectionid
        ) + 1)
   )

$$;
