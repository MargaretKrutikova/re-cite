open DesignSystem;

[@react.component]
let make =
    (~authorName, ~authors: array(Types.author), ~onChange, ~className="") => {
  let (isInputMode, setIsInputMode) = React.useState(() => false);

  <div
    className=Css.(
      style([
        display(`flex),
        justifyContent(spaceBetween),
        alignItems(center),
      ])
    )>
    {isInputMode
       ? <TextField
           label="Author"
           placeholder="Who was it?"
           value=authorName
           onChange
           className
         />
       : <>
           <TextField.NativeSelect
             label="Author"
             placeholder="Who was it?"
             value=authorName
             onChange
             className>
             <option key="empty" value="" disabled=true>
               {React.string("Select author")}
             </option>
             {authors->Belt.Array.map(author =>
                <option value={author.name} key={author.name}>
                  {React.string(author.name)}
                </option>
              )
              |> React.array}
           </TextField.NativeSelect>
           <Button
             className=Css.(
               style([
                 marginLeft(`sm |> Styles.space),
                 marginTop(`sm |> Styles.space),
               ])
             )
             icon=true
             variant=`Contained
             color=`Primary
             onClick={_ => setIsInputMode(_ => true)}>
             <ReactFeather.PlusIcon />
           </Button>
         </>}
  </div>;
};
