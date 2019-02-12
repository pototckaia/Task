'use strict';

var fs = require('fs');
var in_str = fs.readFileSync('input.txt', 'UTF-8');

var number = in_str.split(/\s+/g);

var len = number[0];
var i = 0;
var j = 0;
var max_a = 0;

for (i = 0; i < len; i++) {
	number[i] = parseInt(number[i + 1]);
	if (number[i] > max_a) 
		max_a = number[i]; 
}

var out = '';
var line = '';


for (i = 0; i < max_a + 3; i++) {
	line = '';
	for (j = 0; j < len; j++) {
		if (i === 0) {
			line += '-+---+'; 
		}
		else if (i === number[j] + 1) {
			line += '.+---+'; 
		}
		else if (i <= number[j]) {
			line += '.|###|';	
		}
		else if (i > number[j] + 1) {
			line += '......'
		}
	}
	line += (i === 0 ? '-' : '.');
	out = line + '\n' + out;
}

fs.writeFileSync('output.txt', out);
