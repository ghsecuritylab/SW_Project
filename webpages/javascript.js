let status = 2;

// constants for variable status
const ADMIN_PRIVILAGE = 0;
const USER_PRIVILAGE = 1;
const OTHER_PRIVILAGE = 2;

// parameter from board
const ADMIN_ADDED = 3;

function httpGetAsync(theUrl, callback) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
	    if (xmlHttp.readyState == 4 && xmlHttp.status == 200 && callback !== undefined)
	        callback(xmlHttp.responseText);
	}
	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
	xmlHttp.send(null);
}

function addAdmin() {
	httpGetAsync('/addadmin');
	async_alert('Waiting for tag');
}

function logout() {
	httpGetAsync('/logout');
}

function async_alert(str) {
	setTimeout( () => alert(str) );
}

function twiddleDOM(param) {
	if(status == param) {
		return;
	}
	if (param == ADMIN_PRIVILAGE) {
		document.getElementById("b-blue").disabled = false;
		document.getElementById("b-red").disabled = false;
		document.getElementById("submit").disabled = false;
		document.getElementById("logout").disabled = false;
		status = param;
		async_alert("Logged as admin");
	} else if (param == USER_PRIVILAGE) {
		document.getElementById("b-blue").disabled = false;
		document.getElementById("b-red").disabled = true;
		document.getElementById("submit").disabled = true;
		document.getElementById("logout").disabled = false;
		status = param;
		async_alert("Logged as user");
	} else if (param == OTHER_PRIVILAGE) {
		document.getElementById("b-blue").disabled = true;
		document.getElementById("b-red").disabled = true;
		document.getElementById("submit").disabled = true;
		document.getElementById("logout").disabled = true;
		status = param;
	} else if (param == ADMIN_ADDED) {
		async_alert("Admin added");
		return;
	}
}

setInterval(function() {
	httpGetAsync('/status', twiddleDOM);
}, 500);
