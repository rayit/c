export default class Todo {
    todos = null;

    constructor() {
        // Load data from DB
	    this.todos = this.getTodos();
	    // Selectors
	    document.getElementById('todoForm').addEventListener('submit', this.handleSubmitForm.bind(this));
    }

    // TODO Move to some general class
    createTable(parentId, columns, data) {
        // Create and add table
        let table = document.createElement('table');
        let header = table.createTHead();
        let row = header.insertRow(-1);
        const columnCount = columns.length;
        for( let i=0; i < columnCount; i++) {
            let headerCell = document.createElement('th');
            headerCell.innerText = columns[i].toUpperCase();
            row.appendChild(headerCell)
        }
        let tBody = table.createTBody();
        let rowCount = data.length;
        for( let i=0; i < rowCount; i++) {
            let rowT = tBody.insertRow(-1);
            for(let j=0;j< columnCount; j++) {
                let cell = rowT.insertCell(-1);
                cell.setAttribute('data-label', columns[j].toUpperCase());
                let obj = data[i];
                cell.innerText = obj[columns[j]];
            }
        }
        document.getElementById(parentId).appendChild(table);
    }

	async getTodos() {
	  let todos = await this.loadData('get', '/cgi-bin/select_todo');
	  this.todos = JSON.parse(todos);
	  this.createTable('todoTable', ['id', 'name'], this.todos);
	}

    // Event handler function
    handleSubmitForm(e) {
        e.preventDefault();
        let input = document.querySelector('input');
        if( input.value != '') {
            this.addTodo(input.value);
            input.value = '';
        }
    }

    // Helpers
    addTodo(todo) {
        let ul = document.querySelector('.todo');
        let li = document.createElement('li');
        li.innerHTML = `
            <span class="todo-item">${todo}</span>
            <button name="checkButton"><i class="fas fa-check-square"></i></button>
            <button name="deleteButton"><i class="fas fa-trash"></i></button>`;
        li.classList.add('todo-list-item');
        ul.appendChild(li);
    }

	loadData(method = get, url) {
		 return new Promise(function (resolve, reject) {
        let xhr = new XMLHttpRequest();
        xhr.open(method, url);
        xhr.onload = function () {
            if (this.status >= 200 && this.status < 300) {
                resolve(xhr.response);
            } else {
                reject({
                    status: this.status,
                    statusText: xhr.statusText
                });
            }
        };
        xhr.onerror = function () {
            reject({
                status: this.status,
                statusText: xhr.statusText
            });
        };
        xhr.send();
    	});
	}
}

