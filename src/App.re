/* App.re */

type route =
  | Home
  | Second
  | Third;

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    //<Nav />
    {switch (url.path) {
    | [""] => {
        //Js.log("router: ' '"); 
        <Third />
      } 
    | ["third"] => {
        <Test /> //<img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png" width="400" height="200"/>
      }
    | _ => {
        //Js.log("router: _"); 
        <Third /> //<img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png" width="500" height="300"/>}
      } 
    }}
  </div>;
};
