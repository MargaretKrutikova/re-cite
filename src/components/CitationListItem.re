open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let citationText =
    style([
      marginBottom(`sm |> Styles.space),
      paddingTop(`xs |> Styles.space),
      media(Breakpoint.up(`sm), [paddingTop(px(0))]),
      unsafe("wordBreak", "break-word"),
      whiteSpace(`preWrap),
      ...Styles.font(`base),
    ]);

  let secondaryText = () =>
    style([color(`SecondaryText |> Styles.useColor), ...Styles.font(`sm)]);

  let menu =
    style([
      position(`absolute),
      top(`xxs |> Styles.space),
      right(`xs |> Styles.space),
    ]);

  let menuIcon = () =>
    style([
      width(px(20)),
      marginRight(`xs |> Styles.space),
      color(`Primary |> Styles.useColor),
      flexShrink(0.0),
    ]);
};

[@react.component]
let make = (~text, ~author, ~date, ~slug, ~id, ~onEdit) => {
  let iconStyle = Classes.menuIcon();

  let citationUrl = Route.toUrl(Collection(slug, CitationById(id)));

  let (state, setState) = React.useState(_ => false);
  let toggleActive = _ => setState(s => !s);

  <Card>
    <div className=Classes.citationText> {str(text)} </div>
    <Flex justify=`spaceBetween align=`center>
      <span className={Classes.secondaryText()}> {str(author)} </span>
      <Flex align=`center>
        <div className={Classes.secondaryText()}> {str(date)} </div>
        <UpvoteButton upvoteCount=45 isActive=state onClick=toggleActive />
      </Flex>
    </Flex>
    <div className=Classes.menu>
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
              href=citationUrl
              newTab=true
              variant=`Text
              onClick={_ => toggle()}>
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
      />
    </div>
  </Card>;
};
