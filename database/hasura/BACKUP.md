# Backup data via pg_dump and hasura api

POST request to `/v1alpha1/pg_dump`:

1. For schema:

```
POST /v1alpha1/pg_dump HTTP/1.1
Content-Type: application/json
X-Hasura-Role: admin

{
  "opts": ["-O", "-x", "--schema-only", "--schema", "public"],
  "clean_output": true,
  "source": "<database-source-name>"
}
```

2. For data:

```
POST /v1alpha1/pg_dump HTTP/1.1
Content-Type: application/json
X-Hasura-Role: admin
{
  "opts": ["-O", "-x", "--column-inserts", "--data-only", "--schema", "public"],
  "clean_output": true,
  "source": "<database-source-name>"
}
```
