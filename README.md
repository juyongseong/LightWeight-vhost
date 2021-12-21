# LightWeight-vhost
## Troubleshooting CPU utilization with virt io
### [NetAP: Adaptive Polling Technique for Network Packet Processing in Virtualized Environments](https://www.mdpi.com/2076-3417/10/15/5219)
--- 

폴더 설명
1. share is record

2. shfile is .sh file

3. moduletest/test is module compile file

4. moduletest/vhost is editing and testing vhost file
test1~4 : 모듈테스트 파일
vhost : 예전에 테스트해보던 파일
vhost2 : 5.1.5 인 현재 버전에서 가져온 vhost파일
vhost_net_save, vhost_netfile : net.c 저장파일
vhost_nowrite : 5.1.5버전 커널 vhost, 수정 x
@@@@@@@@@@@@@@@@@@@@@@@@@@

vhost3 : vhost.ko를 빌드하기 위해만들 파일
vhost4, vhost4_2 : vhost_net.ko를 빌드하기 위해 만든 파일
procfs/procfd : proc파일시스템으로 커널 메모리 수정을 위한 파일

현재 진행중인 vhost 파일은 moduletest/vhost4_2/net.c & moduletest/vhost3/vhost.c입니다.

usleep_range 값을 조정하기 전에는 기존의 vhost와 같은 동작을 합니다.
값은 myteststatus 라는 변수가 가지고 있습니다. 
이 값이 0일경우 기존과 같은 동작을 하고
0이 아닐경우 handle_tx 안에서 handle_tx_zerocopy 와 handle_rx, usleep_range를 반복합니다.

moduletest/procfs/procfd/안의 파일들을 통해서 usleep_range 값을 조정할 수 있습니다.
./testEnqueue.c X : X(숫자) 값으로 입력
./testDequeue.c : 값을 빼고 0으로 초기화
./testRead.c : 값을 읽고 0으로 초기화

그후에 dmesg를 통해서 값이 변경된걸 확인후에 작업을 진행하면 됩니다.
X 값 교체할때는 ./testDequqe.c 로 초기화 한뒤에 ./testEnququ.c X 하면됩니다. (queue에 값이 많이 쌓이면 에러떠서 빼주세요.)

vm 종료시에 usleep_range 값이 0이 아닐경우에는 무한루프에 빠져서 종료가 되지 않습니다.
testDequqe.c이나 testRead.c를 통해서 값이 0이 된것을 dmesg확인한후 vm을 종료합니다.

5. tracefile is ftrace file
