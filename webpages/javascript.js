function httpGetPrivilageAsync(theUrl, callback) {
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
	    if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
	        callback(xmlHttp.responseText);
	}
	xmlHttp.open("GET", theUrl, true); // true for asynchronous 
	xmlHttp.send(null);
}

function twiddleDOM(param) {
	if (param == 0) {
		document.getElementById("b-blue").disabled = false;
		document.getElementById("b-red").disabled = false;
		document.getElementById("input").disabled = false;
		document.getElementById("submit").disabled = false;
		document.getElementById("logout").disabled = false;
	} else if (param == 1) {
		document.getElementById("b-blue").disabled = false;
		document.getElementById("b-red").disabled = true;
		document.getElementById("input").disabled = true;
		document.getElementById("submit").disabled = true;
		document.getElementById("logout").disabled = false;
	} else {
		document.getElementById("b-blue").disabled = true;
		document.getElementById("b-red").disabled = true;
		document.getElementById("input").disabled = true;
		document.getElementById("submit").disabled = true;
		document.getElementById("logout").disabled = true;
	}
}

setInterval(function() {
	httpGetPrivilageAsync('/status', twiddleDOM);
}, 500);
