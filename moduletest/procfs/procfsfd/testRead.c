#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#define MAX_LEN (11)

int main(){
	
	int fd=open("/proc/kboard/reader",O_RDONLY);
	char buf[MAX_LEN];
	int n;
	int readRes;
	
	readRes = read(fd,buf,sizeof(buf));
	n=atoi(buf);
	if(!readRes){
		if(n==-1){
			printf("now ring buffer empty\n");
			return -1;
			}
	}else{
		printf("read fail\n");
		return -1;
	}
	printf("dequeue %d\n",n);

	close(fd);
}
