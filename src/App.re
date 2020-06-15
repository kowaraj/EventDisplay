[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    //<Nav />
    {
      Js.log(url.path)
      switch (url.path) {
    | ["v0"] => {        
        <Version0 /> 
      } 
    | ["v1"] => {
        <Version1 />
      }
    | _ => {
        <Version1 />
      } 
    }}
  </div>;
};
