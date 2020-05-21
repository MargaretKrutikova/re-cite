type t =
  | Collection(collectionHeaderData)
  | Default
and collectionHeaderData = {
  onEditSettings: unit => unit,
  slug: string,
  canAdd: bool,
  onAdd: unit => unit,
};
