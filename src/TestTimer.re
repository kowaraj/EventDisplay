let str = ReasonReact.string;
type state = {isTicking: bool};
type action =
    | Tick;

[@react.component]
let make = (~cb) => {

    let savedCallback = React.useRef(cb);
    // React.useEffect1( () => {
    //                             Js.log("useEffect is being registered")
    //                             React.Ref.(  Some(  () => savedCallback->setCurrent(cb)  ));
    //                         },
    //                         [|cb|]);

//     let (state, dispatch) = React.useReducer(
//         (s,a) => {
//             switch a {
//                 | Tick => { Js.log("Tick DISPATCHED"); s.isTicking == true ? { React.Ref.(savedCallback->current()); s } : s }
// //                | Tick => { Js.log("Tick DISPATCHED"); s.isTicking == true ? { cb(); s } : s }
//             };
//         },
//         {isTicking: true}
//     );


    React.useEffect0(() => {
            Js.log("React.useEffect initialized?")
//            let timerId = Js.Global.setInterval( () => { Js.log("dispatching a tick"); dispatch(Tick) }, 2000 );
            let timerId = Js.Global.setInterval( () => { Js.log("dispatching a tick"); React.Ref.(savedCallback->current()) }, 1000 );
            Some( () => {Js.log("UNSUBSCRIBING...."); Js.Global.clearInterval( timerId )} );
        }
    );

    <div> 
        {str("TIMER")}
    </div>;
};
