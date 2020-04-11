open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let menuIcon = () =>
    style([
      width(px(20)),
      marginRight(`xs |> Styles.space),
      color(`Primary |> Styles.useColor),
      flexShrink(0.0),
    ]);
};

[@react.component]
let make = (~slug, ~id: string, ~onEdit) => {
  let citationUrl = Route.toUrl(Collection(slug, CitationById(id)));
  let iconStyle = Classes.menuIcon();

  <Menu
    align=`Right
    renderTrigger={(toggle, _) =>
      <Button onClick=toggle icon=true variant=`Text color=`Primary>
        <ReactFeather.ChevronDownIcon />
      </Button>
    }
    renderOptions={toggle =>
      <React.Fragment>
        <CopyToClipboard
          text={citationUrl |> Route.toAbsoluteUrl}
          onCopy={() => {
            toggle();
            ReactToastify.toast("Copied!");
          }}>
          <Menu.MenuItem>
            <ReactFeather.LinkIcon className=iconStyle />
            {str("Copy link")}
          </Menu.MenuItem>
        </CopyToClipboard>
        <Menu.MenuItem.Link
          href=citationUrl newTab=true variant=`Text onClick={_ => toggle()}>
          <ReactFeather.ExternalLinkIcon className=iconStyle />
          {str("Go to link")}
        </Menu.MenuItem.Link>
        <Menu.MenuItem
          onClick={_ => {
            toggle();
            onEdit();
          }}>
          <ReactFeather.EditIcon className=iconStyle />
          {str("Edit citation")}
        </Menu.MenuItem>
      </React.Fragment>
    }
  />;
};
