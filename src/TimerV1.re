[@react.component]
let make = (~cb) => {
    let savedCallback = React.useRef(cb);

    React.useEffect0(() => {
        let timerId = Js.Global.setInterval( () => { React.Ref.(savedCallback->current()) }, 2000 );
        Some( () => Js.Global.clearInterval( timerId ) );
        });

    <p></p>
};
