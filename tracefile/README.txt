ftrace trace file
190813 : 6 vm's vhost*, handle_rx, handle_tx function_graph | TCP_STREAM | 64 size trace file
190814 : 1 vm's vhost*, handle_rx, handle_tx function_graph | TCP_STREAM | 64 size trace file
190814_2 : 1 vm's all functions enabled graph | TCP_STREAM | 64 size trace file
190814_3 : 1 vm's vhost*, handle_rx, handle_tx function_graph | UDP netperf | 64 size trace file
190814_4 : 1 vm's vhost*, handle_rx, handle_tx function_graph | UDP netperf | 1024 size trace file
190815 : 1 vm's vhost*, handle_rx*, handle_tx* function_graph | UDP netperf | 64 size trace file
190815_2 : 190815's options + abtime add
function description
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
 ##udp 통신할때 handle_tx 동작
 2)               |  handle_tx_kick [vhost_net]() {
 2)               |    handle_tx [vhost_net]() {
 2)   0.112 us    |      vhost_disable_notify [vhost]();
 2)   0.103 us    |      vhost_poll_stop [vhost]();
 2)               |      handle_tx_zerocopy [vhost_net]() {
 2)   0.101 us    |        vhost_zerocopy_signal_used [vhost_net](); //반복시작
 2)   0.162 us    |        vhost_get_vq_desc [vhost]();
 2)   0.102 us    |        vhost_vq_avail_empty [vhost]();
 2)               |        vhost_add_used_and_signal [vhost]() {
 2)   0.140 us    |          vhost_add_used_n [vhost]();
 2)   0.127 us    |          vhost_signal [vhost]();
 2)   0.573 us    |        }                                         //
2)               |        vhost_poll_queue [vhost]() {
 2)   0.141 us    |          vhost_work_queue [vhost]();
 2)   0.337 us    |        }
 2) ! 488.915 us  |      }
 2) ! 489.578 us  |    }
 2) ! 489.779 us  |  }
