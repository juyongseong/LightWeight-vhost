Project LightWeight-vhost, Troubleshooting CPU utilization with virtio
===

### 논문 : [NetAP: Adaptive Polling Technique for Network Packet Processing in Virtualized Environments](https://www.mdpi.com/2076-3417/10/15/5219)
--- 

구성
=====
 - 환경
 	- ubuntu 18.04 LTS
 	- linux-5.1.5
 	- 10GbE NIC
 	- kvm(QEMU emulator version 2.5.0, 1:2.5+dfsg-5ubuntu10.30)
 	- Netperf-2.6.0-2 ([netperf란?](https://jjudrgn.tistory.com/32))




환경설정
=====
 - kvm 설치(openstack 사용중일 경우 생략)
 	- #egrep -c '(vmx|svm)' /proc/cpuinfo	// cpu가 하드웨어적인 가상화를 지원하는지 확인
 	- 0 : 지원x, -> QEMU를 이용하여 반가상화(하드웨어를 에뮬레이터 하는 방식)로 지원하는 QEMU를 사용하게 되며
 		-  kvm관련 패키리와 QEMU를 함께설치후 kvm그룹에 사용자 추가
 		-  가상 머신추가시 가상화 네트워크와 메모리를 사용
 		-  출처 : http://rockball.tistory.com/entry/Ubuntu-KVM-%EC%84%A4%EC%B9%98
 	- 1 이상 : 지원o -> 전가상화(하드웨어를 hypervisor를 통해 사용)

 - ㅁㄴㅇ

기존의 문제점
=====
 - Efficiency
 	- virt io 방식의 CPU utilization 문제
 	- 낮은 네트워크 성능에서 오히려 더 높은 CPU 사용량이 나오는 경우가 발견. 


#### 사용방법
실행법
Xshell을 8개(netserver : 6, jy-os(host os) : 2) 키고 개하단의 To All Shell을 사용한다.
netserver
ssh ubuntu@10.0.0.2 
ubuntu//ubuntu
make한 vhost, vhost_net을 insmod한다. @host os 
vhost, vhost_net 순으로 insmod하고 vhost_net, vhost 순으로 rmmod 한다.
insmod vhost_net.ko에서 에러발생한다면 rmmod vhost후에 virsh start vm1으로 기존의 vhost와 vhost_net을 모듈에 적재한후 vm종료후 모듈을 내려준다.
virsh start vm1 ~ virsh start vm6으로 vm 6개를 킨다.
netserver에서 lab/autossh.exp 1~ lab/autossh.exp 6으로 vm6개에 connect한다.
jy-os(host os) 1개와 netserver(gest os) 6개를 lab폴더로 접근한다.
./setup.sh로 각각 mount와 host os는 vhost pid를 확인한다.
jy-os에서 setup.sh를 눌러서 pid가 화면에 안뜨거나 ./get_pid.sh를 한뒤 share/midfile/pid.txt에 공백으로 있을시에 get_pid.sh 의 -f 뒤 인자를 수정한다.
6개를 켰는데 4개만 나온다면 전체 vm종료후 다시킨다.
moduletest/interval.sh (인터벌)로 us단위 인버발을 조정한다.
jy-os(host os) 1개와 netserver(gest os) 6개를 lab폴더에서 run.sh를 진행한다
run.sh 시간 바이트
run.sh : 1thread, pidstat
run1.sh : 1thread, perf stat
perfthread4.sh : 4thread, pidstat
만약 netserver컴퓨터를 방금 켰다면 ./setup.sh로 netserver port를 open한다.
share/resultfile/2020~.txt에서 결과를 확인한다.
vhost cpu 파일이 없을경우 : pid가 잘못됨
vhost netperf 파일이 없을경우 mount가 잘못됨
위의 경우는 setup.sh를 다시 진행한다.
 인터벌을 또 바꾸고 네트워크 측정은 가능하다.
측정완료 후 vm 종료 전에는 moduletest/interval.sh 0 으로 인터벌 변수를 0으로 만들어준다.
vm 종료 & 모듈 제거




#### 폴더
##### 1. share, savefile : 실험컴퓨터와 가상머신 자료 공유 및 저장

##### 2. shfile : 쉘스크립트 코드

##### 3. moduletest : 모듈 컴파일 코드

##### 4. tracefile : ftrace 파일([ftrace란?](https://jjudrgn.tistory.com/26?category=1010336))
---    

#### 코드
##### 2. shfile : 쉘스크립트 코드




##### 3. moduletest
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

####4. tracefile
```
ftrace trace file
190813 : 6 vm's vhost*, handle_rx, handle_tx function_graph | TCP_STREAM | 64 size trace file
190814 : 1 vm's vhost*, handle_rx, handle_tx function_graph | TCP_STREAM | 64 size trace file
190814_2 : 1 vm's all functions enabled graph | TCP_STREAM | 64 size trace file
190814_3 : 1 vm's vhost*, handle_rx, handle_tx function_graph | UDP netperf | 64 size trace file
190814_4 : 1 vm's vhost*, handle_rx, handle_tx function_graph | UDP netperf | 1024 size trace file
190815 : 1 vm's vhost*, handle_rx*, handle_tx* function_graph | UDP netperf | 64 size trace file
190815_2 : 190815's options + abtime add
190815_3 : 1 vm's all vhost possible trace file | TCP netperf | 64 size trace file
190816 : 1 vm's all vhost possible trace file | TCP netperf | 64 size trace file
190816_2 : 1 vm's all vhost possible trace file | TCP netperf | 64 size trace file
190816_3 : _2 + 동작 최소한 커널 상태(echo 0 > tracing_on 후 cat trace), _2와 같은 결과
190816_4 : 190816's options -+ 1024size 
190816_5 : 190816's options + 6vm
100816_6 : 190816_5's options + 4thread
190816_7 : same 190816_6's options
190822_1~10  : 6 vm's all vhost possible trace file | TCP netperf | 64 size trace file | 1thread
190822_11~20 : 6 vm's all vhost possible trace file | TCP netperf | 64 size trace file | 4thread
191112 : 1vm's all vhost possible trace file | TCP | 64 | 1thread | eddited code of document 11/11

function description

 ##udp 통신할때 handle_tx 동작
0)               |    handle_tx_kick [vhost_net]() {
0)               |      handle_tx [vhost_net]() {
0)   0.103 us    |        vq_iotlb_prefetch [vhost]();
0)   0.101 us    |        vhost_disable_notify [vhost](); // we don't need to be notified agin.
                          vhost_net_disable_vq[vhost_net](); {
0)   0.105 us    |          vhost_poll_stop [vhost](); // stop polling a file.
                          }
0)               |        handle_tx_zerocopy [vhost_net]() {  //socket zero copy : 디스크에서 소켓을 효율적으로 데이터복사하는 방법
<<<<<<< HEAD
0)   0.112 us    |          vhost_zerocopy_signal_used [vhost_net](); 			//반복 시작 /* Release DMAs done buffers first */
=======
0)   0.112 us    |          vhost_zerocopy_signal_used [vhost_net](); 			//반복 시작 /* Release DMAs done buffers first */ 	DMAs done buffers 풀어줌
>>>>>>> f246e21809745564aece7b7a5e8dcee442520631
0)               |          get_tx_bufs [vhost_net]() {
                              vhost_net_tx_get_vq_desc() {
0)               |              vhost_get_vq_desc [vhost]() {//이것은 virtqueue와 사용 가능한 첫 번째 버퍼로 보이고, 편리한 접근을 위해 그것을 iovec로 변환한다.  
0)   0.107 us    |                translate_desc [vhost]();
                                }
0)   0.346 us    |            }
0)   0.554 us    |          }
                            tx_can_batch {
0)   0.103 us    |            vhost_vq_avail_empty [vhost](); /* return true if we're sure that avaiable ring is empty */
                            }
0)               |          vhost_add_used_and_signal [vhost]() { //DMA가 어떤 이유로 더 낮은 장치 드라이버 순서로 되어 있지 않은 경우. upend_idx는 사용된 idx의 끝을 추적하는 데 사용되며, done_idx는 사용된 idx의 헤드를 추적하는 데 사용된다. 낮은 디바이스 DMA가 연속적으로 수행되면 사용된 KVM 게스트 idx에 신호를 보낼 것이다.
0)               |            vhost_add_used_n [vhost]() { //그 버퍼들 중 하나를 사용한 후에, 우리는 그들에게 그것에 대해 이야기한다. 그런 다음 eventfd를 사용하여 게스트에게 알려야 한다.
0)   0.125 us    |              __vhost_add_used_n [vhost]();
0)   0.352 us    |            }
0)   0.126 us    |            vhost_signal [vhost](); //This actually signals the guest, using eventfd.
0)   0.788 us    |          }							    //반복 끝
0)               |          vhost_poll_queue [vhost]() { // 아마 중단하는 코드로 현재 예상
0)   0.189 us    |            vhost_work_queue [vhost]();
0)   0.400 us    |          }
0) # 1027.732 us |        }
0) # 1028.648 us |      }
0) # 1028.849 us |    }


구조
handle_tx {
  handle_tx_zerocopy{
    for(;;) {
      vhost_zerocopy_signal_used() 
      if(Nothing new?  Wait for eventfd to tell us they refilled)
        vhost_work_queue();
      vhost_add_used_and_signal
      if(vhost_exceeds_weight) //Max number of bytes transferred before requeueing the job. 정도를 초과했다면
        vhost_work_queue();
    }
  }
}

tcp 통신에서 비효율적인구조 발견 (190815_3 중간 부분 참고)

4266129.266685 |   0)               |    handle_tx_kick [vhost_net]() {
4266129.266685 |   0)               |      handle_tx [vhost_net]() {
4266129.266686 |   0)   0.108 us    |        vq_iotlb_prefetch [vhost]();
4266129.266686 |   0)   0.106 us    |        vhost_disable_notify [vhost]();
4266129.266686 |   0)   0.101 us    |        vhost_poll_stop [vhost]();
4266129.266686 |   0)               |        handle_tx_zerocopy [vhost_net]() {
4266129.266686 |   0)   0.102 us    |          vhost_zerocopy_signal_used [vhost_net]();
4266129.266687 |   0)               |          get_tx_bufs [vhost_net]() {
4266129.266687 |   0)               |            vhost_get_vq_desc [vhost]() {
4266129.266687 |   0)   0.121 us    |              translate_desc [vhost]();
4266129.266687 |   0)   0.107 us    |              translate_desc [vhost]();
4266129.266687 |   0)   0.120 us    |              translate_desc [vhost]();
4266129.266687 |   0)   0.862 us    |            }
4266129.266688 |   0)   1.079 us    |          }
4266129.266688 |   0)   0.117 us    |          vhost_vq_avail_empty [vhost]();
4266129.266689 |   0)   0.129 us    |          vhost_zerocopy_signal_used [vhost_net]();
4266129.266689 |   0)   0.107 us    |          vhost_zerocopy_signal_used [vhost_net]();
4266129.266690 |   0)               |          get_tx_bufs [vhost_net]() {
4266129.266690 |   0)   0.121 us    |            vhost_get_vq_desc [vhost]();
4266129.266690 |   0)   0.326 us    |          }
4266129.266690 |   0)   0.134 us    |          vhost_enable_notify [vhost](); /* OK, now we need to know about added descriptors. */
4266129.266690 |   0)   4.028 us    |        }
4266129.266690 |   0)   4.860 us    |      }
4266129.266690 |   0)   5.060 us    |    }
 ------------------------------------------
 0) vhost-2-26292  => CPU 0/K-26296 
 ------------------------------------------

4266129.266703 |   0)               |  vhost_poll_wakeup [vhost]() {
4266129.266703 |   0)   0.721 us    |    vhost_work_queue [vhost]();
4266129.266704 |   0)   0.977 us    |  }
 ------------------------------------------
 0) CPU 0/K-26296  => vhost-2-26292 
 ------------------------------------------

4266129.266705 |   0)               |    handle_tx_kick [vhost_net]() {
4266129.266705 |   0)               |      handle_tx [vhost_net]() {


구조
<<<<<<< HEAD
=======

kthread -> vhost_worker -> handle_tx_kick -> handle_tx -> handle_tx_zerocopy

>>>>>>> f246e21809745564aece7b7a5e8dcee442520631
handle_rx {
 mutex_lock_nested(&vq->mutex, VHOST_NET_VQ_RX);
 if (!sock)
	goto out;
 if (!vq_iotlb_prefetch(vq))
	goto out;
 vhost_disable_notify(&net->dev, vq);
 vhost_net_disable_vq(net, vq);
 while(vhost_net_rx_peek_head_len) {
  	if(error)
   		goto out;
  	if (!headcount) {
		if (unlikely(busyloop_intr)) {
			vhost_poll_queue(&vq->poll);
		} else if (unlikely(vhost_enable_notify(&net->dev, vq))) {
			vhost_disable_notify(&net->dev, vq);
			continue;
		}
		goto out;
	}
  
  if (unlikely(busyloop_intr))
		vhost_poll_queue(&vq->poll);
	else
		vhost_net_enable_vq(net, vq);
  if 
  out:
	vhost_net_signal_used(nvq);
	mutex_unlock(&vq->mutex);
}
  
  
/* handle_rx [vhost_net] */                               // 항상 RCU의 읽기 크기 중요 섹션 역할을 하는 워크 큐에서 예상된다.
 2)               |  handle_rx [vhost_net]() {
 2)   0.106 us    |    vhost_disable_notify [vhost]();    // 인터럽트 또는 신호등을 보내지말게 설정. vq.플래그설정   
 2)   0.123 us    |    vhost_poll_stop [vhost]();         // stop a polling a file,이 기능이 반환되면 파일 참조를 삭제하는 것이 안전해진다 , 또한 그 후에 flush 해야한다. 
 2)   0.119 us    |    vhost_net_buf_peek [vhost_net]();  // 
 2)               |    vhost_net_enable_vq [vhost_net]() {
 2)               |      vhost_poll_start [vhost]() {
 2)   0.130 us    |        vhost_poll_func [vhost]();
 2)   0.362 us    |      }
 2)   0.568 us    |    }
 2)   1.461 us    |  }
4313371.298157 |   0)               |    handle_rx_net [vhost_net]() {
4313371.298157 |   0)               |      handle_rx [vhost_net]() {
4313371.298157 |   0)   0.101 us    |        vq_iotlb_prefetch [vhost]();
4313371.298158 |   0)   0.102 us    |        vhost_disable_notify [vhost]();
4313371.298158 |   0)   0.146 us    |        vhost_poll_stop [vhost]();
4313371.298158 |   0)   0.167 us    |        vhost_net_buf_peek [vhost_net]();
4313371.298158 |   0)               |        vhost_get_vq_desc [vhost]() {
4313371.298158 |   0)   0.110 us    |          translate_desc [vhost]();
4313371.298159 |   0)   0.368 us    |        }
4313371.298159 |   0)   0.112 us    |        vhost_net_buf_peek [vhost_net]();
4313371.298160 |   0)               |        vhost_net_enable_vq [vhost_net]() {
4313371.298160 |   0)               |          vhost_poll_start [vhost]() {
4313371.298160 |   0)   0.121 us    |            vhost_poll_func [vhost]();
4313371.298160 |   0)   0.401 us    |          }
4313371.298160 |   0)   0.636 us    |        }
4313371.298160 |   0)               |        vhost_add_used_and_signal_n [vhost]() {
4313371.298160 |   0)               |          vhost_add_used_n [vhost]() {
4313371.298161 |   0)   0.126 us    |            __vhost_add_used_n [vhost]();
4313371.298161 |   0)   0.342 us    |          }
4313371.298161 |   0)   1.182 us    |          vhost_signal [vhost]();
4313371.298162 |   0)   1.822 us    |        }
4313371.298162 |   0)   4.972 us    |      }
4313371.298162 |   0)   5.179 us    |    }
```
