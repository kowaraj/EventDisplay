let image_url = "http://localhost:4000/buffer/";

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
            console.log("ts_sec      = ", ts)
            console.log("ts_sec_utc  = ", ts_sec_utc)

            return ts_sec_utc
        }
        |}];    
    let ts = get_ts();

    <div>
        <img src={image_url ++ "ss_" ++ ts ++ ".png"} style=Style.image/> <br />
    </div>
}
