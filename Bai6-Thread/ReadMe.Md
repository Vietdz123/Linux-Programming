> # THREAD 

> ## I. So sánh Thread và Process
> - Khi gọi fork(), tiến trình con và tiến trình cha nằm trên 2 vùng nhớ khác nhau, hoạt động độc lập với nhau.
>   - Khi 1 tiến trình bị lỗi, crashed thì tiến trình khác vẫn hoạt động bình thường
>    - Còn khi tạo ra thread(), thì thread đó sử dụng chung vùng nhớ với Process. Khi 1 thread bị crashed sẽ khiến cho các thread bị chấm dứt.
> - process ID là một số nguyên nhưng thread ID không nhất thiết là 1 số nguyên. Nó có thể là structure
> - process ID có thể được in ra dễ dàng nhưng thread ID thì không.
> - **crashed:** bị hỏng, hoặc exit() (*Chứ không phải pthread_exit()*)

> ## II. Thread

> - Để tạo thread mới dùng hàm *int pthread_create(pthread_t * threadID, const pthread_attr_t *attr, void *(*start_routine)(void *), void *restrict arg);*. 
>   - Trả về 0 nếu thành công. Khác 0 là thất bại.
>
> - So sánh 2 *structue* của 2 thread ta có 2 hàm:
>   - *pthread_t pthread_self(void)*:
>       - Trả về ThreadID của thread đang gọi tới hàm pthread_self()
>   - *int pthread_equal(pthread_t t1, pthread_t t2)*;
>       - Trả về 0 nếu t1 khác t2, khác 0 nếu t1 = t2.
>
> - Để kết thúc 1 thread: 
>   - *int pthread_exit(void *retval)***:
>       - *retval*: Giá trị trả về khi kết thúc thread.
>       - Giá trị retval này có thể thu được vởi 1 thread khác thông qua *int pthread_join(pthread_t thread, void **retval);***
>       - Trả về 0 nếu thành công, < 0 nếu thất bại.
> 
>   - *int pthread_cancel(pthread_t thread):*
>       - pthread_cancel() gửi 1 yêu cầu kết thúc tới 1 thread cụ thể.
>       - Trả về 0 nếu thành công, < 0 nếu thất bại
>
> - Để thu được giá trị kết thúc của 1 thread ta sử dụng hàm:
>   - *int pthread_join(pthread_t thread, void **retval);***
>       - pthread_join() sẽ block cho đến khi thread ta truyền vào kết thúc. Nếu thread đó đã kết thúc thì pthread_join() sẽ return ngay lập tức.
>       - Để không bị block, ta sẽ sử dụng pthread_detach() ở chính thread tạo ra, và tự nó sẽ thu về trạng thái kết thúc của mình.
> - **Chú ý:** Tương tự như process, khi 1 thread kết thúc mà ta chưa thu về trạng thái kết thúc của nó, thì thread đó sẽ chưa được giải phóng hoàn toàn

> ## III. Đồng bộ dữ liệu (Thread synchronization)
> - Một trong những điểm mạnh của thread chính là việc chia sẻ dữ liệu với nhau qua các biến global (shared variables - shared resource)
>   - Sẽ rất *không ổn* khi 1 thread đang đọc giá trị 1 biến global mà 1 thread khác đang sửa nó

> - **Các thuật ngữ**
>   - *Atomic:* Tại 1 thời điểm chỉ có 1 thread được truy cập vào tài nguyên của chương trình
>       - Atomic: An toàn
>   -*Nonatomic:* Nhiều thread có thể triu cập vào tài nguyên của chương trình tại 1 thời điểm
>       - Nonatomic: Không an toàn
> - Thuật ngữ *critical section:* chỉ đoạn code truy nhập vào tài nguyên được chia sẻ giữa các thread và việc thực thi nó trong bối cảnh atomic.

> - **Các cách đồng bộ dữ liệu giữa các thread:**
>   -   Sử dụng ***Mutex:***
>       - Khởi tạo khóa Mutex: *pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;*
>           - Khoi mới khởi tạo khóa mutex ở trạng thái *unlock*.
>       - Để lock và unlock khóa mutex ta sử dụng hàm:
>           - pthread_mutex_lock(&lock);
>           - pthread_mutex_unlock(&lock);
>   - **Chú ý:** Khi mutex đang bị lock bởi 1 thread, mà ở thread gọi pthread_mutex_lock() thì thread đó sẽ bị block cho đến khi mutex được unlock bởi thread lock nó.
<<<<<<< HEAD
<br>
=======
>
>>>>>>> 19c587a4e733f677ec118ebeef3d69eb5140a623
> - Sử dụng ***condition variables:***
>   - Hai hoạt động chính của condition variables là signal và wait.
>   - Khởi tạo biến *cond*:
>       - *pthread_cond_t cond = PTHREAD_COND_INITIALIZER;*
>       - Hai hàm được sử dụng:
>           - int pthread_cond_signal(pthread_cond_t *cond);
>               - Hàm này được sử dụng để unblock tối thiểu 1 thread đang bị block ở biến *cond*.
>           - int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
>               - Hàm này sẽ bị block với biến *cond*.
>               - Hàm này sẽ unlock khóa mutex trước khi nó sleep , khi cả 2 biến *cond* được unblock bởi hàm *pthread_cond_signal* và mutex được unlock bởi hàm *pthread_mutex_unlock()* thì nó sẽ thức dậy và thực thi tiếp lệnh ở bên dưới, và trong lúc chờ biến *cond* được unblock thì nó sẽ ko bị tốn CPU.
