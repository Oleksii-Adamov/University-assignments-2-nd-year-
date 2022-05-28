window.onload = init;
function init() {
	var addButton = document.getElementById("addButton");
	addButton.onclick = AddToPlayList;
	var deleteButton = document.getElementById("deleteButton");
	deleteButton.onclick = DeleteFromPlayList;
	loadPlaylist();
	console.log("Init");
}
function AddToPlayList() {
	console.log("Add");
	var textInput = document.getElementById("songTextInput");
	var songName = textInput.value;
	var li = document.createElement("li");
	li.innerHTML = songName;
	var ul = document.getElementById("playlist");
	ul.appendChild(li);
	save(songName);
}

function DeleteFromPlayList() {
	var textInput = document.getElementById("songTextInput");
	var songName = textInput.value;
	var ul = document.getElementById("playlist");
	for (var i = 0; i < ul.children.length; i++) {
		if (ul.children[i].innerHTML == songName) {
			ul.removeChild(ul.children[i]);
			break;
		}
	}
	del(songName);
}
