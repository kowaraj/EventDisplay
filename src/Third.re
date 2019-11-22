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
        (s, a) => a,
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

    let handleClick2 = (_e) => {
        Js.log("clicked");
        setSSIndex(ssindex + 1);
    };

    switch sslist {
        | Some(fetched_ss_list : Decode.ss) => 
        {


            // display
            let ss_first = List.nth(fetched_ss_list.fns, ssindex);
            let ss_path = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_copied/";
            <div onClick={handleClick2}> 
            {
                Js.log("nth ("++string_of_int(ssindex) ++ ") element is: " ++ ss_path ++ ss_first);
                <img src=(ss_path ++ ss_first) width="200" height="100"/>
            }
            <br/>
            {
                Js.log("nth ("++string_of_int(ssindex) ++ ") element is: " ++ ss_path ++ ss_first);
                <img src=(ss_path ++ ss_first) width="100%"/>                

                // pre-load images
                Js.log(fetched_ss_list.fns);
                <div> 
                (
                    List.map( 
                        ss_i => {<p> { Js.log(ss_i); str(ss_i) } </p>}, 
                        fetched_ss_list.fns
                    )
                    |> Array.of_list
                    |> React.array
                )
                </div>

            }
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
