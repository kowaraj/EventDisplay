let str = ReasonReact.string;

type state ={
    ind: int, 
    data: string
};
type action = 
    | Click;

let doFetch = () => {
    Js.log("fetching");
    "fetched-data"
};

[@react.component]
let make = () => 
{




    let (x, setX) = React.useState( () => "initial value of x" );

    let doFetch = () => {
        Js.log("fetching");
        Js.Promise.(
            Fetch.fetch("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer_copied/ss_list.json") 
//            Fetch.fetch("http://localhost:3002/content.txt", 
//            Fetch.fetchWithInit("http://localhost:3001/content.txt", 
//            Fetch.fetchWithInit("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt", 
//            Fetch.fetchWithInit("http://localhost:3003/content.txt", 
//              Fetch.RequestInit.make(~method_=Get, ()),
//              Fetch.RequestInit.make(~method_=Get, ~mode=NoCORS, ()),
//            )
            |> then_(Fetch.Response.text)
            |> then_(text => ({Js.log(text); Some(text)} |> resolve))
        );
    };

    React.useEffect0(
        () => {


            Js.Promise.(
                doFetch()
                |> then_( result => {
                            switch (result) {
                                | Some(data) => {
                                    Js.log("fetched data is: ")
                                    Js.log(data);
                                    setX(_ => data);
//                                    setX(_ => "some data have been fetched!");
                                    resolve();
                                    }
                                | None => {
                                    Js.log("NONE! no data fetched");
                                    setX(_ => "no data fetched");
                                    resolve();
                                    }
                            }
                        })
                |> ignore                            
            )
            None;




        }

    );






    // let doFetch = () => {
    //     Js.log("fetching");
    //     Js.Promise.(
    //         Fetch.fetchWithInit("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt", 
    //           Fetch.RequestInit.make(~method_=Get, ~mode=NoCORS, ()),
    //         )
    //             |> then_(Fetch.Response.text)
    //             |> then_(text => {Js.log("text = " ++ text); print_endline(text)} |> resolve)
    //     );
    // };

    // let doFetch = () => {
    //     Js.log("fetching");
    //     Js.Promise.(
    //         Fetch.fetchWithInit("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt", 
    //           Fetch.RequestInit.make(~method_=Get, ~mode=NoCORS, ()),
    //         )
    //             |> then_(Fetch.Response.text)
    //             |> then_(text => {setX(_ => text); print_endline(text)} |> resolve)
    //     );
    // };

    let (_state, _dispatch) = React.useReducer( (_s, a) => 

        switch (a) {
        | Click => {ind: 1, data: x}

        }, 
        {ind: 0, data: "init-data"}
    );

    // let (_state, dispatch) = React.useReducer( (_s, a) => 

    //     switch (a) {
    //     | Click => doFetch() |> ignore; {ind: 1}
    //     }, 
    //     {ind: 0}
    // );

    // {
    // <div>
    //     <button > {str("do-fetch-me")} </button>
    //     //doFetch();

    //     <iframe src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt" width="200" height="400"></iframe>;

    //     <p>       {str("X ?=== " ++ x)}        </p>
    //     <p>       {str("X === " ++ x)}        </p>
    // </div>
    // }

    <div>
        //<button onClick={ _e => dispatch(Click) } > {str("do-fetch-me")} </button> 
        // <br/>
        // //<iframe src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt" width="200" height="200"></iframe>
        <p> {str("Fetched X = " ++ x)} </p>
    </div>

}




