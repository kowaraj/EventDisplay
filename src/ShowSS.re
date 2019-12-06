let str = ReasonReact.string;

[@react.component]
let make = (~ssurl) => {

    <div>
        <img src={ssurl} width="100%"/>
    </div>
}