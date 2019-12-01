[@bs.module "react-copy-to-clipboard"] [@react.component]
external make:
  (~text: string, ~children: React.element, ~onCopy: unit => unit=?) =>
  React.element =
  "CopyToClipboard";
