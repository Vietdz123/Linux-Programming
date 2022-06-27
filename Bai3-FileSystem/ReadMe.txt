                /****************** File Sytem in Linux ******************\
    
    1. Tổng quan về file in Linux:
        +, Các loại file trên Linux:    
            +, Regular file: Là các loại file thông thường như file text và file thực thi(excutable file)
            +, Directories file: file chứa danh sách các file khác
            +, Character Device file: File đại diện cho các thiết bị không có địa chỉ vùng nhớ
                    VD: ls dev/tty
                    VD2: lsblk
                        --> SỬ dụng để xem các ổ cứng nào đang được mount trên hệ thống(tính cả USB)
                        +, sda2 nơi chứa hệ điều hành.
                    VD2: Khi  ta cắn usb vào 
            +, Block device file: là các file đại diện cho các thiết bị có địa chỉ vùng nhớ
            +, Linkfile: như các file shorkcut (như file) trong window
            +, file socket
            +, file pipe

    2. Quyền trong file:
        +, lệnh change quyền: chmod u+r fileA
                              chmod g+w fileA
                              chmod o+w fileA
            +, chmod 0666 test

        +, Thay đổi quyền sở hữu:
            +, sudo chown viet fileA

    3. System Call:
        +, Linux chia thành 2 không gian xử lý:
            +, User space
                --> Nơi thư viện và các application mà mình chạy
            +, Kernel space
                --> Quản lý phần cứng, memory của phần cứng

        
        +, User space: gồm 2 phần
            +, User Application 
            +, GNU C Library  
                    --> VD: Khi ta cần đọc ghi vào 1 file, ta sử dụng hàm fopen() để mở file
                        --> bản chất hàm fopen() đó sẽ ko thể trực tiếp mở file trong phần cứng, mà nó sẽ gọi 1 System Call "open" để mở file.
                            --> System Call là các lời gọi của hệ thống, được sử dụng để chuyển đổi ko gian giữa User space và Kernel space

    4. Quản lý file trong Linux:
        +, Kernel điều khiển việc tương tác giữa tiến trình và file thông qua 3 bảng:
            +, file desciptor table
            +, Open file table
            +, I-node table
        
        +, Bảng i-node table là một bảng mà mỗi phần tử trong i-node table đại diện cho 1 file, chứa các thông tin của 1 file.
            +, Bảng i-node table gồm các cột như: inode number, file type, size, hardlink, permission, và con trỏ trỏ tới file(file ptr), và content trong file
        +, Bảng openfile table:
            +, Bảng openfile table gồm các thông tin: stt, file offset(SEEK SET, SEEKSET + 3, .....), status flag(R/W), inode ptr(1, 5, ...)
                +, Khi ta open 1 file, inode number trong bảng inode table tới vị trí inode ptr của bảng openfile, và cũng như lấy ra các cờ trạng thái R/W trong lệnh ta open (open("file A", O_RDWR));
                        cũng như file offset.
                +, CÙng 1 file được mở có thể có nhiều phần tử bảng openfile table, cũng như các cờ status, file offset khác nhau, nhưng inode ptr giống nhau vì cùng chỉ tới 1 file
        +, Bảng file desciptor table:
            --> Các process khác nhau sử dụng các bảng file desciptor khác nhau, đ liên quan gì tới nhau cả.
            +, Chứa các thông tin như fd, fd flags, file ptr.
                --> Khi mở 1 file, file ptr sẽ được map sang stt của bảng openfile table
                --> Sau đó nó sẽ tìm kiếm file fd nào chưa được sử dụng và sẽ gán giá trị vào fd.
                    3 file đầu fd được sử dụng là stdin, stdout, stderr.
        
    Chú ý:
        +, Một process có thể có nhiều file desciptor cùng tham chiều vào một vị trí trong openfile table
            --> Bằng việc sử dụng 2 hàm dup(), và dup2().
            Giải thích: Bth ta mở 1 file 2 lần trong cùng 1 process, thì sẽ tạo ra 2 file ở open file table và cũng đồng nghĩa là tạo ra 2 file fd
                +, Nhưng nếu ta mở file đó 1 lần, rồi sử dụng hàm dup() hoặc dup2(), thì sẽ có 2 files desciptor có giá trị khác nhau, nhưng chỉ tham chiếu tới 1 file chung duy nhất trong openfile table.
        
        +, Hai process cùng mở 1 file, tham chiếu tới cùng một openfile table.
            --> Sử dụng fork().

    +, Chú ý quan trọng:
        +, Ta có khi ta viết chương trình đọc và ghi 1 file, sau khi build file đó ra file thực thi, ta thực hiện việc load file thực thi đó lên ram rồi chạy
            +, ta có tốc độ trên ram rất nhanh và tất độ trên ổ cứng rất chậm.
                --> Do thằng read() cần chờ HDD gửi dữ liệu lên, mà HDD gửi rất chậm --> CHương trình trên Ram bị delay
                --> Có khả năng gây ra hỏng phần cứng nhất là (SD Card).
            --> Để khắc phục vấn đề này thì Kernel sử dụng 1 file: page cache 
                +, Khi kernel đọc ghi liên tục vào 1 file trong ổ cứng, thì kernel sẽ tạm lưu file đó vào trong 1 Page Cache(Page cache là 1 file nằm trên ram, và được mapping tới file trong ổ cứng).
                    --> Dẫn đến chương trình nằm trên ram sẽ đọc ghi trực tiếp trên Page Cache --> Cải thiện tốc độ
                    --> VD: page cache khi đủ 20 byte sẽ ghi xuống phần cứng 1 lần
                            --> Nên ta muốn ghi 100 byte thì chỉ 5 lần đọc ghi xuống ổ cứng
                        --> Nhưng sẽ xảy ra lỗi là khi page cache chưa đủ dữ liệu, nó sẽ chưa ghi luôn xuống phần cứng
                            --> Có thể bị miss file
                            --> Để khắc phục vấn đề này ta dùng lênh sync
                                +, Để bắt Page cache ghi luôn xuống ổ cứng mà ko cần chờ đủ buffer ở cache mới ghi xuống.
             
    5. File Locking
        +, File locking được sử dụng để quản lý việc nhiều tiến trình cùng đọc và ghi vào 1 file.
        +, Cách hoạt động:
            B1: Ghi trạng thái lock vào I-node của file
            B2: Nếu thành công thì thực hiện đọc ghi file, nếu ko thành công nghĩa là file đang được tiến trình khác sử dụng
                --> ta có thể chờ để tiến trình khác đọc xong, hoặc quyết định ko đọc/ghi vào file đó nữa
            B3: Sau khi đọc/ghi xong gỡ trạng thái lock ra khỏi I-node của file
        

        +,  Có 2 cách để lock 1 file:
            +, Hàm Flock():
                +, ĐƠn giản
                +, Thông tin ghi vào i-node là trạng thái lock
                +, Lock toàn bộ file
                +, Tải 1 thời điểm chỉ có 1 tiến trình đọc/ghi file

                --> Hàm flock()
                    +, int flock(int fd, int operation);
                    +, operation: giá trị lock muốn SET 
                        +, LOCK_SH: Tiến trình có thể đọc file, ko Ghi
                        +, LOCK_EX: Tiến trình có thể đọc ghi file   
                        +, Lock_UN: Thông báo file ko bị lock
                        +, LOC_NB: nếu ko dùng flag này hàm flock sẽ ko kết thúc cho tới khi set được lock 
                                --> Nó sẽ thử mở 1 khóa và nếu file đó ko bị khóa thì nó sẽ vào thực hiện đọc ghi file đó
                                --> Hoặc nếu file đó bị khóa rồi sẽ được chọn 2 hành vi, có thể chờ cho file kia thực hiện xong sẽ vào thực thì hoặc thoát ra luôn. 


            +, Hàm fcntl()
                +, Phức tạp
                +, Thông ghi vào i-node kaf trạng thái lock, khu vực lock, tiến trình lock  
                        --> Nghĩa là ko lock 1 fle, mà chỉ lock 1 phần vị trí của file
                +, Lock được từng khuc vực của file
                +, Nhiều tiến trình có thể đọc/ghi cùng 1 file mà ko xung đột 

            --> fcntl(fd, cmd, &lockstruct);
                +, Với cmd: action muốn thực hiện
                    +, F_SETLCK: đặt lock, bỏ lock
                    +, F_GETLK: đọc thông tin lock
                +, lockstruct: thông tin muốn lock(gồm trạng thái lock, vùng muốn lock, process lock).