'use strict';

var fs = require('fs');
var str = fs.readFileSync('input.txt', 'UTF-8');

var number = str.split(/\s+/g);


var len = parseInt(number[0]);


var i = 0;
var out = 0;
for (i = 1; i <= len; i++) {
	out += parseInt(number[i]); 
}

fs.writeFileSync('output.txt', out);
