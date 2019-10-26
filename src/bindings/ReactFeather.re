module SearchIcon = {
  [@bs.module "react-feather/dist/icons/search.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~disabled: bool=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module PlusIcon = {
  [@bs.module "react-feather/dist/icons/plus.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~disabled: bool=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module UserIcon = {
  [@bs.module "react-feather/dist/icons/user.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~disabled: bool=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module CloseIcon = {
  [@bs.module "react-feather/dist/icons/x.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~fill: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module LogoutIcon = {
  [@bs.module "react-feather/dist/icons/log-out.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~fill: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module LoaderIcon = {
  [@bs.module "react-feather/dist/icons/loader.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~fill: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module FilterIcon = {
  [@bs.module "react-feather/dist/icons/filter.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~fill: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module MoonIcon = {
  [@bs.module "react-feather/dist/icons/moon.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~disabled: bool=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};

module SunIcon = {
  [@bs.module "react-feather/dist/icons/sun.js"] [@react.component]
  external make:
    (
      ~color: string=?,
      ~disabled: bool=?,
      ~onClick: 'c=?,
      ~size: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "default";
};
