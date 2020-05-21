external promiseErrorToJsObj: Js.Promise.error => Js.t('a) = "%identity";

let getInputValue = (e): string => ReactEvent.Form.target(e)##value;

let generateRandomCollectionName = () => {
  let haikunator = Haikunator.createHaikunator();
  haikunator##haikunate({
    tokenHex: true,
    tokenLength: 4,
    tokenChars: "0123456789abcdefghigklmnopqrst",
  });
};

module Display = {
  let hideMobile =
    Css.(style([media(Breakpoint.down(`sm), [display(none)])]));

  let hideDesktop =
    Css.(style([media(Breakpoint.up(`sm), [display(none)])]));
};

module MockReactNetlifyIdentity = {
  open ReactNetlifyIdentity;
  let mockContextValue: reactNetlifyIdentityApi(Js.t({.})) = {
    user: None,
    isConfirmedUser: false,
    isLoggedIn: false,
    signupUser: (~email as _, ~password as _, ~data as _) =>
      Js.Promise.resolve(None),
    loginUser: (~email as _, ~password as _, ~remember as _=false, _) =>
      Js.Promise.resolve(None),
    logoutUser: _ => Js.Promise.resolve(None),
    requestPasswordRecovery: (~email as _) => Js.Promise.resolve(),
    recoverAccount: (~remember as _=false, _) => Js.Promise.resolve(None),
    updateUser: _ => Js.Promise.resolve(None),
    getFreshJWT: _ => Js.Promise.resolve(""),
    url: "",
    loginProvider: _ => ignore(),
    acceptInviteExternalUrl: (~token as _) => "",
    settings: {
      autoconfirm: false,
      disableSignup: false,
      providers: [||],
    },
    param: {
      token: None,
      type_: Unknown,
      error: None,
      status: None,
    },
  };
  let context: React.Context.t(option(reactNetlifyIdentityApi(Js.t({.})))) =
    React.createContext(None);

  let useRawContext = () => React.useContext(context);
  let useContext = () =>
    React.useContext(context)->Belt.Option.getWithDefault(mockContextValue);

  module Provider = {
    let make = React.Context.provider(context);
    let makeProps = (~value, ~children, ()) => {
      "value": value,
      "children": children,
    };
  };
};
