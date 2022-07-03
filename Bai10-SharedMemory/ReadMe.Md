# Shared Memory
> Là vùng nhớ cho phép nhiều tiến trình có thể truy cập tới.

> **I. Phương pháp tạo Shared Memory:**
> - Có 2 phương pháp tạo Shared Memory:
>   - Với hệ thống Linux cũ thì sử dụng API của shm(System V).
>   - Với hệ thống Linux mới thì sử dụng API của mmap(POSIX).

> **1.1. Các bước tạo SystemV Shared Memory:**
> **(Anonymous Mapping):** Mapping vùng nhớ trên Ram.

> - B1: tạo Key
>   - Để định danh cho vùng shared Memory
>   - Key có thể là 1 số nguyên: *#define key 20*
>   - Key có thể được tạo bằng hàm ftok().
> </br>
> - B2: Tạo Shared Memory Segment: Sủ dụng *int msgget(key_t key, int msgflg);*
>   - VDL int shmid = shmget(key, 1024, 0666 | IPC_CREATE);
>       - *shmid:* ID của vùng Shared Memory
>       - *1024:* Kích thước của vùng shared memory và được làm tròng thành page size(làm tròn lên).
>       - **0666:** Quyền của vùng. (Phải có).
> </br>
> - B3: Để attach(map) vùng shared memory segment vừa tạo trên, ta sử dụng hàm *void * shmat(int shmid, const void * shmaddr, int shmflg).* 
>   - VD: chả * shmaddr = (char *)shmat(shmid, NULL, 0);
>       - Khi để NULL, kernel sẽ tự tìm cho vùng nhớ phù hợp giữa stack và heap để ánh xạ sang shared memory segment
>       - Thường ta hay để đó là NULL.
> </br>
> - B4: Khi tiến trình đã sử dụng xong vùng shared đó, thì ta dùng hàm *int shmdt(const void * shmaddr)* để detach vùng nhớ đó đi.
>   - VD: shmdt(shmaddr);
> </br>
> - B5: Sau khi các process đã sử dụng xong và *shmdt()*, và ta muốn xóa vùng shared thì ta dùng hàm *int shmctl(int shmid, int cmd, struct shmid_ds * buf).*
>   - VD: shmctl(shmid, IPC_RMID, NULL);
>   - Hàm chỉ bị hủy khi tất các process đã unmap vùng nhớ đó đi.

> **1.2. Các bước tạo Posix Shared Memory:**
> - B1: Tạo Shared Memory Object: *int shm_open(const char * name, int oflag, mode_t mode);*
>   - VD: #define FILENAME "test_sharedmemory"
>   - int fd = shm_open(FILENAME, O_RDWR, 0666);
> </br>
> - B2: Set size cho vùng shared Memory: *int ftruncate(int fd, off_t length);*
>   - VD: int ftruncate(fd, 100);
> </br>
> - B3: map vùng không gian địa chỉ process tới vùng Shared Memory. Sử dụng hàm ***void * mmap(void * addr, size_t length, int prot, int flags, int fd, off_t offset);***
>   - Chúng ta có 4 kiểu mapping như sau:
>       - **Private anonymous mapping**: Tạo một shared memory object nằm trên Ram (Virtual file).
>           - A ghi dữ liệu vào, B sẽ không phân biệt được Data thay đổi.
>       - **Private file mapping**: Tapk 1 shared memory trên ổ cứng,
>           - A ghi dữ liệu vào, B sẽ không nhận biết được
>           - Kĩ thuật copy-on-write.
>       - **Shared anonoymous mapping**: tạo 1 shared memory trên Ram.
>           - A ghi dữ liệu vào, B sẽ nhận biết được.
>       - **Shared memory mapping**: Tạo 1 shared memory trên ổ cứng
>           - A ghi dữ liệu vào, B sẽ nhận biết được.
>   - **VD**: char *data = char *data = (char *)mmap(0, 100, PROT_READ | PROT_WRITE, MAP_PRIVATE, shm_fd, 0);
>       - addr: địa chỉ memory của calling process được map. Tương tự như shm nên set giá trị là 0 và kernel sẽ allocation addr phù hợp
>       - length: độ dài của shared memory object được map(> 0).
>       - prot: memory protection of mapping (không được conflict với file permission).
>           - PROT_EXEC  ---> Pages may be executed
>           - PROT_READ  ---> Pages may be read.
>           - PROT_WRITE ---> Pages may be written.
>           - PROT_NONE  ---> Pages may not be accessed.
>       - **flags:** cờ cho phép các process có thể thấy được cập nhật của các process vào shared memory hay không.
>           - **MAP_SHARED**  ---> cập nhật của process này vào shared memory là available với các process khác.
>               - Nghĩa là: khi thay đổi dữ liệu, nó sẽ thay đổi dữ liệu trực tiếp dữ liệu ở file luôn.
>           - **MAP_PRIVATE** ---> kernel sử dụng phương thức copy-on-write để tạo ra vùng nhớ riêng cho thay đổi của process. Các thay đổi này sẽ không visiable đối với các process khác.
>               - Nghĩa là: khi thay đổi dữ liệu, nó sẽ thay đổi dữ liệu ở vùng nhớ ở process chứ ko thay đổi ở dữ liệu file.
>           - **MAP_ANONYMOUS** ---> Tạo ra anonymous mapping. Toàn bộ ô nhớ trên vùng này được khởi tạo là 0. Không cần quan tâm tới fd.
>           - **MAP_UNINITIALIZED** ---> Không khởi tạo vùng anonymous mapping.
> </br>
> B4: Unmap vùng địa chỉ map tới Shared Memory. Sử dụng hàm *int munmap(void * addr, size_t len);*
>   VD: munmap(data, 100);
> </br>
> B5: Xóa vùng shared. Sử dugj hàm *int shm_unlink(const char * name);*
>   VD: shm_unlink(FILE_NAME);