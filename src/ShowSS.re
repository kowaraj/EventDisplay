let str = ReasonReact.string;

[@react.component]
let make = (~buf) => {

    let (buffer, setBuffer) = React.useState( () => []);
    let (nextBuffer, setNextBuffer) = React.useState( () => []);
    let (ssurl, setSSUrl) = React.useState( () => "")
    let (index, setIndex) = React.useState( () => 0)
    
    let timerCb = () => {
        let blen = List.length(buffer);
        setIndex( i => (blen > 2) ? ((i + 1) mod blen) : i )
    };

    React.useEffect0( () => {
        Js.log("========================== ShowSS: useEffect !")
        Js.log(String.concat(" ", buf));
        setNextBuffer(_ => buf);
        setBuffer(_ => buf);
        None
    })

    React.useEffect1( () => {
        Js.log("========================== ShowSS: useEffect(buf)")
        setNextBuffer(_ => buf);
        Js.log(String.concat(" ", buf));
        None
    }, 
    [|buf|]);

    <div>

        <div>
        {
            let blen = List.length(buffer);
            let ssurl = (blen != 0) ? List.nth(buffer, index): "noname";
            <img src=ssurl width="100%"/>
        }
        </div>
        
        
        <InfiniteTimer cb=timerCb/>

    </div>

}