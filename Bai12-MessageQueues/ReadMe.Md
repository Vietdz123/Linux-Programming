# Giới thiệu Message Queue

- **Message Queue** là một danh sách liêt kết(link-list) các message được duy trì bởi Kernel
- Tất cả các Process có thể trao đổi dữ liệu thông qua việc truy cập vào cùng một queues
- Mỗi một message sẽ được đính kèm thông tin về type( type message).
    - Nghĩa là mỗi Message gồm 2 trường:    
        - *Message* 
        - *Type Message*
<div></div>

- Message Queue có 2 cách triển khải
  - **System V**
  - **Posix**

## I. Các bước triển khai của SystemV

![](2022-06-27-12-40-03.png)

- Tạo Key
    - Hàm sử dụng: **key_t ftok(const char *pathname, int proj_id);***
    - VD: *key = ftok("progfile", 65);*
    - Ta cũng có thể tự định nghĩa 1 Key, rồi truyền vào các bước để sử dụng mà ko cần qua hàm ftok(): #DEFINE KEY 50
<div></div>

- Tạo Message Queue hoặc mở một Queue có sẵn
  - Hàm sử dụng: **int mssget(key_t key, int msgfl)**
    - Với msgfl:
      - IPC_CREATE: Tạo mới Queue
      - IPC_EXCL: Được sử dụng với IPC_CREATE, để chắc chắn có thể tạo ra Queue, nếu như Key đã tồn tại thì sẽ trả lại lỗi
  - VD: *int msgid = msgget(key, 0666 | IPC_CREAT);*
<div></div>

- Ghi dữ liệu vào trong Queue
  - Hàm sử dụng: **int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);***
    - msqid: Id thu được từ *msgget*.
    - msgp: con trỏ trỏ tới dữ liệu ta muốn gửi(messages).
    - msgsz: Kích thước của message.
    - msgflg: 
      - IPC_NOWAIT: Nếu Queue bị full hoặc ko có dữ liệu, thì sẽ return ngay lập tức cho mình --> Ko bị block
      - IPC_NOERROR: Cắt bớt message nếu kích thước message lớn hơn msgsz.
    - VD: *msgsnd(msgid, "Hello ae wibu", sizeof("hello ae wibu), 0);*
<div></div>

- Đọc dữ liệu từ Message Queue
  - Hàm sử dụng: **ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);***
    - msqid: Id thu được từ *msgget*.
    - msgp: con trỏ trỏ tới buffer để lưu dữ liệu
    - msgsz: kích thước muốn đọc
    - msgtyp: (Chú ý Trong Message Queue có nhiều Type). 
      - Trong Imgae: 3 là thằng vào đầu tiên, và 1 là thằng vào sau cùng
        - Nếu để Type là 0: thì sẽ lấy ra thằng đầu tiên trong Queue, trong TH này là thằng 3
        - Nếu type là số nguyên dương +ve: VD là số 5, thì trong ảnh sẽ lấy chính xác số 5 đầu tiên từ vị trí đầu tiên --> Vị trí thứ 3 từ phải sáng
        - Nếu type là số nguyên âm -ve: VD là số -5, thì sẽ lấy ra thằng có type nhỏ nhất với giá trị tuyệt đối của -ve, với trong ảnh là 1
<div></div>

- Giải phóng Message Queue
  - Sử dụng hàm: **int msgctl(int msqid, int cmd, struct msqid_ds *buf);***
    - msqid: Id thu được từ *msgget*.
    - IPC_RMID: Xóa message queue ngay lập tức
        - Kể cả có thằng khác đang dùng queue
    - buf ta thường để NULL.


## II. Các bước triển khai trên POSIX

- Tạo Message Queue hoặc mở một Queue có sẵn
  - Hàm sử dụng: 
    - **mqd_t mq_open(const char *name, int oflag);*** - Mở một Queue có sẵn
    - **mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);*** - Tạo mới Queue
      - Với oflag:
        - O_CREAT: Tạo mới Queue
        - IPC_EXCL: Được sử dụng với O_CREAT, nếu như name đã tồn tại thì sẽ trả lại lỗi
        - O_RDONLY
        - O_NONBLOCK: Nếu như Queue mà full để ghi hoặc ko có dữ liệu để đọc, thì return ngay lập tức.
      - mode: 0666
      - attr: là một struct để lưu trữ các thông tin của Queue, nếu ta để NULL thì sử dụng mặc định
  - VD: *int msgid = msgget(key, 0666 | IPC_CREAT);*
<div></div>

- Ghi dữ liệu vào trong Queue
  - Hàm sử dụng: **   int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);**
    - mqdes: Giá trị trả về ở bước 1.
    - msg_ptr: con trỏ trỏ tới buffer lưu dữ liệu muốn gửi đi.
    - msg_ptr: kích cỡ buffer.
    - msg_prio: Priorty của Message.
      - Mỗi một message có một **Priorty** là một số nguyên dương ko âm. Message trong Queue sẽ được sắp xếp giảm dần với **0 là độ ưu tiên thấp nhất**
      - Khi một Message mới vào Queue thì nó sẽ được xếp sau các Message có cùng độ ưu tiên.
<div></div>

- Đọc dữ liệu từ Message Queue
  - Hàm sử dụng: **ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);**
    - mqdes: Giá trị trả về ở bước 1.
    - msg_ptr: con trỏ trỏ tới buffer lưu dữ liệu muốn nhận.
    - msg_ptr: kích cỡ buffer.
    - msg_prio: Priorty của Message.
  - Hàm mq_receive() sẽ đọc giá trị có độ ưu tiên cao nhất trùng với độ ưu tiên Priorty.
<div></div>

- Đóng message queue khi không sử dụng
  - 

- Giải phóng Message Queue
  - Sử dụng hàm: **mq_unlink(const char *name)**.
    - Khi tất cả các Process đang sử dụng Message Queue đều Đóng thì hàm này mới đc sử dụng và giải phong Queue hoang toàn.