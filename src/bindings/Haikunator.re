type options = {
  tokenHex: bool,
  tokenLength: int,
  tokenChars: string,
};

type t = {. [@bs.meth] "haikunate": options => string};

[@bs.new] [@bs.module "haikunator"]
external createHaikunator: unit => t = "default";
