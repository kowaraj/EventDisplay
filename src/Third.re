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
        |> Js.Promise.then_( result => { Js.log(result); setSSList(result); Js.Promise.resolve(); 
        } )
        |> ignore
    };

     React.useEffect0( () => {
        callDoFetch();        
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
    }

    switch sslist {
        | Some(fetched_ss_list : list(string)) => 
        {
            <div onClick={handleClick}> 
            (
                // fetched_ss_list
                // |> Array.of_list
                // |> React.array
            )
            </div>;
        }
        | None => 
        {
            <div onClick={handleClick}> 
                {str("failed to fetch ss_list_json")}
            </div>;
        }
    }

}
//<img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png" width="400" height="200"/>;
// <h1> {ReasonReact.string("Third page")} </h1>;
