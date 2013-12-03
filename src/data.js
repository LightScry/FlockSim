
k = 2
URL = "http://0.0.0.0:8000/node_data.json"

$.getJSON(URL, function() {
  alert("success");
})
.success(function() { alert("second success"); })
.error(function(jqXHR, textStatus, errorThrown) {
		x  = JSON.parse( jqXHR.responseText )
        console.log(x)
    })
.complete(function() { alert("complete"); });

var myJSONObject = {"bindings": [
        {"ircEvent": "PRIVMSG", "method": "newURI", "regex": "^http://.*"},
        {"ircEvent": "PRIVMSG", "method": "deleteURI", "regex": "^delete.*"},
        {"ircEvent": "PRIVMSG", "method": "randomURI", "regex": "^random.*"}
    ]
};
myJSONObject.bindings[0].method    // "newURI"
console.log(myJSONObject.bindings[0].method)