'use strict';

var fs = require('fs');
var in_str = fs.readFileSync('input.txt', 'UTF-8');
var  list_str = in_str.split(/\s+/g);

var len = list_str[0];

var max_count = 0;
var out = '';
var i = 0;
var j = 0;
var buf;

var reg = /(^|[^aeiouy])[aeiouy]{2}($|[^aeiouy])/g

for (i = 1; i <= len; i++) {
	j = 0;
	while ((buf = reg.exec(list_str[i]))) {
		j++;
		reg.lastIndex = buf.index + 1;
	}
	if (j === max_count) {
		out = out + list_str[i] + '\n';
	}
	else if (j > max_count) {
		out = list_str[i] + '\n';
		max_count = j;
	}
}

fs.writeFileSync('output.txt', out);