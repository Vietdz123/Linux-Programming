    Cách tạo static chuẩn:

+, Tạo 1 folder chứa file object --> obj
+, tạo 1 folder chứa file static --> lib/static

B1: Tạo file object:
    stage1:
        gcc -c ./src/helloViet.c -o ./obj/helloViet.o -I ./inc/ 
        gcc -c ./src/helloWibu.c -o ./obj/helloWibu.o -I ./inc/

B2. Link các file object này lại với nhau
    stage2:
        ar rcs ./lib/static/lib_mylib.a ./obj/helloViet.o ./obj/helloWibu.o
    
    --> Tạo ra file static: lib_mylib.a
        +, Chú ý: file tạo cần có tên đầu file là lib

B3. Sử dụng static:
    using:
        gcc -c -o ./obj/main.o main.c
        gcc -o main ./obj/main.o -Llib/static -l_mylib
    
    --> Ở file lib_mylib.a ta tacihs lib ra và lấy "_mylib.a" và ghép với đầu l
        --> Đầu "l" ở đây chỉ file static
    
    --> Đầu "L" chỉ thư mục chứa file static:  Llib/static
