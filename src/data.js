k = 2
URL = "http://127.0.0.1:8000/node_data.json"

var updatedData;
var ctx = $('#canvas')[0].getContext("2d");
var WIDTH = ctx.width
var HEIGHT = ctx.height

function sendRequest(){
	$.ajax({
	    url: URL,
	    success: function (data) {
			updatedData = data;
			//console.log(updatedData);
	    },
	    dataType: "html"
	});
}

function drawNode( color,  size,  coords){
	//draw a circle
	ctx.beginPath();
	ctx.fillStyle = color;
	ctx.arc(coords[0],coords[1], size, 0, Math.PI*2, true); 
	ctx.closePath();
	ctx.fill();
}

function drawNodes(){
	var normalNodes = updatedData.split('@')[0].split('|');
	var targetNodes = updatedData.split('@')[1].split('|');
	var predatorNodes = updatedData.split('@')[2].split('|');
	
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	
	
	// Draw normal nodes
	for(var x = 0; x < normalNodes.length; x ++){
		var coords = normalNodes[x].split(',');
		drawNode("#7700ff",2,coords);
	}
	
	// Draw predator nodes
	for(var x = 0; x < predatorNodes.length; x ++){
		var coords = predatorNodes[x].split(',');
		drawNode("#00A308",5,coords);
	}
	
	// Draw target nodes
	for(var x = 0; x < targetNodes.length; x ++){
		var coords = targetNodes[x].split(',');
		drawNode("#ff7700",5,coords);
	}
}

function updateData(){
	tid = setTimeout(updateData, 25); // repeat myself
	sendRequest();
	//console.log(updatedData)
	drawNodes();
}

updateData();
