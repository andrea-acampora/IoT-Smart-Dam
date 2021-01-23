$(document).ready(function () {
    $.getJSON('http://time.jsontest.com', function (data) {
            var rilevazione = `WaterLevel: ${data.value}<br>
                    State: ${data.state}<br>
                    TimeStamp: ${data.timeStamp}`
            $(".mypanel").append(rilevazione); 
    });
});
