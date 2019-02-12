'use strict';

var fs = require('fs');
var in_str = fs.readFileSync('input.txt', 'UTF-8');

var program = in_str.split('\n');

var len = parseInt(program[0]);
var index_eq = 0;
var i = 0;

var  var_stack = [];
var out_str = '';


var search_varib = function(name) {
	var j = var_stack.length - 1;
	var varib = var_stack[j];
	while (varib.name !== name) {
		j--;
		varib = var_stack[j];
	}
	return j;

}



for (i = 1; i <= len; i++) {
	program[i] = program[i].trim();
	
	if (program[i] === '{') {
		var separ = {};
		separ.name = '{';
		separ.value = undefined;
		var_stack.push(separ);
	}
	else if (program[i] === '}') {
		var k = {};
		while (k.name != '{'){
			k = var_stack.pop();
		};
	}
	else if (program[i].slice(0, 3) === 'int') {
		var varib = {};
		varib.name = program[i].slice(4).trim();
		varib.value = 0;
		var_stack.push(varib);
	}
	else if (program[i].slice(0, 5) === 'print') {
		var index = search_varib(program[i].slice(6).trim());
		out_str += var_stack[index].value + '\n';
	}
	
	index_eq = 0;
	if ((index_eq = program[i].search('=')) !== -1) {
		var recipient_name = program[i].slice(0, index_eq).trim();
		var premise_val = program[i].slice(index_eq + 1).trim();
		
		if (isNaN(premise_val)) {
			premise_val = var_stack[search_varib(premise_val)].value;
		}
		var recipient_varib = var_stack[search_varib(recipient_name)];
		recipient_varib.value = premise_val;
	}
}

fs.writeFileSync('output.txt', out_str);
