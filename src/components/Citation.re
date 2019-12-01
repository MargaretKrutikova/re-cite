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
    ]);
};

[@react.component]
let make = (~text, ~author, ~date) => {
  let iconStyle = Classes.menuIcon();

  <Card>
    <div className=Classes.citationText> {str(text)} </div>
    <Flex justify=`spaceBetween align=`end_>
      <span className={Classes.secondaryText()}> {str(author)} </span>
      <span className={Classes.secondaryText()}> {str(date)} </span>
    </Flex>
    <div className=Classes.menu>
      <Menu
        align=`Right
        renderTrigger={toggle =>
          <Button onClick=toggle icon=true variant=`Text color=`Primary>
            <ReactFeather.ChevronDownIcon />
          </Button>
        }
        renderOptions={() =>
          <React.Fragment>
            <Menu.MenuItem>
              <ReactFeather.LinkIcon className=iconStyle />
              {str("Copy link")}
            </Menu.MenuItem>
          </React.Fragment>
        }
      />
    </div>
  </Card>;
};
