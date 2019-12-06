let str = ReasonReact.string;

type sss = {
    i: int, 
    len: int,
    bi: int, 
    sslist1: list(string),
    sslist2: list(string)
};
let url_json_list = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/ss_list.json";

[@react.component]
let make = () => { 
    let (ssurl, setSSUrl) = React.useState( () => "")
    let (sss, setSSS) = React.useState( () => {i: 0, len: 0, bi: 0, sslist1: [], sslist2: []})
    let (debug, setDebug) = React.useReducer(
        (_s, a) => a,
        true
    );


    let doFetchJSON = () => {
        //Js.log("fetching list of screenshots in json");
        Js.Promise.(
            Fetch.fetch(url_json_list) 
            |> then_(Fetch.Response.json)
            |> then_(json => {
                json 
                |> Decode.ss_list
                |> (fs => {Some(fs)}  |> resolve)
                })
        );
    };

    let callDoFetchJSON = () => {
        doFetchJSON()
        |> Js.Promise.then_( result => { 
            Js.log("callDoFetchJSON: "); Js.log(result); 
            switch result { 
                | Some(r  : Decode.ss) => {
                    switch r.bi {
                        | 1 => {
                                    setSSS(s => {
                                        ...s, 
                                        len: List.length(r.fns), 
                                        bi: r.bi,
                                        sslist1: r.fns
                                    })
                        }
                        | 2 => {
                                    setSSS(s => {
                                        ...s, 
                                        len: List.length(r.fns), 
                                        bi: r.bi,
                                        sslist2: r.fns
                                    })
                        }
                        | _ => {    () }
                    }
                }
                | None => setSSS(s => {...s, len: 0})
            }
            Js.Promise.resolve(); 
        } )
        |> ignore
    };

    // React.useEffect0( () => {
    //     Js.log("Fetching data! ")
    //     callDoFetchJSON();        
    //     None // no destroying
    // });

    // // side effect: Preloading images from the fetched filenames
    // React.useEffect1( () => {
    //     switch sslist {
    //     | Some(fetched_ss_list : Decode.ss) => 
    //     {
    //         // preloading...
    //         let ss_path = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_1/";
    //         let preload_ss = [%raw {|
    //             function(a) {
    //                 //console.log("preloading: " + a);
    //                 const img = new Image();
    //                 img.src = a;
    //                 return;
    //             }
    //             |}];

    //         List.map( 
    //             ss_i => {
    //                 preload_ss(ss_path ++ ss_i) |> ignore;
    //                 <p key=ss_i> {str(ss_i)} </p> 
    //             }, 
    //             fetched_ss_list.fns
    //         )
    //         |> Array.of_list
    //         |> React.array
    //         |> ignore;
            
    //         None;
    //     }
    //     | None => None;
    //     }
    // }, 
    // [|sslist|]);

    let fetchSS = (_e) => {
        Js.log("fetch SS");
        callDoFetchJSON();
    };
    let nextSS = (_e) => {
        Js.log("next SS");
        //setSSIndex( (ssindex + 1) mod sslistlen); 
        ();
    };
    let prevSS = (_e) => {
        Js.log("prev SS");
        //setSSIndex( (ssindex > 0) ? (ssindex - 1) : ssindex) ;
        ()
    };
    let timerCallbackOnTick = () => {
        Js.log("timerCallbackOnTick")
        setSSS( s => {...s, i: (s.len > 1) ? ((s.i + 1) mod s.len) : s.i} )
    };

    let switchDebug = (_e) => {
        setDebug( !debug );
    };

    let ss_path = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/";
    Js.log("sss.bi = " ++ string_of_int(sss.bi))
    Js.log("sss.len = " ++ string_of_int(sss.len));

    // switch sss.bi {
    //     | 1 => {
    //                 let ss_name = List.nth(sslist, sss.i);
    //                 setSSUrl(_ => ss_path ++ "buffer_1/" ++ ss_name)
    //             }
    //     | 2 => {        
    //                 let ss_name = List.nth(sslist2, sss.i);
    //                 setSSUrl(_ => ss_path ++ "buffer_2/" ++ ss_name)
    //             }
    //     | _ => {        
    //                 setSSUrl(_ => ss_path ++ "buffer_2/" ++ "noname")
    //             }
    // };

    <div>
        <div>
        (
            switch sss.bi {
                | 1 => {
                            let ss_name = List.nth(sss.sslist1, sss.i);
                            <ShowSS ssurl=(ss_path ++ "buffer_1/" ++ ss_name )/>
                        }
                | 2 => {        
                            let ss_name = List.nth(sss.sslist2, sss.i);
                            <ShowSS ssurl=(ss_path ++ "buffer_2/" ++ ss_name )/>                }
                | _ => {        
                        
                            <ShowSS ssurl=("")/>
                        }
            }
        )
        </div>
        // <br/>
        // {
        //     Js.log("URL: " ++ ssurl);
        //     <img src=ssurl width="100%"/>
        // }
        // <br/>
        <div hidden=(!debug)> 
            <>
            <InfiniteTimer cb=timerCallbackOnTick/>
            <button onClick={fetchSS}> {str("FETCH")} </button>
            <button onClick={nextSS}> {str("NEXT")} </button>
            <button onClick={prevSS}> {str("PREV")} </button> <br/>
            <p> {str("Total number of screenshots: " ++ string_of_int(sss.len) )}</p>
            <p> {str("Currently displayed is: " ++ string_of_int(sss.i) )}</p>
            <p> {str("Currently displayed batch is: " ++ string_of_int(sss.bi))}</p>
            </>
        </div>

        <div style=( ReactDOMRe.Style.make(~float="left", ~width="50%", ()))>
        (
            <div>
            {
                List.map( 
                    ss_i => {
                        <p key=ss_i> {str(ss_i)} </p>
                    }, 
                    sss.sslist1
                )
                |> Array.of_list
                |> React.array;
            }
            </div>
        )
        </div>

        <div style=( ReactDOMRe.Style.make(~float="left", ~width="50%", ()))>
        (
            <div>
            {
                List.map( 
                    ss_i => {
                        <p key=ss_i> {str(ss_i)} </p>
                    }, 
                    sss.sslist2
                )
                |> Array.of_list
                |> React.array;
            }
            </div>
        )
        </div>

        <>
            <button onClick={switchDebug}> {str("DEBUG")} </button>
        </>
    </div>
}
