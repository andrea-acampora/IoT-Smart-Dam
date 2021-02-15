$(document).ready(function () {

	let levels = [];
	let x = 0;
	let y = 0;
	const levels_length = 6;
	$(".level-title,.opening-title,.mode-title,.prev-title").hide();
	let requestLoop = setInterval(function () {
		$.getJSON('http://f6ab7aa9c1c8.ngrok.io/api/data', function (data) {
			console.log(data);
			let state = data.state;
			let timestamp;
			let level;
			let mode;
			let opening;
			
			$(".mode").empty();
			$(".state").empty();
			$(".opening").empty();
			$(".prev-levels").empty();
			$(".current-level").empty();
			$(".level-title,.opening-title,.mode-title,.prev-title").hide();

			
			if(state=="ALARM"){
				$(".state").css("color","red");
			}else if(state=="PRE_ALARM"){
				$(".state").css("color","blue");
			}else if(state=="NORMAL"){
				$(".state").css("color","green");
			}
			$(".state").text(state);

			if ("value" in data) {
				timestamp = data.timeStamp;
				level = data.value;
				levels.push(new Array(level, timestamp));
				if (levels.length > levels_length) {
					levels.shift();
				}
				let result = "";
				for (let i = 0; i < levels.length - 1; i++) {
					result += `<div>` + levels[i][0] + ` - ` + levels[i][1] + `</div>`;
				}
				
				$(".prev-title").show();
				$(".prev-levels").append(result);
				let current = `<div>` + levels[levels.length - 1][0];
	
				$(".level-title").show();
				$(".current-level").append(current +" cm </div>");
			}else{
				levels = []; 
			}

			if("modality" in data) {
				mode = data.modality;
				$(".mode-title").show();
				$(".mode").text(mode);
			}
			
			if("opening" in data) {
				opening = data.opening;
				$(".opening-title").show();
				$(".opening").text(opening + " %");
			}
		});
	}, 6000);


});
