let str = ReasonReact.string;

[@react.component]
let make = () => {
    let (ssindex, setSSIndex) = React.useState( () => 0);


    let timerCallbackOnTick = () => {
        Js.log(ssindex)
        Js.log("Tick IN >>     : " ++ string_of_int(ssindex));
        setSSIndex( x => x + 1);
        Js.log("        << OUT : " ++ string_of_int(ssindex))
    };

    <div>
        <TestTimer cb=timerCallbackOnTick/>
        {str("Currently displayed is: " ++ string_of_int(ssindex) )}
    </div>
}
