#include <stdio.h>
#include <stdlib.h>

int main(){
	/*char* str = (char*) calloc(501, sizeof(char));*/
	char str[501];
	scanf("%s", str);
	
	int *used = (int*) calloc(26, sizeof(int));

	if(str[0] != 'a'){
		printf("NO");
		return 0;
	} 
	used[0] = 1;

	int i = 1;
	while(str[i]){
		if (!used[str[i]-97-1] && str[i] != 'a'){
			printf("NO");
			return 0;
		}
		used[str[i]-97] = 1;
		i++;
	}
	printf("YES");
}