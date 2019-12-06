let fns_to_str = (fnlist) => {
    let buf_grep = List.map(fn => {
        let fn_len = String.length(fn);
        String.sub(fn, fn_len-10, 7);
    },fnlist);
    String.concat(" ", buf_grep)
};



