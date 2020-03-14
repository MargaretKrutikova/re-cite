CREATE TABLE public.authors (
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
ALTER SEQUENCE public.authors_id_seq OWNED BY public.authors.id;
CREATE TABLE public.citations (
    id integer NOT NULL,
    text text NOT NULL,
    "authorId" integer NOT NULL,
    "collectionId" uuid NOT NULL,
    added date DEFAULT now() NOT NULL
);
CREATE SEQUENCE public."citations_authorId_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
ALTER SEQUENCE public."citations_authorId_seq" OWNED BY public.citations."authorId";
CREATE SEQUENCE public.citations_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
ALTER SEQUENCE public.citations_id_seq OWNED BY public.citations.id;
CREATE TABLE public.collections (
    name text NOT NULL,
    id uuid DEFAULT public.gen_random_uuid() NOT NULL,
    slug text NOT NULL
);
ALTER TABLE ONLY public.authors ALTER COLUMN id SET DEFAULT nextval('public.authors_id_seq'::regclass);
ALTER TABLE ONLY public.citations ALTER COLUMN id SET DEFAULT nextval('public.citations_id_seq'::regclass);
ALTER TABLE ONLY public.authors
    ADD CONSTRAINT "authors_name_collectionId_key" UNIQUE (name, "collectionId");
ALTER TABLE ONLY public.authors
    ADD CONSTRAINT authors_pkey PRIMARY KEY (id);
ALTER TABLE ONLY public.citations
    ADD CONSTRAINT citations_pkey PRIMARY KEY (id);
ALTER TABLE ONLY public.collections
    ADD CONSTRAINT collections_name_key UNIQUE (name);
ALTER TABLE ONLY public.collections
    ADD CONSTRAINT collections_pkey PRIMARY KEY (id);
ALTER TABLE ONLY public.collections
    ADD CONSTRAINT collections_slug_key UNIQUE (slug);
ALTER TABLE ONLY public.authors
    ADD CONSTRAINT "authors_collectionId_fkey" FOREIGN KEY ("collectionId") REFERENCES public.collections(id) ON UPDATE RESTRICT ON DELETE RESTRICT;
ALTER TABLE ONLY public.citations
    ADD CONSTRAINT "citations_authorId_fkey" FOREIGN KEY ("authorId") REFERENCES public.authors(id) ON UPDATE CASCADE ON DELETE CASCADE;
ALTER TABLE ONLY public.citations
    ADD CONSTRAINT "citations_collectionId_fkey" FOREIGN KEY ("collectionId") REFERENCES public.collections(id) ON UPDATE CASCADE ON DELETE CASCADE;
