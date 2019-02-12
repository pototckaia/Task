'use strict';

var fs = require('fs');

var str = fs.readFileSync('input.txt', 'UTF-8');


var digit = str.split('\n');

var i;


var count_digit = new Array(10);

count_digit.fill(0);

for (i = 0; i < digit.length - 1; i++) {
	digit[i] = parseInt(digit[i + 1], 10);
}



for (i = 0; i < digit.length - 1; i++) {
	count_digit[parseInt(digit[i], 10)]++;
}


var buf = count_digit[0];
var out_str = '';


for (i = 1; i < count_digit.length; i++) {
	out_str += count_digit[i] + ' ';
}
out_str += buf;

fs.writeFileSync('output.txt', out_str);

