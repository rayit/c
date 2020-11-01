export default class Login {

    loginForm;

    constructor() {
        this.loginForm = document.querySelector('#loginForm');
        console.log('constructor Login', this.loginForm);
        this.loginForm.onsubmit = this.handleSubmitForm.bind(this);
    }

    handleSubmitForm(e) {
        e.preventDefault();
        let input = document.querySelector('input');
        console.log('Login form clicked');
    }
}
