async function get_ezdata_token( btn ) {
    try {
        var token = window.localStorage.getItem("ezdata_token")
        if (token == null || btn){
            token = await window.$nuxt.$axios.post("https://ezdata.m5stack.com/api/accessKey/apply")
            token = token.data.data.accessKey
            window.localStorage.setItem("ezdata_token", token)
        }
        setTimeout(() => {
            document.getElementById("ezdata_token").innerHTML = token;
        }, 100);
    } catch (error) {

    }
}