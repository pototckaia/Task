#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **matrix;
int n, m;
double eps = 0.000000012;

void swap_rows(int index1,int index2){
	double *tmp = matrix[index1];
	matrix[index1] = matrix[index2];
	matrix[index2] = tmp;
}

void prin(){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m + 1; j++){
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	freopen("input.txt", "r", stdin); 
	freopen("output.txt", "w", stdout);
	
	scanf("%d %d", &n, &m);
	

	matrix = (double **) malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++){
		matrix[i] = (double *) malloc((m + 1) * sizeof(double));
		for (int j = 0; j < m + 1; j++)
			scanf("%lf", &matrix[i][j]);
	}

	prin();
	
	for (int col = 0, row = 0; col < m && row < n; col++){
		if (col >= n)
			break;
		int h = col;
		for (int j = h + 1; j < n; j++){
			if (abs(matrix[h][col]) < abs(matrix[j][col])){
				h = j;
			}
		}
		if (matrix[h][col] < eps){
			continue;
		}
		swap_rows(col, h);
		prin();
		for (int j = col + 1; j < n; j++){
			double c = matrix[j][col] / matrix[col][col];
			for (int k = col; k < m + 1; k++){
				matrix[j][k] -= matrix[row][k] * c; 
			}
			prin();		
		}
		row++;
	}

	int count = 0;
	int no_solutions = 0;

	for (int row = 0; row < n - count; row++){
		double s = 0;
		for (int col = 0; col < m; col++){
			s += matrix[row][col];
		}

		if (s < eps && matrix[row][m] < eps){
			count++;
			for (int i = row; i < n - 1; i++){
				swap_rows(i, i + 1);
			}
		}
		if (s < eps && matrix[row][m] != 0){
			no_solutions = 1;
			break;
		}
	}


	if (no_solutions && 0){
		printf("%s\n", "Система несовместна\n");
		return 0;
	}

	if (m > n - count){
		printf("%s\n", "Система неопределенная\n");
		return 0;
	}

	for (int row = n - 1 - count; row > 0; row--){
		double c;
		for (int i = row - 1; i >= 0; i--){
			c = matrix[i][row] / matrix[row][row];
			for (int col = row; col < m + 1; col++){
				matrix[i][col] -= matrix[row][col] * c;
			}
		}
	}

	int j = 0;
	for (int i = 0; i < n - count; i++){
		if (matrix[i][j] == 0) continue;
		matrix[i][m] = matrix[i][m] / matrix[i][j];
		j++;
	}

	for (int i = 0; i < n -count; i++){
		printf("x%d = %lf\n", i + 1, matrix[i][m]);
	}
}