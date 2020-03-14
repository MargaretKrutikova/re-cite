CREATE OR REPLACE FUNCTION public.get_random_citation_by_slug
(collectionslug text)
 RETURNS SETOF citations
 LANGUAGE sql
 STABLE
AS $function$

SELECT "get_random_citation"(
       (SELECT id
  FROM collections
  WHERE collections.slug = collectionSlug
        LIMIT
1)
    );

$function$
