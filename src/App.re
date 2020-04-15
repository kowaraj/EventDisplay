[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    //<Nav />
    {
      // Js.log(url.path);
      switch (url.path) {
    | ["v0"] => {        
        // <p> {R.str("v0 route")} </p>
        <Version0 /> // copy of Third.re
      } 
    | ["v1"] => {
        //<p> {R.str("v1 route")} </p>
        <Version1 />
        // <AutoReloader />
      }
    | _ => {
        <p> {R.str("default route")} </p>
      } 
    }}
  </div>;
};
