/* App.re */

type route =
  | Home
  | Second
  | Third;

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    <Nav />
    {switch (url.path) {
     | [""] => {Js.log("router: ' '"); <Third />} //<Home />
     | ["second"] => <Second /> //<iframe src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt" width="200" height="400"></iframe>
     | ["third"] => <Third /> //<img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png" width="400" height="200"/>
     | ["ed"] => <EventDisplay /> //<img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png" width="400" height="200"/>
     | _ => {Js.log("router: _"); <Third />} //<img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png" width="500" height="300"/>}
      // | _ => Js.log("home??? by default"); <Home />
     }}
  </div>;
};
