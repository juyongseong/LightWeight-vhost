/********************************************************
********함수가 시작되고 종료되기 까지의 시간 측정********
********************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <stdlib.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/string.h>

//struct timespec start_point, end_point;
//int sec;
//long nsec;
#define MAX_FUNC 20					//허용가능한 함수의 개수
int fperf_num=0;					//현재 함수의 개수

struct fperf {
	const char* str;
	struct timespec start_point, end_point;
	int sec;					//아직 미사용 총합?
	long nsec;					//"
};

struct fperf fperf_arr[MAX_FUNC];			//배열대신 맵이나 벡터등을 사용할수 있을까?(속도측면,,)

inline void fperf_start(const char * str) {
	int i;
	struct fperf *fpp=NULL;
	
	for(i=0; i<fperf_num; i++) {			//배열에 포함되어있는지 확인
		if(strcmp(fperf_arr[i].str, str)==0) {	//함수이름 비교
			fpp = &fperf_arr[i];
			break;
		}
	}
	if(fpp == NULL) {					//등록된 함수가 없다면 추가
		fperf_num++;
		fpp = &fperf_arr[fperf_num-1];
		fpp->str = str;
		fpp->sec =0;
		fpp->nsec =0;
		getnstimeofday(&(fpp->start_point));
	}
	 getnstimeofday(&(fpp->start_point));
}

inline void fperf_end(const char * str) {
	int i, sec;
	long nsec;
	struct fperf *fpp=NULL;
	struct timespec temp;
	getnstimeofday(&temp);

	for(i=0; i<fperf_num; ++i) {
		if(strcmp(fperf_arr[i].str, str)==0) {
			fpp = &fperf_arr[i];
			break;
		}
	}
	if(fpp != NULL) {				//널포인터가 아니라면 => 등록된 함수라면
		fpp->end_point = temp;
		sec = fpp->end_point.tv_sec - fpp->start_point.tv_sec;
        	nsec = fpp->end_point.tv_nsec - fpp->start_point.tv_nsec;
		fpp->sec += sec;
		fpp->nsec += nsec;
		if(fpp->nsec >= 1000000000) {
			fpp->sec++;
			fpp->nsec-=1000000000;
		}
        	if(sec!=0 && nsec < 0)
                	        nsec = 1000000000 - fpp->start_point.tv_nsec + fpp->end_point.tv_nsec;
        	printk("%s %d.%09ld\n",str, sec, nsec);
	}
}

//#define START long temp; struct timespec point; getnstimeofday(&point); temp=point.tv_nsec;
//#define END getnstimeofday(&point); temp=point.tv_nsec-temp; printk("%s %09ld\n",__func__, temp);;

extern void f1(void) {
	fperf_start(__func__);
	//START;
       // msleep(20);
	fperf_end(__func__);
	//END;
}

extern void f2(void) {
	fperf_start(__func__);
	//START;
        //msleep(10);
	fperf_end(__func__);
	//END;
}
extern void f3(void) {
	fperf_start(__func__);
	//START;
	//msleep(1);
	fperf_end(__func__);
	//END;
	return;
}
extern void f11(int i) {
        fperf_start(__func__);
	//START;
        msleep(20);
	i++;
	printk("%d", i);
        fperf_end(__func__);
	//END;
}

extern void f22(int i) {
        fperf_start(__func__);
	//START;
        msleep(10);
	f11(i+1);
        fperf_end(__func__);
	//END;
}
extern void f33(int i) {
        fperf_start(__func__);
	//START;
        msleep(1);
	f22(i+1);
        fperf_end(__func__);
	//END;
}

static int __init init_hello(void){
        printk(KERN_ALERT "Hello, kernel!\n");
	printk(KERN_ALERT "test1\n");
	f1();
	f2();
	f3();
	printk(KERN_ALERT "test2\n");
	f33(1);
	return 0;
}

static void __exit exit_hello(void){
	int i;
        printk(KERN_ALERT "Good-bye, kernel!\n");
	printk("total run time\n");
	for(i=0; i<fperf_num; ++i) {
		printk("%s %d.%09ld\n",fperf_arr[i].str, fperf_arr[i].sec, fperf_arr[i].nsec);
	}
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
