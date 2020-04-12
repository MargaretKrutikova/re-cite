type loggedInUser = {
  email: string,
  id: string,
};

type t =
  | Anonymous
  | LoggedInUser(loggedInUser);

let make =
    ({user, isLoggedIn}: ReactNetlifyIdentity.reactNetlifyIdentityApi('a)) => {
  switch (user, isLoggedIn) {
  | (Some(loggedInUser), true) =>
    LoggedInUser({email: loggedInUser.email, id: loggedInUser.id})
  | _ => Anonymous
  };
};

let isLoggedIn =
  fun
  | LoggedInUser(_) => true
  | _ => false;

let useIdentityContext = () => {
  let mockContext = Utils.MockReactNetlifyIdentity.useRawContext();
  switch (mockContext) {
  | None => ReactNetlifyIdentity.useIdentityContextSimple()
  | Some(_) => Utils.MockReactNetlifyIdentity.useContext()
  };
};
