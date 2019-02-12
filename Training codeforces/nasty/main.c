#include <stdio.h>
#include <stdlib.h>


int check(char * m, char * pm, int * buf){
	
	int j = 0, i = 0;
	while ( m[i] != '\0' && pm[j] != '\0') {
		if (m[i] == pm[j] && buf[i] != -1)
			j++;
		i++;
	}
	return ( pm[j] == '\0' ? 1 : 0);
}

int main(){
	char *word, *answer;
	int *position, *dash;
	char buf;
	
	int size_word = 0, n = 4;
	word = (char *) malloc(n * sizeof(char));
	while( (buf = (char) getchar()) != '\n'){
		word[size_word] = buf;
		if (++size_word >= n) {
			n *= 2;
			word = (char *) realloc(word, n);
		}
		word[size_word] = '\0'; 
	}

	int m = 4, size_ans = 0;
	answer = (char *) malloc(m * sizeof(char));
	while( (buf = (char) getchar()) != '\n'){
		answer[size_ans] = buf;
		if (++size_ans >= m) {
			m *= 2;
			answer = (char *) realloc(answer, m);
		}
		answer[size_ans] = '\0'; 
	}	

	dash = (int *) calloc(size_word, sizeof(int));
	position = (int *) malloc(size_word * sizeof(int));
	
	for (int i = 0; i < size_word; i++)
		scanf("%d", &position[i]);

	int l = 0, r = size_word + 1;
	int med;
	while (r - l > 1){
		med = (r + l) / 2;
		for (int i = 0; i < size_word; i++)
			dash[i] = 0;
		for (int i = 0; i < med; i++)
			dash[position[i] - 1] = -1;
		if (check(word, answer, dash))
			l = med;
		else 
			r  = med; 
	}
	printf("%d\n", l);
}
