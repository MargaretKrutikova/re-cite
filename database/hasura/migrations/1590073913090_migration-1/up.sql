CREATE TABLE public.citations
(
    id integer NOT NULL,
    text text NOT NULL,
    "authorId" integer NOT NULL,
    "collectionId" uuid NOT NULL,
    added timestamp
    with time zone DEFAULT now
    () NOT NULL
);

    CREATE TABLE public.authors
    (
        id integer NOT NULL,
        name text NOT NULL,
        "collectionId" uuid NOT NULL
    );
    CREATE SEQUENCE public.authors_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
    ALTER SEQUENCE public.authors_id_seq
    OWNED BY public.authors.id;
    CREATE TABLE public.citation_upvotes
    (
        id integer NOT NULL,
        "userId" text NOT NULL,
        "citationId" integer NOT NULL
    );
    CREATE SEQUENCE public.citation_upvotes_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
    ALTER SEQUENCE public.citation_upvotes_id_seq
    OWNED BY public.citation_upvotes.id;
    CREATE SEQUENCE public."citations_authorId_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
    ALTER SEQUENCE public."citations_authorId_seq"
    OWNED BY public.citations."authorId";
    CREATE SEQUENCE public.citations_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
    ALTER SEQUENCE public.citations_id_seq
    OWNED BY public.citations.id;
    CREATE TABLE public.collections
    (
        name text NOT NULL,
        id uuid DEFAULT public.gen_random_uuid() NOT NULL,
        slug text NOT NULL
    );
    CREATE TABLE public.test
    (
        id integer NOT NULL,
        date time
        with time zone DEFAULT now
        () NOT NULL,
    date2 timestamp without time zone DEFAULT now
        () NOT NULL
);
        CREATE SEQUENCE public.test_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
        ALTER SEQUENCE public.test_id_seq
        OWNED BY public.test.id;
        CREATE TABLE public.users
        (
            id uuid NOT NULL,
            "externalUserId" text NOT NULL
        );
        ALTER TABLE ONLY public.authors
        ALTER COLUMN id
        SET
        DEFAULT nextval
        ('public.authors_id_seq'::regclass);
        ALTER TABLE ONLY public.citation_upvotes
        ALTER COLUMN id
        SET
        DEFAULT nextval
        ('public.citation_upvotes_id_seq'::regclass);
        ALTER TABLE ONLY public.citations
        ALTER COLUMN id
        SET
        DEFAULT nextval
        ('public.citations_id_seq'::regclass);
        ALTER TABLE ONLY public.test
        ALTER COLUMN id
        SET
        DEFAULT nextval
        ('public.test_id_seq'::regclass);
        ALTER TABLE ONLY public.authors
        ADD CONSTRAINT "authors_name_collectionId_key" UNIQUE
        (name, "collectionId");
        ALTER TABLE ONLY public.authors
        ADD CONSTRAINT authors_pkey PRIMARY KEY
        (id);
        ALTER TABLE ONLY public.citation_upvotes
        ADD CONSTRAINT citation_upvotes_pkey PRIMARY KEY
        (id);
        ALTER TABLE ONLY public.citation_upvotes
        ADD CONSTRAINT "citation_upvotes_userId_citationId_key" UNIQUE
        ("userId", "citationId");
        ALTER TABLE ONLY public.citations
        ADD CONSTRAINT citations_pkey PRIMARY KEY
        (id);
        ALTER TABLE ONLY public.collections
        ADD CONSTRAINT collections_name_key UNIQUE
        (name);
        ALTER TABLE ONLY public.collections
        ADD CONSTRAINT collections_pkey PRIMARY KEY
        (id);
        ALTER TABLE ONLY public.collections
        ADD CONSTRAINT collections_slug_key UNIQUE
        (slug);
        ALTER TABLE ONLY public.test
        ADD CONSTRAINT test_pkey PRIMARY KEY
        (id);
        ALTER TABLE ONLY public.users
        ADD CONSTRAINT "users_externalUserId_key" UNIQUE
        ("externalUserId");
        ALTER TABLE ONLY public.users
        ADD CONSTRAINT users_pkey PRIMARY KEY
        (id);
        ALTER TABLE ONLY public.authors
        ADD CONSTRAINT "authors_collectionId_fkey" FOREIGN KEY
        ("collectionId") REFERENCES public.collections
        (id) ON
        UPDATE RESTRICT ON
        DELETE RESTRICT;
        ALTER TABLE ONLY public.citation_upvotes
        ADD CONSTRAINT "citation_upvotes_citationId_fkey" FOREIGN KEY
        ("citationId") REFERENCES public.citations
        (id) ON
        UPDATE RESTRICT ON
        DELETE RESTRICT;
        ALTER TABLE ONLY public.citations
        ADD CONSTRAINT "citations_authorId_fkey" FOREIGN KEY
        ("authorId") REFERENCES public.authors
        (id) ON
        UPDATE CASCADE ON
        DELETE CASCADE;
        ALTER TABLE ONLY public.citations
        ADD CONSTRAINT "citations_collectionId_fkey" FOREIGN KEY
        ("collectionId") REFERENCES public.collections
        (id) ON
        UPDATE CASCADE ON
        DELETE CASCADE;

        CREATE FUNCTION public.get_citations_after_id(collectionid uuid, lastcitationid integer) RETURNS SETOF public.citations
    LANGUAGE sql STABLE
    AS $$
        SELECT
            *
        FROM
            citations
        WHERE
  "collectionId" = collectionid AND "id" > lastcitationid
        ORDER BY
  "id" DESC
        $$;
        CREATE FUNCTION public.get_latest_citation(collectionid uuid) RETURNS SETOF public.citations
    LANGUAGE sql STABLE
    AS $$
        SELECT *
        FROM citations
        WHERE "collectionId" = collectionid
        ORDER BY "id" DESC
LIMIT 1
$$;
CREATE FUNCTION public.get_random_citation
        (collectionid uuid) RETURNS SETOF public.citations
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
        CREATE FUNCTION public.get_random_citation_by_slug(collectionslug text) RETURNS SETOF public.citations
    LANGUAGE sql STABLE
    AS $$
        SELECT "get_random_citation"(
       (SELECT id
            FROM collections
            WHERE collections.slug = collectionSlug
        LIMIT
        1)
    );
$$;
        CREATE FUNCTION public.random_between(low integer, high integer) RETURNS integer
    LANGUAGE plpgsql STRICT
    AS $$
        BEGIN
            RETURN floor(random()* (high-low + 1) + low);
        END;
        $$;
        CREATE FUNCTION public.test(citationid integer, citationtext text) RETURNS boolean
    LANGUAGE plpgsql
    AS $$
        BEGIN
            IF (citationID IS NULL) THEN
            RETURN FALSE;
            ELSE
            RETURN TRUE;
        END
        IF;
END;
$$;
        CREATE FUNCTION public.test2(citationid integer, citationtext text) RETURNS boolean
    LANGUAGE plpgsql
    AS $$
        BEGIN
            IF (citationID IS NULL) THEN
            RETURN FALSE;
            ELSE
            RETURN TRUE;
        END
        IF;
END;
$$;
        CREATE FUNCTION public.test3(citationid integer, citationtext text) RETURNS SETOF public.citations
    LANGUAGE plpgsql
    AS $$
        BEGIN
            IF (citationID IS NULL) THEN
            RETURN QUERY (
            SELECT *
            from citations
            where id = 2
            );
        ELSE
        RETURN QUERY (
        SELECT *
        from citations
        where id = citationID
        );
        END
        IF;
END;
$$;
