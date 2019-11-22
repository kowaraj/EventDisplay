let str = ReasonReact.string;
let handleClick = (_e) => Js.log("clicked");
let msg = "hi";

[@react.component]
let make = () => {
    let (data, setData) = React.useReducer(
        (_oldState, actionIsNewState) => actionIsNewState,  //state after action
        None // initial state
    );
    let (sslist, setSSList) = React.useReducer(
        (_oldState, actionIsNewState) => actionIsNewState,  //state after action
        None // initial state
    );
    let (ssindex, setSSIndex) = React.useReducer(
        (s, a) => a,
        0
    );


    let doFetch = () => {
        Js.log("fetching from third");
        Js.Promise.(
            Fetch.fetch("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_copied/ss_list.json") 
            |> then_(Fetch.Response.text)
            |> then_(text => ({Js.log(text); Some(text)} |> resolve))
        );
    };

    let doFetchJSON = () => {
        Js.log("fetching from third");
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

    let callDoFetch = () => {
        doFetch()
        |> Js.Promise.then_( result => { Js.log(result); setData(result); Js.Promise.resolve(); 
        } )
        |> ignore
    };

    let callDoFetchJSON = () => {
        doFetchJSON()
        |> Js.Promise.then_( result => { Js.log("doFetchJSON results are: "); Js.log(result); setSSList(result); Js.Promise.resolve(); 
        } )
        |> ignore
    };

     React.useEffect0( () => {
        callDoFetch();        
        None // no destroying
    });

     React.useEffect0( () => {
        callDoFetchJSON();        
        None // no destroying
    });

    switch data {
        | Some(fetched_data) => 
        {
            <div onClick={handleClick}> 
                {str(fetched_data)}
            </div>;
        }
        | None => 
        {
            <div onClick={handleClick}> 
                {str("failed to fetch")}
            </div>;
        }
    };

    let handleClick2 = (_e) => {
        Js.log("clicked");
        setSSIndex(ssindex + 1);
    }
    switch sslist {
        | Some(fetched_ss_list : Decode.ss) => 
        {
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
// <h1> {ReasonReact.string("Third page")} </h1>;
