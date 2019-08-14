#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <stdlib.h>
#include <linux/delay.h>
#include <linux/time.h>
struct timespec start_point, end_point;
long double operating_time;

extern void f1(void) {
        getnstimeofday(&start_point);
        msleep(1);
        getnstimeofday(&end_point);
        //operating_time = (long double)((long double)(end_point.tv_sec-start_point.tv_sec)+(long double)(end_point.tv_nsec/1000000-start_point.tv_nsec/1000000)/1000000.0);
        printk("%ld, %ld\n", start_point.tv_sec, end_point.tv_sec);
        printk("%ld, %ld\n", start_point.tv_nsec, end_point.tv_nsec);
        //printk("%Lf\n", operating_time);
}

extern void f2(void) {
	msleep(1);
}

static int __init init_hello(void){
        printk(KERN_ALERT "Hello, kernel!\n");
	f1();
	f2();
        return 0;
}

static void __exit exit_hello(void){
        printk(KERN_ALERT "Good-bye, kernel!\n");
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
