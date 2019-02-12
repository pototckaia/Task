#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *createSet(int size){
	int *disjointedSet = (int *) malloc(size * sizeof(int));
	for (int i = 0; i < size; i++){
		disjointedSet[i] = i;
	}
	return disjointedSet;
}

int find(int *disjointedSet, int x){
	if (x == disjointedSet[x]){
		return x;
	}
	else{
		disjointedSet[x] = find(disjointedSet, disjointedSet[x]);
		return disjointedSet[x];
	}
}

int merge(int *disjointedSet, int rep_a, int rep_b){
	rep_a = find(disjointedSet,rep_a);
	rep_b = find(disjointedSet,rep_b);
	if (rep_a == rep_b){
		return 0;
	}
	disjointedSet[rep_b] = rep_a;
	return 1;
}

int main(){
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	
	char *line_p = (char *) malloc(5001 * sizeof(char)); 

	int m = 0;
	char c;
	while ((c = fgetc(input)) != '\n' && !feof(input)){
		line_p[m] = c;
		m++;
	}
	int *disjointedSet = createSet(2 * m);
	int create_count = 0;

	for (int i = 0; i < m; i++){
		if (line_p[i] != ' '){
			disjointedSet[i] = -1; 
			continue;
		}
		if (i == 0 || disjointedSet[i - 1] == -1){
			disjointedSet[i] = i;
			create_count += 1;
		}
		else{
			disjointedSet[i] = disjointedSet[i - 1];	
		}
	}
	int rooms_count = create_count;
	int merge_count = 0;
	int prev_offset = 0;
	int cur_offset = m;

	while (!feof(input)){
		prev_offset = abs(cur_offset - m);
		create_count = 0;
		merge_count = 0;
		int k = 0;
		while ((c = fgetc(input)) != '\n' && !feof(input)){ 			
			if (c != ' '){
				disjointedSet[cur_offset + k] = -1;
				k++; 
				continue;
			}
			if (k == 0 || disjointedSet[cur_offset + k - 1] == -1){
				disjointedSet[cur_offset +  k] = cur_offset + k;
				create_count += 1;
			}
			else{
				disjointedSet[cur_offset + k] = disjointedSet[cur_offset + k - 1];	
			}
			k++;
		}
		for (int i = 0; i < m; i++){
			if (disjointedSet[cur_offset + i] != -1 && disjointedSet[prev_offset + i] != -1){
				if (merge(disjointedSet, cur_offset+i, prev_offset+i))
					merge_count += 1;				
			}
		}
		cur_offset = abs(cur_offset - m);
		rooms_count += create_count - merge_count;
	}

	fprintf(output, "%d\n", rooms_count);
   	free(line_p);
   	free(disjointedSet);
}