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
0)   0.112 us    |          vhost_zerocopy_signal_used [vhost_net](); 			//반복 시작 /* Release DMAs done buffers first */
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
handle_rx {
 mutex_lock_nested(&vq->mutex, VHOST_NET_VQ_RX);
 if (!sock)
		 goto out;
	if (!vq_iotlb_prefetch(vq))
		 goto out;
 vhost_disable_notify(&net->dev, vq);
	vhost_net_disable_vq(net, vq);
 while() {
  if(error)
   goto out;
  if (!headcount) {
			if (unlikely(busyloop_intr)) {
				vhost_poll_queue(&vq->poll);
			} else if (unlikely(vhost_enable_notify(&net->dev, vq))) {
				/* They have slipped one in as we were
				 * doing that: check again. */
				vhost_disable_notify(&net->dev, vq);
				continue;
			}
			/* Nothing new?  Wait for eventfd to tell us
			 * they refilled. */
			goto out;
		}
  
  if (unlikely(busyloop_intr))
		vhost_poll_queue(&vq->poll);
	else
		vhost_net_enable_vq(net, vq);
  
  
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
