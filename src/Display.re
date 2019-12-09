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
    isInitialized: bool, 
};

let state_to_str = (s) => {
    string_of_int(s.index) ++ (s.isTicking?"+":"-") ++ (s.isInitialized?"+":"-") ++ 
    string_of_int(List.length(s.buffer)) ++ string_of_int(List.length(s.nextBuffer)) ;
};

let preloaded_im = Util.preload_image2("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1574257457.png");

[@react.component]
let make = (~cb, ~buf) => {

    let (ss, dispatch) = 
        React.useReducer( 
            (state, action) => switch (action) { 
                | Init(buf) => {
                    Js.log("DISPLAY:::Dispatch( Init ) ---> " ++ state_to_str(state));
                    Js.log(buf)
                    //Util.preload_images(Array.of_list(buf)) |> ignore;
                    let new_s = {...state, isInitialized: true, buffer: buf, nextBuffer: ["init"]}
                    //Js.log("DISPLAY:::Dispatch( Init ) -----------> " ++ state_to_str(state));
                    new_s
                    }
                | Update(nextbuf) => { 
                    Js.log("DISPLAY:::Dispatch( Update )");
                    Util.preload_images(Array.of_list(nextbuf)) |> ignore;
                    {...state, nextBuffer: nextbuf}
                    }
                | Tick => {
                    let len = List.length(state.buffer)
                    let i = state.index
                    Js.log("DISPLAY:::Dispatch( Tick ) " ++ string_of_int(len) ++ " " ++ string_of_int(i) );

                    (i == len -2) ? cb() : ()

                    let rollover = (i == len - 1)
                    rollover 
                    ? { 
                        List.length(state.nextBuffer) != 0 
                        ? {...state, index: 0, buffer: state.nextBuffer, nextBuffer: []}
                        : {...state, index: 0}
                    }
                    : {...state, index: state.index + 1}

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

    let timerCb = () => {
        //Js.log("tick");
        dispatch(Tick)
    }

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

    // Rendering the component
    {
        <div style=Style.ss>
            <div hidden=true>
            {
                Js.log("******************************************" ++ state_to_str(ss));
                let fnstr1 = Util.fns_to_str(ss.buffer);
                Js.log("buffer  = " ++ fnstr1);
                let fnstr2 = Util.fns_to_str(ss.nextBuffer);
                Js.log("bufferN = " ++ fnstr2);
                <p> { str(fnstr1)} <br /> { str(fnstr2)} </p>
            }
            </div>
            <div>
            {
                //Js.log("DISPLAY:::ss = "); Js.log(ss);
                switch ss.isInitialized {
                | false => {
                    <p> {str("N/A")} 
                        <img src="not-initialized" width="100%"/>
                    </p>
                    }
                | true => {
                    let fn = List.nth(ss.buffer, ss.index);
                    Js.log(fn);
                    <div> 
                        <p hidden=true id="preloaded_im"> {str(Util.fn_grep(fn))} </p>
                        <div>
                            <img src={fn} width="100%"/>
                        </div>
                    </div>
                    }
                }
            }
            </div>
            <InfiniteTimer cb=timerCb/>
        </div>
    };

 
}