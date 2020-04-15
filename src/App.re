[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    //<Nav />
    {
      switch (url.path) {
    | ["v0"] => {        
        <Version0 /> 
      } 
    | ["v1"] => {
        <Version1 />
      }
    | _ => {
        <p> {R.str("default route")} </p>
      } 
    }}
  </div>;
};
