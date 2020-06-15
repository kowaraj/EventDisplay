[@react.component]
let make = (~cb) => {
    let savedCallback = React.useRef(cb);
    let (enabled, setEnabled) = React.useState( () => true)
    let (count, setCount) = React.useState( () => 0)

    React.useEffect0(() => {
        let timerId = Js.Global.setInterval( () => {
            setCount(c => c + 1)
            React.Ref.(savedCallback->current())
        }, 1000 );
        Some( () => Js.Global.clearInterval( timerId ) );
        });

    <div hidden=true> 
        { R.str("Timer.V1 is " ++ (enabled ? "running " : "stopped ") ++ ", count: " ++ string_of_int(count) )  }
    </div>;
};
