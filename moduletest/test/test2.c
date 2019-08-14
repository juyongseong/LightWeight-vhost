#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

struct timeval start_point, end_point;
double operating_time;


void f1() {
	gettimeofday(&start_point, NULL);
	usleep(1);
	gettimeofday(&end_point, NULL);
	operating_time = (double)(end_point.tv_sec)+(double)(end_point.tv_usec)/1000000.0-(double)(start_point.tv_sec)-(double)(start_point.tv_usec)/1000000.0;
	printf("%ld, %ld\n", start_point.tv_sec, end_point.tv_sec);
	printf("%ld, %ld\n", start_point.tv_usec, end_point.tv_usec);
	printf("%f\n", operating_time);
}

void f2() {
	gettimeofday(&start_point, NULL);
	usleep(2);
	gettimeofday(&end_point, NULL);
	operating_time = (double)(end_point.tv_sec)+(double)(end_point.tv_usec)/1000000.0-(double)(start_point.tv_sec)-(double)(start_point.tv_usec)/1000000.0;
	printf("%ld, %ld\n", start_point.tv_sec, end_point.tv_sec);
	printf("%ld, %ld\n", start_point.tv_usec, end_point.tv_usec);
	printf("%f\n", operating_time);

	
}

void f3() {
	gettimeofday(&start_point, NULL);
        usleep(3);
        gettimeofday(&end_point, NULL);
        operating_time = (double)(end_point.tv_sec)+(double)(end_point.tv_usec)/1000000.0-(double)(start_point.tv_sec)-(double)(start_point.tv_usec)/1000000.0;
        printf("%ld, %ld\n", start_point.tv_sec, end_point.tv_sec);
	printf("%ld, %ld\n", start_point.tv_usec, end_point.tv_usec);
        printf("%f\n", operating_time);
}
void f4() {
	gettimeofday(&start_point, NULL);
        usleep(47);
        gettimeofday(&end_point, NULL);
        operating_time = (double)(end_point.tv_sec)+(double)(end_point.tv_usec)/1000000.0-(double)(start_point.tv_sec)-(double)(start_point.tv_usec)/1000000.0;
        printf("%ld, %ld\n", start_point.tv_sec, end_point.tv_sec);
        printf("%ld, %ld\n", start_point.tv_usec, end_point.tv_usec);
        printf("%f\n", operating_time);
}
int main(void) {
	f1();
	f2();
	f3();
	f4();
}

