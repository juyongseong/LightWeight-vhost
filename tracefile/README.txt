ftrace trace file

190814 : vhost*, handle_rx, handle_tx function_graph trace file
190814_2 : all functions enabled graph trace file


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
