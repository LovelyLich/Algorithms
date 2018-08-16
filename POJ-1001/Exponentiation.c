#include <stdio.h>
#include <string.h>
#include <math.h>

#define INIT_LEN 6
#define MAX_LEN 150
#define LINE_SZ 100

int input[MAX_LEN];
int mid[MAX_LEN];
int result[MAX_LEN];

//get the number length
int get_number_length(int *array, int max_len) {
	int i;

	for (i = max_len-1; i >=0; i--) {
		if (array[i] != 0) {
			break;
		}
	}

	return i+1;
}
/*
 * @exp: exponential number
 */
int exponential(int exp) {
	int i = 0;
	int k = 0;
	int m = 0;
	int init_len = get_number_length(input, MAX_LEN);

	//init mid with input
	memset(mid, 0, MAX_LEN * sizeof(int));
	for (i = 0; i < init_len; i++) {
		mid[i] = input[i];
	}
	if (exp < 2) {
		for(i=0; i < init_len; i++) {
			result[i] = input[i];
		}
		return 0;
	} 
	//start multiply: input ^2...exp
	for (k = 2; k <= exp; k++) {
		int mid_len = get_number_length(mid, MAX_LEN);
		int j;

		memset(result, 0, MAX_LEN * sizeof(int));
		for (i = 0; i < init_len; i++ ) {
			for (j = 0; j < mid_len; j++) {
				result[i + j] += input[i]  * mid[j];

				//发生进位
				for (m = i + j; m < MAX_LEN; m++) {
					if (result[m] >= 10) {
						result[m + 1] += result[m] / 10;
						result[m] = result[m] % 10;
					} else
						break;
				}
			}
		}
		//copy result back to mid
		memset(mid, 0, MAX_LEN * sizeof(int));
		for (i = 0; i < get_number_length(result, MAX_LEN); i++) {
			mid[i] = result[i];
		}
	}
	return 0;
}

int read_args(char *line, int *exp, int *npoint) {
	char *p =  line;
	char c;
	int max_index = 0;
	int i = 0;
	int point_num = 0;

	while(*p != ' ' && *p != '\n') {
		c = *p;
		point_num++;
		if (c == '.') {
			point_num = 0;
			p++;
			continue;
		}
		if (max_index + 1 > INIT_LEN -1)
			return 0;
		for (i = max_index+1;i>0; i--) {
			input[i] = input[i-1];
		}
		input[0] = c - 48;
		max_index++;
		p++;
	}
	sscanf(p, " %d", exp);
	*npoint = point_num;
	return 1;
}

int main(int argc, char **argv) {
	while (1) {
		int exp;
		int i, j;
		int npoint;
		int len, integer_len;
		char line[LINE_SZ];

		memset(input, 0, 6 * sizeof(int));
		memset(mid, 0, MAX_LEN * sizeof(int));
		memset(result, 0, MAX_LEN * sizeof(int));

		if (fgets(line, LINE_SZ, stdin) && read_args(line, &exp, &npoint)) {
			exponential(exp);
		} else {
			break;
		}
		npoint  = npoint * exp;
		len = get_number_length(result, MAX_LEN);
		//浮点部分省略0
		for (i=0; i < npoint; i++) {
			if (result[i] != 0)
				break;
		}
		//处理移动
		if (i > 0) {
			for (j=0;  j + i < len; j++) {
				result[j] = result[i+j];
				result[i+j] = 0;
			}
		}
		//小数位不够，补充0
		if (len <= npoint) {
			printf(".");
			for (i=npoint - len; i >0; i--) {
				printf("0");
			}
			for (i = len-1; i >= 0; i--) {
				printf("%d", result[i]);
			}
		} else {
			j = get_number_length(result, MAX_LEN);
			for(i= j-1; i >=0; i--) {
				if (j - 1 - i == len - npoint) {
					printf(".");
				}
				printf("%d", result[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
