export default class Login {

    loginForm;

    constructor() {
        this.loginForm = document.querySelector('#loginForm');
        console.log('constructor Login', this.loginForm);
        this.loginForm.onsubmit = this.handleSubmitForm.bind(this);
    }

    handleSubmitForm(e) {
        e.preventDefault();
        let username = this.loginForm.querySelector('input[name="username"]');
        let password = this.loginForm.querySelector('input[name="password"]');
        this.login("POST", "/cgi-bin/login", username, password);
    }


    login(method = get, url, username, password) {
        return new Promise(function (resolve, reject) {
            let http = new XMLHttpRequest();
            let params = "username="+username+"&password=" + password;
            http.open(method, url, true);

            // Send the proper header information along with the request
            http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            http.onreadystatechange = function() {
                if( http.readyState == 4 && http.status == 200) {
                    alert(http.responseText);
                }
            }
            http.send(params);
        });
    }
}
