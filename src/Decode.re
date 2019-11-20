type ss  = {
    name_list: list(string), 
    };

let ss_list_decoder = ss_list_json => {
    Json.Decode.{
        name_list: field("screenshots", list(string), ss_list_json)
    }
}

let ss_list = json => {
    Js.log("Decode.ss_list: json source is: <commented out>")
    Js.log(json);
    Json.Decode.(ss_list_decoder, json);
}


