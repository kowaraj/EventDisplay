let str = ReasonReact.string;



[@react.component]
let make = () => 
{
    let (x, setX) = React.useState( () => "initial value of x" );

let doFetch = () => {
    Js.log("fetching");

    Js.Promise.(
        Fetch.fetch("https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt")
            |> then_(Fetch.Response.text)
            |> then_(text => {setX(_ => text); print_endline(text)} |> resolve)
    );

};
    doFetch();

    <iframe src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt" width="200" height="400"></iframe>;

    <p>       {str("X = " ++ x)}        </p>


}




