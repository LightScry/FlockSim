k = 2
URL = "127.0.0.1:8000/node_data.json"

var updatedData;
var ctx = $('#canvas')[0].getContext("2d");

function sendRequest(){
	$.ajax({
	    url: URL,
	    success: function (data) {
			updatedData = data;
	    },
	    dataType: "html"
	});
}

function drawNodes(){
	var splitNodes = updatedData.split('|');
	
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	for(var x = 0; x < splitNodes.length; x ++){
		var coords = splitNodes[x].split(',');
		//draw a circle
		ctx.beginPath();
		ctx.fillStyle = "#00A308";
		ctx.arc(coords[0],coords[1], 2, 0, Math.PI*2, true); 
		ctx.closePath();
		ctx.fill();
	}
}

function updateData(){
	tid = setTimeout(updateData, 50); // repeat myself
	sendRequest();
	//console.log(updatedData)
	drawNodes();
}

updateData();
