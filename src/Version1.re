let image_url = "http://localhost:4000/buffer";

[@react.component]
let make = () => { 
    let get_ts = [%raw {|
        function() {
            const now = new Date()
            const ts = Math.floor(Date.now() / 1000)   
            const offset_min = now.getTimezoneOffset()
            const ts_sec_utc = Math.floor(now / 1000) + offset_min * 60

            // console.log("now         = ", now)
            // console.log("now_____utc = ", now.toUTCString())
            // console.log("now_sec_utc = ", Date(now.toUTCString()))
            // console.log("now_sec     = ", Date(now))
            
            //console.log("ts_sec      = ", ts)
            //console.log("ts_sec_utc  = ", ts_sec_utc)

            return ts_sec_utc
        }
        |}];   
         
    let ts : int = get_ts();
    let (index, setIndex) = React.useState(() => 0);
    let (imageURL, setImageURL) = React.useState(() => image_url ++ "/ss_0000000000.png");
    let timerCallback = () => {
        Js.log("periodic timer callback");
        let ts = get_ts()
        setImageURL(_ => image_url ++ "/ss_" ++ string_of_int(ts) ++ ".png")
    };

    <div>
        <img src={imageURL} style=Style.image/> <br />
        <TimerV1 cb=timerCallback/>
    </div>
}
