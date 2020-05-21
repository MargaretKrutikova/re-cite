type t =
  | Collection(collectionHeaderData)
  | Default
and collectionHeaderData = {
  onEditSettings: unit => unit,
  slug: string,
  canAdd: bool,
  onAdd: unit => unit,
};

let isCollection =
  fun
  | Collection(_) => true
  | _ => false;
