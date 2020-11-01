import Todo from './todo.js';
import Login from './login.js';

window.addEventListener("hashchange",  () => {
    var contentDiv = document.getElementById("app");
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
    const contentDiv = document.getElementById("app");
    contentDiv.innerHTML = await fetchHtmlAsText("views/login.html");
    new Login();
}

async function loadHome() {
    const contentDiv = document.getElementById("app");
    contentDiv.innerHTML = await fetchHtmlAsText("views/home.html");
}

async function loadTodo() {
    const contentDiv = document.getElementById("app");
    contentDiv.innerHTML = await fetchHtmlAsText("views/todo.html");
    new Todo();
}



