#include <stdio.h>

int main(void) {
	long double l1 = 3044.299692123L;
	long double l2 = 3044.299695123421L;
	long double l3 = 3044.299696123452312L;
	printf("%.19Lf, %.19Lf, %.19Lf\n", l1, l2, l3);
	printf("%.19Lf, %.19Lf\n", l2-l1, l3-l2);
}
