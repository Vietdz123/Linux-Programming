> # Linux-Programming

> ## Overview about IPC: Các cơ chế trao đổi dữ liệu giữa các Process.

![](2022-06-27-15-38-37.png)

> **IPC chia làm 2 phần**: 
-   Communication
-   Synchonization 

> ### I. Synchonization
- Với các **Unamed** thì thường được sử dụng cho các Process có mỗi quan hệ cha con(Related).
- Với các **Named** thì thường được sử dụng cho các Process ko có mối quan hệ tới nhau(Unamed).

> **1.1 Data Transfer**
- Đặc điểm chung là nếu 1 bên gửi dữ liệu vào trong Pipe hay Message Queue,... mà bên nhận nhận dữ liệu đấy thì dữ liệu đó sẽ mất đi trong Queue hay Pipe,...
- Data Transfer chia làm 2 loại:
  - **Message**: *Dữ liệu gửi đi sẽ được đóng gói thành từng message*.
    -  **MessageQueue**: SystemV Message Queue và Posix Message Queue.
    -  **Datagram Socket**.
  - **Byte Stream**: *Dữ liệu đẩy vào Pipe hoặc socket theo các luồng byte, ta có thể lấy bao nhiêu byte trong luồng đó cũng được*.
    - **PIPE**: *Uname PIPE: Sử dụng 1 virtual Pipe để tạo ra định danh của hệ thống, nếu hệ thống bị resart thì dữ liệu sẽ bị mất đi*.
    - **FIFO**: *Named PIPE: Sử dụng 1 file thưc trong hệ thống, và khi hệ thống resart thì dữ liệu sẽ không bị mất.*
 - **Stream Socket**: *Sử dụng để truyền tải dữ liệu giữa 2 máy khác nhau hoặc trên cùng 1 máy**.

> **1.2 Shared Memory**
- Nhiều Process có thể tham chiếu đến vùng Shared đó được, và không lo bị mất dữ liệu. Tuy nhiên để giảm tải quá nhiều Process tham gia vào hệ thống thì ta thường kết hợp Semaphore và Shared Memory
- Shared Memory chia làm 2 loại:
  - **System V Shared Memory**: *Thuộc loại Annoymous Mapping, kiểu Virtual*.
  - **Posix Shared Memory**: *Sử dụng File Mapping*.
  - Kĩ thuật thường được sử dụng: **Memory Mapping**:
    - **Annoymous Mapping**
    - **FIle Mapping**


>### II. Synchonization

> **2.1 Đồng bộ ở cấp độ file:**
- "record" lock(fcntl()).
  - Có khả năng lock từng byte trong file.
- file lock(flock()).
  - Lock luôn cả một file.

> **2.2 Đồng bộ ở cấp độ Thread:**
- Khóa Mutex
- Conditional variable, và thường được kết hợp với mutex

> **2.3 Đồng bộ giữa các Process**
<div>Mặc dù Semaphor cũng đồng bộ được giữa các Thread nhưng đa số Semaphore được sử dụng để đồng bộ giữa các Process</div>

- Semaphore
    - SystemV Semaphore(Không học).
    - Posix Semaphore
        - Named: *Sử dụng 1 file thực để làm khóa*.
        - Unamed: *Sử dụng 1 Virtual file để làm khóa*.