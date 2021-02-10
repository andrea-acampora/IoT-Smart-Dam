$(document).ready(function () {
	
	let levels = []; 
	let x = 0 ; 
	let y = 0; 
	const levels_length = 6
	let requestLoop = setInterval(function(){
		$.getJSON('https://jsonplaceholder.typicode.com/todos/1', function (data) {
			 console.log(data);
			let state = data.state; 
			let level = data.level; 
			let mode = data.mode; 
			let opening = data.opening; 
			let timestamp = data.timestamp; 

			levels.push(new Array(level, timestamp));
			if(levels.length > levels_length){
				levels.shift(); 
			}

			console.log(levels); 

			let result = ""; 
			for(let i = 0; i < levels.length-1; i++){
				result += `<div>`+ levels[i][0] + ` - `+ levels[i][1]+`</div>`; 
			}
			$(".prev-levels").empty();
			$(".prev-levels").append(result);


			let current = `<div>`+ levels[levels.length-1][0] + `</div>`; 
			
			$(".current-level").empty();
			$(".current-level").append(current);

			$(".state").empty(); 
			$(".mode").empty(); 
			$(".opening").empty(); 

			$(".state").text(state); 
			$(".mode").text(mode); 
			$(".opening").text(opening); 
		});
	}, 5000); 

	   
});
