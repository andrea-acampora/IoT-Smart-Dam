$(document).ready(function () {
	while(true){
	    $.getJSON('http://8738a3a6495e.ngrok.io/api/data', function (data) {
            var rilevazione = `WaterLevel: ${data[0].value}<br>
                    State: ${data[0].state}<br>
                    TimeStamp: ${data[0].timeStamp}`
            $(".mypanel").append(rilevazione); 
    		});
	}

});
