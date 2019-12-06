let str = ReasonReact.string;

type action = 
    | Init(list(string))
    | Update(list(string))
    | Tick;

type state = {
    index: int,
    buffer: list(string),
    nextBuffer: list(string),
    ssurl: string, 
    isTicking: bool,
    isInitialized: bool
};

[@react.component]
let make = (~buf) => {

    let (ss, dispatch) = 
        React.useReducer( 
            (state, action) => switch (action) { 
                | Init(buf) => {
                    Js.log("DISPLAY:::Dispatch( Init )");
                    {...state, isInitialized: true, buffer: buf, nextBuffer: buf}
                    }
                | Update(nextbuf) => { 
                    Js.log("DISPLAY:::Dispatch( Update )")
                    state
                    }
                | Tick => {
                    Js.log("DISPLAY:::Dispatch( Tick )")
                    state
                }
                },
            {
                index: 0,
                buffer: [],
                nextBuffer: [],
                ssurl: "",
                isTicking: false,
                isInitialized: false
            }
        );

   React.useEffect1( () => {
        Js.log("DISPLAY:::useEffect( buf )")
        switch buf {
            | Some(fns) => {
                Js.log("DISPLAY:::useEffect( buf ) -> Some(fns)")
                switch ss.isInitialized {
                    | false => {
                        Js.log("DISPLAY:::useEffect( buf ) -> Some(fns) -> init=false")
                        dispatch(Init(fns))
                        }
                    | true => {
                        Js.log("DISPLAY:::useEffect( buf ) -> Some(fns) -> init=true")
                        dispatch(Update(fns))
                        }
                }
            }
            | None => {
                Js.log("DISPLAY:::useEffect( buf ) -> None");
                ();
            }
        }
        None;
    }, [|buf|]);

    {
        // .render
        <div style=Style.ss>
            <div>
            {
                Js.log("******************************************");
                let fnstr1 = Util.fns_to_str(ss.buffer)
                Js.log("buffer1 = " ++ fnstr1);
                let fnstr2 = Util.fns_to_str(ss.buffer)
                Js.log("buffer2 = " ++ fnstr2);
                <p> { str(fnstr1)} <br /> { str(fnstr2)} </p>
            }
            </div>
            <div>
            {
                Js.log("DISPLAY:::ss = "); Js.log(ss);
                switch ss.isInitialized {
                | false => {
                    <img src="not-initialized" width="100%"/>
                    }
                | true => {
                    <img src={List.nth(ss.buffer, ss.index)} width="100%"/>
                    }
                }
            }
            </div>
            //<InfiniteTimer cb=timerCb/>
        </div>
    };

 
}