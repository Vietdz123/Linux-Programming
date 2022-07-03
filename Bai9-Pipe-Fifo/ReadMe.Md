> # PIPE và FIFO trong Linux

> - Pipe cho phép gửi nhận data trong cùng 1 tiến trình or giữa các tiến trình related tới nhau.


# I. PIPE.
> **1.1. Cách tạo PIPE.**

> int pipefd[2];
> pipe(pipefd);

> - Hàm pipe() sẽ sinh ra pipe
>   - pipefd[1] là đầu để ghi data vào pipe
>   - pipefd[0] là đầu để đọc data 

> **1.2 Đọc ghi qua PiPE:**

> - Sau khi đã tạo pipe ở bước 1, ta sử dụng 2 hàm read(), write() để đọc ghi dữ liệu vào pipe.
> VD: write(pipefd[1], "Hello ae wibu");
> VD: read(pipefd[0], buff, 40);

> - **Chú ý 1**: Số 40 ở đây có nghĩa là số byte nhiều nhất có thể đọc được.
> - **Chú ý 2**: Hàm read() sẽ block cpu cho tới khi có data được ghi vào bên trong pipe.
> - **Chú ý 4**: Khi pipe đã full dữ liệu, chương trình sẽ block ở hàm write(), đến khi có hàm read() lấy dữ liệu đi khỏi pipe thì nó mới đẩy tiếp data vào.
> - **Chú ý 3**: pipe có thể được sử dụng trong các tiến trình cha con. Hàm pipe() phải được gọi trước câu lệnh fork().
> - **Chú ý 4**: Ơ process child muốn đọc dữ liệu từ bên process cha thì cần đóng các đầu ko cần thiết.
>   - Bên cha: close(fd[0]);    //Đóng đầu đọc
>   - Bên con: close(fd[1]);    // Đóng đầu ghi
>   - Sau khi bên cha truyền xong cần đóng cả đầu ghi.
>       - Bởi vì bên "con" sẽ đợi đến khi có data gửi tới để dừng block nên khi không close(fd[1]) thì CPU sẽ ngầm định rằng vẫn sẽ có 1 sự kiến nào đóc sẽ write vào pipe. Nên process con vẫn bị treo ở hàm read().
>       - Tóm lại là ta cần đóng hàm fd[1] khi dùng xong để thông báo tới process con là đã ghi xong, sẽ ko có data tới để thoát khỏi block.

> **1.3 popen()**
> Hàm popen () sẽ thực hiện lệnh được chỉ định bởi string command. Nó sẽ tạo một pipe giữa chương trình gọi popen() và lệnh được thực thi, và sẽ trả về một con trỏ đến một stream mà có thể được sử dụng để đọc hoặc ghi vào đường dẫn.
> Đọc ví dụ để hiểu.

# II. FIFO
> - Là một kiểu mở rộng của pipe.
> - **PIPE** chỉ tồn tại trong suốt process hoặc bị close ở 2 đầu.
> - **FIFO** có tên trong hệ thống tệp và được mở rộng như 1 file thông thường
> - FIFO được tạo ra nhờ:
>   - Hàm ***mkfifo(PATH_FIFO, O_RDWR)***
>   - Từ shell: mkfifo [-m mode] pathname
>       - VD: mkfifo -m 0666 ./fifo
> - Từ đây ta có thể open, read, write fil FIFOs.
> - FIFO được sử dụng để nhiều process đọc ghi data qua nhau nhờ file FIFO vừa tạo.