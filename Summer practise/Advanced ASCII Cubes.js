/*
..+---+
./   /|      
+---+ |      
|   | + 
|   |/.
+---+..

*/

'use strict';

var draw_cube = function(x, y, z){
	var xx = x*4+y*2;
	var yy = y*2+z*3;

	cub[xx][yy] = '+';
	cub[xx+4][yy] = '+';
	cub[xx+4][yy+3] = '+';
	cub[xx][yy+3] = '+';
	cub[xx+6][yy+5] = '+';
	cub[xx+2][yy+5] = '+';
    cub[xx+6][yy+2] = "+";


	cub[xx+1][yy+4] = '/';
	cub[xx+5][yy+4] = '/';
    cub[xx+5][yy+1] = "/";
	
	cub[xx][yy+1] = '|';
	cub[xx][yy+2] = '|';
	cub[xx+4][yy+1] = '|';
	cub[xx+4][yy+2] = '|';
    cub[xx+6][yy+3] = "|";
    cub[xx+6][yy+4] = "|";

    cub[xx+5][yy+2] = " ";
	cub[xx+5][yy+3] = " ";
	
	let i = 0, j = 0;
	for (i = 0; i < 3; i++){
		cub[xx+1+i][yy] = '-';
	}
	for (i = 0; i < 3; i++){
		cub[xx+1+i][yy+1] = ' ';
	}
	for (i = 0; i < 3; i++){
		cub[xx+1+i][yy+2] = ' ';
	}
	for (i = 0; i < 3; i++){
		cub[xx+1+i][yy+3] = '-';
	}

	for (i = 0; i < 3; i++){
		cub[xx+2+i][yy+4] = ' ';
	}
	for (i = 0; i < 3; i++){
		cub[xx+3+i][yy+5] = '-';
	}
}

var fs = require('fs');
var str_out = fs.readFileSync('input.txt', 'UTF-8');

var table = str_out.split(/\s+/g);
var n = table[0];
var m = table[1];
table.splice(0, 2);

var max_z = Math.max.apply(null, table);

var cub = [];
var i = 0, j = 0;

for (i = 0; i < m*4+n*2+1; i++){
	cub[i] = [];
}

var z = 0;
var iter = 0;

for (z = 1; z <= max_z; z++){
	iter = 0;
	for (j = n-1; j >= 0; j--){
		for (i = 0; i < m; i++){
			if (parseInt(table[iter]) >= z){
				draw_cube(i, j, z);
			}
			iter++;
		}
	}
}


var max_length = 0;
for (i = 0; i < cub.length; i++){
	max_length = Math.max(max_length, cub[i].length);
}

var b = '', str = '';
for (j = 3; j < max_length; j++){
	b = '';
	for (i = 0; i < cub.length; i++){
		if (cub[i][j] === undefined || cub[i][j] === null){
			b += '.';
		}
		else {
			b += cub[i][j];
		}
	}
	str = b + '\n' + str;
}

fs.writeFileSync("output.txt", str);

