// when the tag is being dropped into a spot that allows this action
function allowDrop(ev){
    // by default the browser doesn't allow drag and drop
    ev.preventDefault();
}

// when the elem starts being dragged
function drag(ev){
    // store the elems id to transfer it to drop target
    ev.dataTransfer.setData("text", ev.target.id);
}

// when the dragged elem is dropped
function drop(ev){
    ev.preventDefault();
    let data = ev.dataTransfer.getData("text");
    // appends the dragged elem to the drop target
    ev.target.appendChild(document.getElementById(data));
}

