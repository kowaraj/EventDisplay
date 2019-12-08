let fns_to_str = (fnlist) => {
    switch (List.length(fnlist)) {
        | 0 => "emptylist"
        | 1 => List.hd(fnlist)
        | _ => {
            List.length(fnlist) == 0 ? "emptylist" : List.hd(fnlist)
            let buf_grep = List.map(fn => {
                let fn_len = String.length(fn);
                String.sub(fn, fn_len-10, 7);
            },fnlist);
            "[ " ++ String.concat(" ", buf_grep) ++ " ]"
        }
    }
};

let fn_grep = (fn) => {
        let fn_len = String.length(fn);
        String.sub(fn, fn_len-10, 7);
};

let fn_sub = (fn, off, n) => {
        let fn_len = String.length(fn);
        String.sub(fn, fn_len-off, n);
};

let preload_image = [%raw {|
    function(url) {
        //console.log("preloading: " + url);
        const img = new Image();
        img.src = url;
        return;
    }
    |}];

let preload_image2 = [%raw {|
    function(url) {
        //console.log("preloading: " + url);
        const img = new Image();
        img.src = url;
        return img; 
    }
    |}];

let preload_images = [%raw {|
    function(url_list) {
        console.log("preloading list: " + url_list);
        url_list.map(url => {
                console.log("preloading ss: " + url);
                const img = new Image();
                img.src = url;
                return;
            }, url_list);
    }
    |}];
