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
     | [] => <Home />
     | ["second"] => <iframe src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/content.txt" width="200" height="400"></iframe>
     | ["third"] => <img src="https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/ss_1573150824.png"/>
     | _ => <Home />
     }}
  </div>;
};
