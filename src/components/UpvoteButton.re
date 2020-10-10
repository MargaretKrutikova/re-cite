open DesignSystem;
open Mutations;
open ApolloHooks;

type size = [ | `Medium | `Large];

module Classes = {
  open Css;

  let upvoteContainer = style([marginLeft(`lg |> Styles.space)]);
  let upvoteCount = size => {
    let fs =
      switch (size) {
      | `Medium => Styles.font(`sm)
      | `Large => Styles.font(`base)
      };
    style([
      marginLeft(`xxs |> Styles.space),
      marginRight(`xs |> Styles.space),
      ...fs,
    ]);
  };
  let upvoteButton = () => style([color(`BodyText |> Styles.useColor)]);
  let upvoteIcon = size => {
    let size =
      switch (size) {
      | `Medium => 20
      | `Large => 26
      };
    style([
      unsafe("strokeWidth", "1px"),
      width(px(size)),
      height(px(size)),
    ]);
  };

  let upvoteIconActive = () =>
    style([unsafe("fill", Styles.useColor(`Primary) |> Colors.toString)]);
};

let isUpvotedByLoggedInUser = (user, upvoteUserIds) => {
  switch (user) {
  | User.LoggedInUser({id: userId}) =>
    upvoteUserIds->Belt.Array.keep(id => id == userId)->Belt.Array.length > 0
  | _ => false
  };
};

[@react.component]
let make =
    (
      ~upvoteCount,
      ~citationId: int,
      ~upvoteUserIds,
      ~size: size=`Medium,
      ~className="",
    ) => {
  let upvoteActiveIconStyle = Classes.upvoteIconActive();

  let identity = User.useIdentityContext();
  let user = User.make(identity);

  let (upvote, upvoteStatus, _) = useMutation(UpvoteCitation.definition);
  let (removeUpvote, removeUpvoteStatus, _) =
    useMutation(RemoveUpvoteCitation.definition);

  let isActive = isUpvotedByLoggedInUser(user, upvoteUserIds);

  let handleUpdate = userId => {
    switch (upvoteStatus, removeUpvoteStatus) {
    | (Loading, _)
    | (_, Loading) => ignore()
    | _ =>
      let variables = UpvoteCitation.makeVariables(~userId, ~citationId, ());

      if (isActive) {
        removeUpvote(~variables, ()) |> ignore;
      } else {
        upvote(~variables, ()) |> ignore;
      };
    };
  };

  let handleUpvoteClick = () => {
    switch (user) {
    | User.LoggedInUser(user) => handleUpdate(user.id)
    | _ => ReactToastify.toast("Log in to upvote")
    };
  };

  <Flex
    align=`center className={Css.merge([Classes.upvoteContainer, className])}>
    <Button
      className={Classes.upvoteButton()}
      size
      color=`Primary
      icon=true
      onClick={_ => handleUpvoteClick()}>
      <ReactFeather.UpvoteIcon
        className={Css.merge([
          Classes.upvoteIcon(size),
          isActive ? upvoteActiveIconStyle : "",
        ])}
      />
    </Button>
    {upvoteCount > 0
       ? <div className={Classes.upvoteCount(size)}>
           {upvoteCount |> string_of_int |> React.string}
         </div>
       : React.null}
  </Flex>;
};
