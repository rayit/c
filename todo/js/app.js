import Todo from './todo.js';
import Login from './login.js';

export default class app {

    constructor() {
        let page = `<header class="logo">
                <a href="https://www.rayit.nl" target="_blank">
                    <img src="images/todo-logo.png" class="logo" alt="todo">
                </a>
                <h2 class="headline">Todo</h2>
            </header>
            <nav class="nav">
                <a href="#login" class="nav__link" data-link>Login</a>
                <a href="#home" class="nav__link" data-link>Dashboard</a>
                <a href="#todo" class="nav__link" data-link>Todo</a>
                <a href="#settings" class="nav__link" data-link>Settings</a>
            </nav>
            <div id="content"></div>`;

        document.getElementById('app').innerHTML = page;
    }
}

new app();

window.addEventListener("hashchange",  () => {
    var contentDiv = document.getElementById("content");
    contentDiv.innerHTML = location.hash;
    switch(location.hash) {
        case '#todo':
            loadTodo();
            break;
	    case "#dashboard":
	        loadHome();
	    break;
        case '#login':
            loadLogin();
            break;
        default:
            loadLogin();
    }
});

async function fetchHtmlAsText(url) {
    const response = await fetch(url);
    return await response.text();
}

async function loadLogin() {
    const contentDiv = document.getElementById("content");
    contentDiv.innerHTML = await fetchHtmlAsText("views/login.html");
    new Login();
}

async function loadHome() {
    const contentDiv = document.getElementById("content");
    contentDiv.innerHTML = await fetchHtmlAsText("views/home.html");
}

async function loadTodo() {
    const contentDiv = document.getElementById("content");
    contentDiv.innerHTML = await fetchHtmlAsText("views/todo.html");
    new Todo();
}



