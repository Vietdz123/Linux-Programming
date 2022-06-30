> # Process Trong Linux

> ## I. Memory Layout Process
![](2022-06-27-17-26-10.png)

**Memory Layout Process** được chia làm các phần như sau:
>**1. Text Segment**
> - Là nơi chứa các đoạn mã lệnh của chương trình(Các lệnh thực thi của chương trình), các hằng số và các marcos.
> - Vùng text Segment là Read-Only để ngăn chặn việc bị sửa đổi và là vùng có thể được chia sẻ bởi các Process khác.
>   - Ví dụ về Sharable: Đó là gọi fork(), với kĩ thuật "copy-on-write", vùng text được sử dụng **chung tạm thời** bởi process cha và con.

> **- Tản mạn về kĩ thuật *copy-on-write*:**
> - Đầu tiên khi ta gọi system call fork(), thì sẽ tạo process con, với process con là bản sao của process cha. Ý tưởng ở đây là **lúc đầu** Process con và cha đều sử dụng chung các vùng nhớ *Page Memory*, nhưng khi một trong 2 process muốn sửa đổi dữ liệu trên vùng nhớ đó thì process con sẽ phải copy vùng nhớ đó ra và sử dụng riêng, điều này làm 2 process không bị ảnh hưởng gì.
> **Chú ý:** Memory được load lên Ram được chia làm nhiều Pages, chỉ Page nào bị Process sửa đổi mới được copy và sửa đổi riêng chứ ko sửa đổi tất cả các Page.
> ![](2022-06-27-18-09-56.png)  

**2. Initialized Data Segment(DS)**
> Là một phần của không gian địa chỉ ảo của chương trình(*virtual address space*), chứa các biến toàn cục và biến tĩnh được khởi tạo bởi người lập trình.
> DS không phải là read-only *hoàn toàn*, và giá trị của các biến có thể được thay đổi tại thời điểm run-time.

> VD: Ta khởi tạo và gán giá trị các biến global, static global, hoặc static local.</br>
> int a = 5; </br>
> char abc[] = "Hello ae wibu";     // read-write DS </br>
> char *hihi = "hello";             // read-only      </br>
> int main() {static int x = 6;}

**3. Uninitialized Data Segment(BSS):** 
> Data trong Segment này được Kernel khởi tạo bằng 0 trước khi chương trình bắt đầu thực thi. Segment này chứa tất cả các biến global và static được khởi tạo bằng 0 hoặc không có khởi tạo rõ ràng trong mã nguồn.

> VD: int i;       </br>
> static abc[30];  </br>

**4. Heap:**
> Heap là phân đoạn được sử dụng để cấp phát động.

**5. Stack:**
> - Dữ liệu trong Stack được chia làm từng frame, gọi là stack frame.
> - Activation record: Khi một fucntion gọi một function khác, một Stack frame sẽ được đẩy vào Stack. Stack frame này được gọi là Activation record.
> - Mỗi Activation record có parameters, local variables, and return address.
>   - Lúc đầu, hàm *main()* sẽ được gọi, vậy Activation record sẽ được tạo ra cho hàm main(), và sẽ được đẩy vào stack.
>   - Sau đó, khi main() gọi function *f1()*, nó cũng tạo ra Activation record cho f1() ở top of stack.
>   - Khi hàm f1() kết thúc, nó sẽ trở về hàm main(), và xóa Activation record khỏi stack luôn.  
> ![](2022-06-28-23-12-07.png)

## II. System Call fork()
> - Ta có **chú ý**: Ở tiến trình A, khi gọi fork tạo ra tiến trình con B.
> - Ta luôn có system call **getpid()** thì luôn lấy pid ở tiến trình đang chạy, gọi **getppid()** thì lấy pid của tiến trình đẻ ra tiến trình đang chạy đó.
>   - Nếu ta muốn lấy pid của tiến trình A tại tiến trình ***A*** thì gọi getpid().
>   - Nếu ta muốn lấy pid của tiến trình A và B tại tiến trình ***B*** thì gọi getppid() và getpid().

## III. System Call wait
> - Được sử dụng để theo dõi trạng thái kết thúc của 1 trong các tiến trình con mà tiến trình cha tạo ra
> - Hàm pid_t wait(int *status);
>   - Tại thời điểm wait() được gọi, nó sẽ block cho đến khi có 1 tiến trình con kết thúc or thay đổi trạng thái kết thúc
>   - Nếu tồn tại 1 tiến trình con đã kết thúc trước thời điểm gọi wait(), **nó sẽ return ngay lập tức**
>   - *Hạn chế*: Không kiểm soát được cụ thể tiến trình con nào trả về

> - Ta có một số marco để xem tiến trình kết thúc như nào:
>       - *WIFEXITED(int *status)*: Trả về 1 nếu tiến trình con kết thúc 1 cách bth
>       - *WIFSIGNALED(status)*: rả về 1 nếu tiến trình con kết thúc khi bị kill

> - Để xử lý *Hạn chế* ở system call wait(), ta sử dụng system call *waitpid(pid_t pid, int *status, int option)* để theo dõi chính xác tiến trình con nào mong muốn.


