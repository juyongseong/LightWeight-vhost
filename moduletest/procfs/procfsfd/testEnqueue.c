#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc,char** argv){
	
	int fd=open("/proc/kboard/enqueue",O_WRONLY);
	if(argc != 2){
        	printf("testEnqueue: invalid argument");
        	return -1;
    	}
	
	int res;
    
        res= write(fd,argv[1],sizeof(argv[1]));
        if(res==-1){
            printf("now ring buffer full\n");
        }else{
            printf("enqueue %s\n",argv[1]);
        }
	close(fd);
}
