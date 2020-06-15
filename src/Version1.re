let image_url_dev = "http://localhost:4000/buffer";
let image_url_pro = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/buffer/";
let image_url_s0 = "https://test-apashnin-ams.web.cern.ch/test-apashnin-ams/ss_0.png";
let image_url = image_url_pro;

// 1. no offset_min for UTC! 
[@react.component]
let make = () => { 
    let get_ts = [%raw {|
        function() {
            const now = new Date()
            const ts = Math.floor(Date.now() / 1000)   
            const offset_min = now.getTimezoneOffset()
            const ts_sec_utc = Math.floor(now /2 / 1000)*2 -60 // no offset for UTC! + offset_min * 60
            return ts_sec_utc 
        }
        |}];   


    let ts : int = get_ts();
    let (index, setIndex) = React.useState(() => 0);
    let (imageURL, setImageURL) = React.useState(() => image_url_s0);
    let timerCallback = () => {
        //Js.log("periodic timer callback");
        let ts = get_ts()
        setImageURL(_ => image_url ++ "/ss_" ++ string_of_int(ts) ++ ".png")
    };

    <div>
        <img src={imageURL} style=Style.image/> <br />
        <TimerV1 cb=timerCallback/>
    </div>
}
