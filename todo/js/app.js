import Todo from './todo.js';

window.addEventListener("hashchange",  () => {
    console.log('hash')

    var contentDiv = document.getElementById("app");
    contentDiv.innerHTML = location.hash;
    switch(location.hash) {
        case '#todo':
            loadTodo();
            break;
        default:
            loadHome();
    }
});

async function fetchHtmlAsText(url) {
    const response = await fetch(url);
    return await response.text();
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



