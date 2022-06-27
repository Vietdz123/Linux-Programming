# Quá trình biên dịch 1 file thực thi

    +, Quá trình 1: Giai đoạn tiền xử lý:
        +, Loại bỏ các comments
        +, Mở rộng các macros
        +, Mở rộng các include file
        +, Biên dịch các câu lệnh điều kiện
    --> Kết quả thu được là 1 file .i

    stage1:
        gcc -E main.c -o main.i

    +, Quá trình 2: Biên dịch file .s sang file asm
    stage2:
        gcc -S main.i -o main.S

    +, Quá trình 3: Biên dịch asm sang mã máy
        --> Tạo ra file .o
    stage3:
        gcc -c main.s -o main.o

    --> Để xem hiển thị file đó ở dạng hex thì gõ lệnh:
        hexdump -C main.o

    +, Qua trình 4: Giai đoạn linker(linking)   
    +, Mồi file .o thu được ở giai đoạn 3 là 1 phần của chương trình
    +, Ở giai đoạn linking sẽ liên kết chúng lại để được 1 file hoàn chỉnh
