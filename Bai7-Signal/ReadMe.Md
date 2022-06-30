 # Signal

> - Có 2 tín hiệu thường bị Catch là *SIGINT và SIGTERM*
> - *SIGKILL và SIGTERM* không thể bị catch.

> - Hàm Signal: **sighandler_t signal(int signum, sighandler_t handler);**
> Tín hiệu signal này cũng có thể tự gửi signal đến bản thân tiến trình đó qua hàm **getpid()** và **int kill(pid_t pid, int sign)**
>   -  VD: kill(getpid(), SIGINT); //trong code
>       - Tương đương với kill -2 process 
>       - Trả về 0 nếu thành công, khác 0 nếu thất bại.

# Blocking and unblocking signal
> - Signal có thể làm gián đoạn process
>   - Blocking signal sẽ giải quyết vấn đề này.
> - Mỗi một process có thể chỉ định các signal cụ thể nào đó mà nó muốn block. Nếu signal bị block thì tín hiệu đó vẫn được xảy ra nhưng tạm thời bị kernel giữ trong hàng chờ xử lý.
>   - Tín hiệu chỉ được gửi tới process sau khi được unblocking

> - Danh sách các signal bị block được gọi là **signal mask.**
> - Các hàm được sử dụng để set *signal mask.*
>   1. int sigemptyset(sigset_t *set);
>       - Hàm này khởi tạo 1 sigset_t với ko tín hiệu signal nào bị block.
>       - sigset_t là một nơi chưa tập hợp các signal được sử dụng để block hoặc unblock.
>   2. int sigfillset(sigset_t *set);
>       - Hàm này khởi tạo 1 sigset_t với mọi  tín hiệu signal bị block.
>   3. int sigaddset(sigset_t *set, int signo);
>       - Thêm tín hiệu signal vào sigset_t
>   4. int sigaddset(sigset_t *set, int signo);
>       - Xóa tín hiệu signal khỏi sigset_t
>   5. int sigismember(const sigset_t *set, int signum);
>      - Kiểm tra trong *sigset_t* có tín hiệu *signum* không.
>   6. ***int sigprocmask(int how, const sigset_t *restrict newset, sigset_t *restrict oldset);***
>       - Hàm này được sử dụng để set **signal mask**.
>       - Với *how* là: 
>           - SIG_SETMASK: signal mask sẽ bị thay đổi thành newset.
>           - sIG_BLOCK: newset sẽ được thêm vào signal mask.
>           - sig_unblock: newset sẽ bị xóa khỏi signal mask.
>  **Chú ý:**
>               - Nếu oldset khác NULL, sigprocmask sẽ lấy được signal mask trước khi bị thay đổi và lưu vào oldset
>               - Nếu oldset là NULL, sigprocmask sẽ bỏ qua việc thay đổi giá trị của signal mask, nhưng nó sẽ lấy được giá trị của signal và lưu vào oldset.