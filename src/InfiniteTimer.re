let str = ReasonReact.string;
type state = {isTicking: bool};
type action =
    | Start
    | Stop
    | Tick;

module Button = {
  [@react.component]
  let make = (~label, ~onClick) => { <button onClick> {str(label)} </button>;  };
};

[@react.component]
let make = (~cb) => {

    let savedCallback = React.useRef(cb);
    let (state, dispatch) = React.useReducer(
        (s,a) => {
            switch a {
                | Start => {isTicking: true}
                | Stop => {isTicking: false}
                | Tick => { s.isTicking == true ? { cb(); s } : s }
            };
        },
        {isTicking: true}
    );

    React.useEffect0(() => {
//            let timerId = Js.Global.setInterval( () => dispatch(Tick), 1000 );
            let timerId = Js.Global.setInterval( () => React.Ref.(savedCallback->current()), 1000 );
            Some( () => Js.Global.clearInterval( timerId ) );
        }
    );

    <div> 
        {
            str("Infinite timer is " ++ (state.isTicking ? "running " : "stopped ") )
        } 
        {
            state.isTicking
            ? <Button label="STOP" onClick={_event => dispatch(Stop)} />
            : <>
                <Button label="START" onClick={_event => dispatch(Start)} />
            </>
        }

    </div>;
};
