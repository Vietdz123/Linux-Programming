            /**************** Character Device Driver ****************\
    
    +, Tổng quát: 3 bước
        --> Bước 1: Allocate devive number(major/minor)
                --> Cấp phát số device number cho thiết bị mình muốn
            +, Device number được tạo ra bởi 2 số: major và minor number
                +, major number: là số xác định liên kết giữa Driver và device. Một major number có thể chia sẻ giữa nhiều Device Driver.
                    --> Đại diện cho thiết bị cụ thể

                +, minor number: là số dùng để phân biệt các thiết bị vật lý riêng lẻ.
                    --> Đại diện cho phiêm bản thiết bị.
                

            +, Để cấp phát device number ta có thể sử dụng 1 trong 2 cách sau:      --> check xem đã cấp phất number file: cat /pro/devices
                +, Static Allocating
                    dev_t dev = MKDEV(173, 0);          --> Chọn số 173
                    (register_chrdev_region(&mdev.dev_num, 1, "m-cdev")
                +, Dynamic Allocating
                    --> Với Dynamic Allocating: thì kernel tự tìm cho chúng ta một số major phù hợp  //Vì đôi khi ta ko biết phải chọn số nào
                    +, VD: alloc_chrdev_region(&mdev.dev_num, 0, 1, "m-cdev")
                        --> Số 0: là số bắt đầu của minor number
                        --> SỐ 1: là số lượng minor number
                            --> Nếu Kernel cấp phát cho ta số major là 80, thì ta sẽ được 2 số là 80.0
                    +, VD: alloc_chrdev_region(&mdev.dev_num, 3, 2, "m-cdev")
                            --> Nếu Kernel cấp phát cho ta số major là 80, thì ta sẽ được 2 số là 80.3 và 80.4
                    
                    +, unregister_chrdev_region(mdev.dev_num, 1);
                        --> Xóa cấp phát động, giải phóng bộ nhớ.
                    
                    --> "m-cdev": Tên của device number --> cat /pro/device

        +, Bước 2: Create  Device file          --> Check xem đã có device file chưa: ls -l /dev/ | grep 235
            --> Tạo class Device 
                    --> Mỗi nhóm device có một nhiệm vụ riêng biệt: nhóm tai nghe, nhóm kết nối,...
                    --> Nên ta cần chia device vào các class 
                +, mdev.m_class = class_create(THIS_MODULE, "m_class")
                    --> THIS_MODULE: như con trỏ this.
                        m_class: Tên class                   
            --> Tạo device file
                +, device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "m_device");

    
    +, Khi một Application muốn giao tiếp với 1 thiết bị phần cứng thì trải qua các bước như nào:
        Đầu tiên Application sẽ đọc ghi vào phần Device file(or Device Node) vì Device file đại diện cho một phần cứng cụ thể
                Mà Device file lại được gán một số, gọi là Device number(major và minor). Nên Device file sẽ tham chiếu xuống Device number, từ số 
                major number và minor number, nó sẽ tìm được đúng Device Driver cho mình, và trong chương trình điều khiển sẽ điều khiển Hardware

    --> Khi ta muốn đọc ghi vào thanh ghi, ta có thể đọc ghi vào device file
        +, Driver đại diện bởi struct cdev
        +, Device(thiết bị của mình) được đại diện bởi Device file
            --> Driver giúp cho thiết bị mình chạy được.