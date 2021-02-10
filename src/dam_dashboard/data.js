$(document).ready(function () {

	let levels = [];
	let x = 0;
	let y = 0;
	const levels_length = 6
	let requestLoop = setInterval(function () {
		$.getJSON('http://042c464fe0ae.ngrok.io/api/data', function (data) {
			
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

			$(".state").text(state);

			if ("level" in data) {
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
				
				$(".prev-levels").append(result);
				let current = `<div>` + levels[levels.length - 1][0] + `</div>`;
	
				$(".current-level").append(current);
			}else{
				levels = []; 
			}

			if("mode" in data) {
				mode = data.mode;
				$(".mode").text(mode);
			}
			
			if("opening" in data) {
				opening = data.opening;
				$(".opening").text(opening);
			}
		});
	}, 5000);


});
