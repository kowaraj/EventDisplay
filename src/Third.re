let str = ReasonReact.string;
let handleClick = (_e) => Js.log("clicked");
let msg = "hi";

[@react.component]
let make = () => {
    let (sslist, setSSList) = React.useReducer(
        (_oldState, actionIsNewState) => actionIsNewState,  //state after action
        None // initial state
    );
    let (ssindex, setSSIndex) = React.useReducer(
        (_s, a) => a,
        0
    );

    let doFetchJSON = () => {
        Js.log("fetching list of screenshots in json");
        Js.Promise.(
            Fetch.fetch("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_copied/ss_list.json") 
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
        |> Js.Promise.then_( result => { Js.log("doFetchJSON results are: "); Js.log(result); setSSList(result); Js.Promise.resolve(); 
        } )
        |> ignore
    };

    React.useEffect0( () => {
        callDoFetchJSON();        
        None // no destroying
    });

    React.useEffect1( () => {
        switch sslist {
        | Some(fetched_ss_list : Decode.ss) => 
        {
            // preloading...
            let ss_path = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_copied/";
            let preload_ss = [%raw {|
                function(a) {
                    console.log("preloading: " + a);
                    const img = new Image();
                    img.src = a;
                    return;
                }
                |}];

            List.map( 
                ss_i => {
                    // Js.log(ss_i); 
                    preload_ss(ss_path ++ ss_i);
                    <p key=ss_i> {str(ss_i)} </p> 
                }, 
                fetched_ss_list.fns
            )
            |> Array.of_list
            |> React.array
            |> ignore;
            
            None;
        }
        | None => None;
        }
    }, 
    [|sslist|]);

    let fetchSS = (_e) => {
        Js.log("fetch SS");
        callDoFetchJSON();
    };
    let nextSS = (_e) => {
        Js.log("next SS");
        setSSIndex( (ssindex + 1) mod 60);
    };
    let prevSS = (_e) => {
        Js.log("prev SS");
        setSSIndex( (ssindex > 0) ? (ssindex - 1) : ssindex) ;
    };



    switch sslist {
        | Some(fetched_ss_list : Decode.ss) => 
        {
            // display
            let ss_first = List.nth(fetched_ss_list.fns, ssindex);
            let ss_path = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_copied/";

            // let preload_ss = [%raw {|
            //     function(a) {
            //         console.log("preloading: " + a);
            //         const img = new Image();
            //         img.src = a;
            //         return;
            //     }
            //     |}];

//            <div onClick={handleClick2}> 

            // {
            //     <div>
            //     {
            //         Js.log("asdf")        
            //         List.map( 
            //             ss_i => {
            //                 // Js.log(ss_i); 
            //                 preload_ss(ss_path ++ ss_i);
            //                 <p key=ss_i> {str(ss_i)} </p> 
            //             }, 
            //             fetched_ss_list.fns
            //         )
            //         |> Array.of_list
            //         |> React.array;
                        
            //         str("asdf")
            //     }
            //     </div>
            // };

            <div> 
                // <div>
                //     {
                //     List.map( 
                //         ss_i => {
                //             // Js.log(ss_i); 
                //             preload_ss(ss_path ++ ss_i);
                //             <p key=ss_i> {str(ss_i)} </p> 
                //         }, 
                //         fetched_ss_list.fns
                //     )
                //     |> Array.of_list
                //     |> React.array;
                // <div>
                //     </div>

                //     }
                // </div>


                <div>
                    <button onClick={fetchSS}> {str("FETCH")} </button>
                    <button onClick={nextSS}> {str("NEXT")} </button>
                    <button onClick={prevSS}> {str("PREV")} </button>
                    <br/>
                    {
                        Js.log("nth ("++string_of_int(ssindex) ++ ") element is: " ++ ss_path ++ ss_first);
                        <img src=(ss_path ++ ss_first) width="200" height="100"/>
                    }
                    <br/>
                    {
                    Js.log("nth ("++string_of_int(ssindex) ++ ") element is: " ++ ss_path ++ ss_first);
                    <img src=(ss_path ++ ss_first) width="100%"/> //    |>ignore;           
                    }
                </div>
            </div>;
        }
        | None => 
        {
            Js.log(sslist);
            <div onClick={handleClick}> 
                {str("failed to fetch ss_list_json")}
            </div>;
        }
    }
}
