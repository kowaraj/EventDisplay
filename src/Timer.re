let str = ReasonReact.string;
type state = {seconds: int, isTicking: bool};
type action =
    | Start
    | Stop
    | Reset
    | Tick;

module Button = {
  [@react.component]
  let make = (~label, ~onClick) => { <button onClick> {str(label)} </button>;  };
};

[@react.component]
let make = (~cb) => {

    let (state, dispatch) = React.useReducer(
        (s,a) => {
            switch a {
                | Start => {...s, isTicking: true}
                | Stop => {...s, isTicking: false}
                | Reset => {seconds: 60, isTicking: false}
                | Tick => { 
                    s.isTicking == true && s.seconds > 1 
                        ? { cb(); {...s, seconds: s.seconds - 1} } 
                        : {...s, isTicking: false}
                    }
            };
        },
        {seconds: 60, isTicking: false}
    );

    React.useEffect0(() => {
            let timerId = Js.Global.setInterval( () => dispatch(Tick), 1000 );
            Some( () => Js.Global.clearInterval( timerId ) );
        }
    );

    <div> 
        {
            str("Timer: [" ++ string_of_int(state.seconds) ++ "] is " ++ (state.isTicking ? "running " : "stopped ") )
        } 
        {
            state.isTicking
            ? <Button label="STOP" onClick={_event => dispatch(Stop)} />
            : <>
                <Button label="START" onClick={_event => dispatch(Start)} />
                <Button label="RESET" onClick={_event => dispatch(Reset)} />
            </>
        }

    </div>;
};
