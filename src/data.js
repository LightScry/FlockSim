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

function drawNodes(){
	var splitNodes = updatedData.split('|');
	
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	for(var x = 0; x < splitNodes.length; x ++){
		var color  = "#00A308";
		var size = 2;
		var coords = splitNodes[x].split(',');
		if(x == splitNodes.length-1){
			color = "#7700ff";
			size = 4;
		}
		//draw a circle
		ctx.beginPath();
		ctx.fillStyle = color;
		ctx.arc(coords[0],coords[1], size, 0, Math.PI*2, true); 
		ctx.closePath();
		ctx.fill();
	}
}

function updateData(){
	tid = setTimeout(updateData, 25); // repeat myself
	sendRequest();
	//console.log(updatedData)
	drawNodes();
}

updateData();
