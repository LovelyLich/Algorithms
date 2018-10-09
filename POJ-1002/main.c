#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SZ 100
#define NUM_SZ 7

int parse_line_into_number(const char *line, int len) {
	int i;
	int j;
	const char *p = line;
	int result[NUM_SZ] = {0};
	int ret = 0;

	for (i = 0, j = 0; i < strlen(line); i++) {
		if (*(p+i) == '-')
			continue;
		switch(*(p+i)) {
		case 'A':
		case 'B':
		case 'C':
			result[j] = 2;
			j++;
			break;
		case 'D':
		case 'E':
		case 'F':
			result[j] = 3;
			j++;
			break;
		case 'G':
		case 'H':
		case 'I':
			result[j] = 4;
			j++;
			break;
		case 'J':
		case 'K':
		case 'L':
			result[j] = 5;
			j++;
			break;
		case 'M':
		case 'N':
		case 'O':
			result[j] = 6;
			j++;
			break;
		case 'P':
		case 'R':
		case 'S':
			result[j] = 7;
			j++;
			break;
		case 'T':
		case 'U':
		case 'V':
			result[j] = 8;
			j++;
			break;
		case 'W':
		case 'X':
		case 'Y':
			result[j] = 9;
			j++;
			break;
		default:
			result[j]= *(p+i) - 48;
			j++;
			break;
		}
	}

	//转换为数字
	for (j = 0; j < NUM_SZ; j++) {
		ret += result[j] * pow(10, NUM_SZ - j - 1);
	}
	return ret;
}

int cmp(const void *v1, const void* v2) {
	int *x =(int *)v1;
	int *y =(int *)v2;
	return (*x) - (*y);
}
int main(int argc, char **argv) {
	char line[LINE_SZ] = {0};
	int line_num;
	int *phones = NULL;
	int i = 0;
	int dup_cnt = 1;
	int dup_exist = 0;

	scanf("%d ", &line_num);

	phones = calloc(line_num, sizeof(int));
	if (!phones)
		return 0;

	while(i < line_num && fgets(line, LINE_SZ, stdin) != NULL) {
		int phone_num;

		phone_num = parse_line_into_number(line, LINE_SZ);
		phones[i++] = phone_num;
	}

	qsort(phones, line_num, sizeof(int), cmp);

	for (i = 0; i < line_num; i++) {
		if (phones[i] == phones[i + 1]) {
			dup_exist = 1;
			dup_cnt++;
		} else if (dup_cnt > 1) {
			printf("%03d-%04d %d\n", phones[i] / 10000, phones[i] % 10000, dup_cnt);
			dup_cnt = 1;
		}
	}
	if (!dup_exist)
		printf("No duplicates.\n");
}
