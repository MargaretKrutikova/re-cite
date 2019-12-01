open DesignSystem;

let str = React.string;

module Classes = {
  open Css;

  let bigQuote = () =>
    style([
      borderLeft(`xxs |> Styles.space, `solid, `Primary |> Styles.useColor),
      marginBottom(`xl |> Styles.space),
      paddingLeft(`lg |> Styles.space),
      media(
        Breakpoint.up(`sm),
        [
          marginBottom(`xxl |> Styles.space),
          paddingLeft(`xl |> Styles.space),
        ],
      ),
    ]);

  let citation = () =>
    style([color(`SecondaryText |> Styles.useColor), ...Styles.font(`md)]);

  let hideMobile =
    style([
      display(none),
      media(Breakpoint.up(`sm), [display(initial)]),
    ]);
};

[@react.component]
let make = () => {
  <>
    <div className={Classes.bigQuote()}>
      <Heading level=`h1>
        {str("Write it down now, before you forget.")}
      </Heading>
      <div className={Classes.citation()}> {str("- ReCite")} </div>
    </div>
    <Text>
      {str(
         "An app that helps you manage citations from your
         colleagues, friends, books, movies, your cat or even yourself.",
       )}
    </Text>
    <Text>
      <span className=Classes.hideMobile>
        {str(
           {j|A deliberate place for citations — no more notepad,
          slack messages to yourself, or worse, pen and paper. |j},
         )}
      </span>
      {str("Create a collection and start adding citations right now.")}
    </Text>
    <Button
      gutter=`xl
      color=`Primary
      variant=`Contained
      onClick={_ => Route.push(CreateCollection)}>
      {str("Get started")}
    </Button>
    <Text size=`Small variant=`Secondary>
      {str(
         "The project is continuously developed and improved, many features are about to land,
         but if you have a specific request or found a bug, feel free to submit it on ",
       )}
      <Link
        href="https://github.com/margaretkrutikova/re-cite/issues" newTab=true>
        {React.string("github")}
      </Link>
      {str(".")}
    </Text>
  </>;
};
