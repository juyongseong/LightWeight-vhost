함수 그래프 분석 및 설명

 /* handle_rx [vhost_net] */
 2)               |  handle_rx [vhost_net]() {
 2)   0.106 us    |    vhost_disable_notify [vhost]();      /* We don't need to be notified again. */   //인터럽트 또는 신호등을 보내지말게 설정함.  사용함에 등록 vq->used_flags |= VRING_USED_F_NO_NOTIFY;
 2)   0.123 us    |    vhost_poll_stop [vhost]();
 2)   0.119 us    |    vhost_net_buf_peek [vhost_net]();
 2)               |    vhost_net_enable_vq [vhost_net]() {
 2)               |      vhost_poll_start [vhost]() {
 2)   0.130 us    |        vhost_poll_func [vhost]();
 2)   0.362 us    |      }
 2)   0.568 us    |    }
 2)   1.461 us    |  }
