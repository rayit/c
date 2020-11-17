export default class Table {

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
}