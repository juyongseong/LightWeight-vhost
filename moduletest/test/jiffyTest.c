#include <stdio.h>
#include <linux/jiffies.h>

extern usigned long volatile jiffies;

void f() {
	usigned long time_stamp = jiffies;
	for(int i=0; i<100000000; i++) {
		int j=0;
		j++;
	}
	usingned long time_next = jiffies;
	usingned long time_btween = time_next - time_stamp;
	printf("%d\n", time_btween);
}

int main(void) {
	f();
}
