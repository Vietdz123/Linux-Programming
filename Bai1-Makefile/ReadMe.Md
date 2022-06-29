# Giới thiệu Makefile
    
# I. Makefile là gì:
- Makefile là 1 script bên trong có chứa các thông tin:
  - Cấu trúc của một Makefile (file, depedency):
    - Các cmd dùng để tạo hủy file.
    - Chương trình Make: sẽ đọc nội dung trong Makefile và thực thi nó.

# II. Cấu trúc của một Makefile:
    hellomake(Target): main.c(depedency)
        gcc -o main main.c(Action)
-  Khi ta gõ make hellomake thì sẽ kiểm tra phần depedency(main.c) tồn tại hay chưa:
   -  Nếu có thì mới thực hiện rule hellomake.
   - Nếu ko có thì ko thực hiện.

# III. Ví dụ:
    File Makefile:
        .PHONY: rule1 rule2 rule3 all clean

        var = "var"
        var3 ?= "var3"
        include vietdz.mk

        var1 = $(var)
        var2 := $(var)
        var3 ?= $(var)

        rule4: huyNgu.c huyNgu.h
                @echo $@
                @echo $<
                @echo $^

        rule3:
                @echo "$(var1)"
                @echo "$(var2)"
                @echo "$(var3)"

        var := "changed"

        rule1:
                echo "Hello im rule1"

        rule2:
                @echo "Hello im rule1"

        all:
                gcc -o main main.c ./inc/hello.c -I.

        clean:
                rm -rf main


 >  - **Kết quả:**</br>
 >      - make rule1:               --> In ra cả 2 kết quả</br>
 >          - echo "Hello im rule1"  --> In ra câu lệnh thực hiện</br>
 >          - Hello im rule1         --> In ra cả kết quả.</br>
 >      - make rule2:</br>
 >          - Hello im rule2         --> In ra mỗi kết quả.</br>
        

# IV. Các phép gán:
        +, var1 = $(var) 
            --> Phép toán đệ quy, biến var thay đổi như nào thì var1 thay đổi theo như thế
        
        +, var2 := $(var)
            --> Phép toán trực tiếp, chỉ gán theo câu lệnh hiện tại

        +, var3 ?= $(var)
            --> Kiếm tra var3 có giá trị chưa, nếu chưa có thì sẽ gán var cho var3
                                                Nếu có thì ko gán cho var3 nữa.


    --> Khi trong folder có nhiều file make files
        VD: Makefile, vietdz.mk, .....
        --> Khi gọi make thì ưu tiên chạy file Makefile, vậy để chạy file khác ta dùng lệnh
                make -f vietdz rule3.

    --> Khi ta include vietdz.mk
        --> thì nội dung file vietdz.mk sẽ được chèn trực tiếp vào file mà include file đó.

    --> Biến môi trường: 
            rule4: huyNgu.c huyNgu.h
                @echo $@
                @echo $<
                @echo $^

        --> Kết quả:   
                rule4
                huyNgu.c
                huyNgu.c huyNgu.h
            +, Với $@: Giá trị đầu tiên nằm bên trái dấu :
            +, Với $<: Giá trị đầu tiên nằm bên phải dấu :
            +, Với $^: toàn bộ giá trị nằm bên phải dấu :
        
