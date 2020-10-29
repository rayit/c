// Load data from DB
(function() {
var xhr = new XMLHttpRequest();

xhr.onload = function() {
	// process our return data
	if (xhr.status >= 200 && xhr.status < 300 ) {
		console.log('success!', xhr);
		let ul = document.querySelector('ul');
		let cars = JSON.parse(xhr.response);
		for(let i=0; i< cars.length; i++) {
			let car = cars[i];
			let li = document.createElement('li');
			li.innerHTML = `
				<span class="todo-item">${car.name}</span>
			`;
			li.classList.add('toto-list-item');
			ul.appendChild(li);
		}
	} else {
		console.log('The request failed...');
	}
};
xhr.open('GET', 'http://80.240.27.253/cgi-bin/select_cars');
xhr.send();

})();

// submit form
document.querySelector('form').addEventListener('submit', handleSubmitForm);

function handleSubmitForm(e) {
	e.preventDefault();
	let input = document.querySelector('input');
	if (input.value != '' )
		addTodo(input.value);
	input.value = '';
}

function addTodo(todo) {
	let ul = document.querySelector('ul');
	let li = document.createElement('li');
	li.innerHTML = `
		<span class="todo-item">${todo}</span>
	`;
	li.classList.add('toto-list-item');
	ul.appendChild(li);
}
