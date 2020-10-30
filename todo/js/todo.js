export default class Todo {
    constructor() {
	    this.getCars();
	    // Selectors
	    document.querySelector('form').addEventListener('submit', this.handleSubmitForm);
    }
	async getCars() {
	  this.cars = await this.loadData('get', 'http://80.240.27.253/cgi-bin/select_cars');
	  this.cars = JSON.parse(this.cars);
	  for(let car of this.cars) {
		console.log(car);
	  }
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

