#include <stdio.h>

// gcd: 计算两个正整数的最大公约数
// 其中: x >= 0, 且 y >= 0
unsigned int gcd(unsigned int x, unsigned int y) {
	int t;

	while(1) {
		//打印每步中的过程
		printf("x=%u, y=%u\n", x, y);
		if (y == 0) {
			return x;
		} else {
			t = y;
			y = x % y;
			x = t;
		}
	}
}

//求两个数的最小值
unsigned int liyi_min(unsigned int x, unsigned int y) {
	return x > y ? y : x;
}

//求一个数的绝对值
unsigned int liyi_abs(int x) {
	return x * ((x > 0) - (x < 0));
}

int main(int argc, char *argv[]) {
	int a, b;

	scanf("%d%d", &a, &b);
	unsigned int ret = a > b ? gcd(a, b):gcd(b, a);
	printf("%u\n", ret);
	return 0;
}
