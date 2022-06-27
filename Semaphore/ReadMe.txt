                /*************************** Semaphore ***************************\
    
        #include <semaphore.h>

    +, Semaphore là cơ chế đồng bộ truy cập giữa các process và thread.
    +, Mục đích chính được sử dụng để block process và thread truy cập vào 1 vùng nhớ
    +, Có 2 loại Semaphore:
            +, System V Semaphore
            +, Posix Semaphore
                +, Unamed Semaphore và Named Semaphore

--> Thường cái nào dùng Named thì cái đó dùng file để làm định danh, và có thể chia sẽ mỗi liên kết giữa nhiều file
--> Cái nào mà anonymous và Unamed thì dùng Virtual file nằm trên file và dùng chỉ để liên kết giữa các process hoặc thread trong file đó

1. Named Semaphore:
    +, Là Semaphore được đặt tên, được tạo thông qua hàm sem_open(). Các unrelated process có thể truy cập tới cùng 1 Semaphore.

2. Unnamed Semaphore
    +, Là Semaphore không được đặt tên, do không có name để sử dụng chung nên để sử nó cần phải truy cập vào các vùng nhớ chung(shared memory, mmap, global variable,...)
    +, Được sử dụng cho việc truy cập giữa các process hoặc threads
    +, Đối với các process thì nó là vùng nhớ đc shared(Sử dụng shm hoặc Posix Map), còn với các thread là vùng nhớ mà các thread được chia sẻ trong chương
        trình VD: global hoặc head

3. Nguyên lý hoạt động chung của Semaphore:
    +, Semaphore là một số nguyên dương được duy trì bởi Kernel có giá trị lớn hơn hoặc bằng 0
    +, Có thể thực hiện nhiều hoạt động khác nhau(tức là các lệnh gọi hệ thống) trên Semaphore, bao gồm những điều sau:
            +, Tăng giá trị hiện tại của Semaphore lên 1 dùng sem_post();
            +, Trừ giá trị hiện tại của Semaphore xuống 1 dùng sem_wait();
            +, Đọc giá trị hiện tại của Semaphore.
    
    3.1. Waiting on Semaphore:
        +, Hàm sem_wait() giảm 1 giá trị của Semaphore
        +, Nếu giá trị Semaphore lớn hơn 0, Semaphore sẽ return ngay lập tức
        +, nếu giá trị Semaphore = 0, sem_wait() sẽ block cho đến khi giá trị Semaphore tăng trên 0.
        +, Sau khi sem_wait() được trả về thì giá trị của Semaphore sẽ được giảm đi 1.
                int sem_wait(sem_t *sem);

    --> pthread_mutex() thì chỉ có 1 thread sử dụng tài nguyên
        --> Còn Semaphore sẽ cho phép nhiều thread cùng sử dụng tài nguyên.
    
    --> Ta thấy hàm sem_wait() sẽ bị block đến khi giá trị Semaphore lớn hơn 0, nên ta được cung cấp 1 hàm sem_trywait().
        +, Hàm sem_trywait() chỉ thực hiện chờ trong một thời gian nhất đinh, nếu timeout mà giá trị semaphore vẫn bằng 0 thì lỗi sẽ được trả về ETIMEOUT.
    
    3.2 Posting on Semaphore:
        +, Hàm sem_post() sẽ tăng giá trị Semaphore lên 1
        +, Nếu có nhiều process cùng đang chờ Semaphore lên 1, thì Kernel sử dụng thuật toán round-robin và time-sharing để quyết định.
                --> Tức là ko phải thằng process nào wait trước thì sẽ thực hiện trước.
    
    3.3 Read Semaphore Value:
        +, Hàm sem_getvalue() trả về giá trị hiện tại Semaphore.
        +, Giá trị Semaphore được nằm trong con trỏ sval.
            int sem_getvalue(sem_t *sem, int *sval);

4. Nguyên lý hoạt động của Named-Semaphore:

    4.1 Opening Named Semaphore:
        +, sem_open() sử dụng để tạo một semaphore mới hoặc mở một semaphore có sẵn
            VD; sem_t *sem = sem_open("/named_app", O_CREAT|O_EXCL, R_W_PERM, 1);
        +, Tổng quát: 
            sem_t *sem_open(const char *name, int oflag);           // 2 đối số
            sem_t *sem_open(const char *name, int oflag,            // 4 đối số
                            mode_t mode, unsigned int value);

        --> name: Tên định danh của Semaphore.
            oflag: cho biết mode hoạt động của sem_open():
                +, 0: mở một Semaphore đang tồn tại
                +, O_CREAT: tạo 1 semaphore mới
                +, O_CREAT và O_EXCL: tạo một semaphore mới và trả về lỗi nếu đã tồn tại semaphore liên kết với tên được đưa ra. 
        
        --> Nếu O_CREAT được sử dụng thì 2 đối số nữa sẽ được thêm cho sem_open():
            +, mode: giá trị quyền Semaphore được tạo ra, vd: 0666
            +, value: giá trị khởi tạo cho semaphore, là số nguyên >= 0.
    
    4.2 Closing named Semaphore:
        +, Khi thực hiện sem_open() thì semaphore sẽ được liên kết với process. Hệ thống sẽ ghi lại mỗi liên kết này
        +, sem_close() sẽ thực hiện kết thúc liên kết này. Giải phóng bất kì tài nguyên nào mà hệ thống đã liên kết và giảm số lượng process đã tham chiếu tới semaphore.
            --> Đơn giản là xóa liên kết.
    
    4.3 Removing named Semaphore:
        +, Hàm sem_unlink() xóa semaphore được xác định bằng name và đánh dấu semaphore sẽ bị hủy sau khi tất cả các process ngừng sử dụng nó.
        +, Tức là semaphore sẽ bị hủy cho đến khi tất các tiến trình liên kết tới nó gọi hàm sem_close().


5. Unamed Semaphore:

    5.1 Khởi tạo Unamed Semaphore:
            int sem_init(sem_t *sem, int pshared, unsigned int value);
        +, Hàm sem_init() được sử dụng để khởi tạo Semaphore và thông báo cho Kernel là semaphore được sử dụng để shared mỗi liên kết giữa các process hoặc các thread trong cùng 1 process.
        +, Đối số pshared cho biết liệu semaphore có được chia sẻ giữa các threads hay các process hay không:
            +, pshared là 0: semaphore sẽ được chia sẻ giữa các process và thread. Semaphore sẽ được tạo ra và trỏ tới một địa chải heap hoặc global
            +, pshared khác 0: semaphore được chia sẻ giữa các process, sem sẽ là địa chỉ của một vùng nhớ được shared giữa các process(System V hoặc Posix mmap).
        +, value: giá trị semaphore được khởi tạo.
    
    5.2 Destroying an Unnamed Semaphore:
        +, Hàm sem_destroy() hủy semaphore