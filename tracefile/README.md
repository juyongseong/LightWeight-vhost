# 함수 그래프 분석 및 설명
## EXPORT_SYMBOL_GPL(vhost_enable_notify);
bool vhost_enable_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
/* OK, now we need to know about added descriptors. */
handle_rx? handle_txz?
net.c의 함수
이함수에 의해 실행되는 vhost함수들이 많이 있음!
static int vhost_update_avail_event(struct vhost_virtqueue *vq, u16 avail_event)
vhost가 이벤트 가능한지 ?
이후 연결관계?
void vhost_poll_init(struct vhost_poll *poll, vhost_work_fn_t fn, unsigned long mask, struct vhost_dev *dev)
/* Init poll structure */
int vhost_poll_start(struct vhost_poll *poll, struct file *file)
/* Start polling a file. We add ourselves to file's wait queue. The caller must keep a reference to a file until after vhost_poll_stop is called. */
static int vhost_poll_wakeup(wait_queue_entry_t *wait, unsigned mode, int sync,  void *key)
void vhost_poll_queue(struct vhost_poll *poll)
void vhost_work_queue(struct vhost_dev *dev, struct vhost_work *work)
이후 연결관계?
int vq_iotlb_prefetch(struct vhost_virtqueue *vq)
vq io를 진행중인 처리와 병행하기전 사전에 판독?
void vhost_disable_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
/* We don't need to be notified again. */
 vhost_enable_notify~vhost_disable_notify까지의 일련의 과정들을 used_flags를 통해 vring를 통제?
//인터럽트 또는 신호등을 보내지말게 설정함.  사용함에 등록 vq->used_flags |= VRING_USED_F_NO_NOTIFY;
이후 연결관계?
void vhost_poll_stop(struct vhost_poll *poll)
/* Stop polling a file. After this function returns, it becomes safe to drop the file reference. You must also flush afterwards. */
int vhost_get_vq_desc(struct vhost_virtqueue *vq, struct iovec iov[], unsigned int iov_size, unsigned int *out_num, unsigned int *in_num, struct vhost_log *log, unsigned int *log_num)
/*This looks in the virtqueue and for the first available buffer, and converts it to an iovec for convenient access.  Since descriptors consist of some number of output then some number of input descriptors, it's actually two iovecs, but we pack them into one and note how many of each there were. This function returns the descriptor number found, or vq->num (which is never a valid descriptor number) if none was found.  A negative code is returned on error. */
무언가 중요한 함수같음
virtqueue와 최초의 사용 가능한 버퍼에 대해 살펴보고, 그것을 iovc로 변환하여 편리하게 접근할 수 있도록 한다
예외를 처리하는 if문과 return이 많이 존재;


 ## /* handle_rx [vhost_net] */
 2)               |  handle_rx [vhost_net]() {
 2)   0.106 us    |    vhost_disable_notify [vhost]();  //인터럽트 또는 신호등을 보내지말게 설정. vq.플래그설정   
 2)   0.123 us    |    vhost_poll_stop [vhost]();
 2)   0.119 us    |    vhost_net_buf_peek [vhost_net]();
 2)               |    vhost_net_enable_vq [vhost_net]() {
 2)               |      vhost_poll_start [vhost]() {
 2)   0.130 us    |        vhost_poll_func [vhost]();
 2)   0.362 us    |      }
 2)   0.568 us    |    }
 2)   1.461 us    |  }
