    Cách tạo static chuẩn:

+, Tạo 1 folder chứa file object --> obj
+, tạo 1 folder chứa file static --> lib/share

B1: Tạo file object:
    stage1:
        gcc -c ./src/helloViet.c -o ./obj/helloViet.o -I ./inc/ 
        gcc -c ./src/helloWibu.c -o ./obj/helloWibu.o -I ./inc/

B2. Link các file object này lại với nhau
    stage2:
        gcc -shared ./obj/helloViet.o ./obj/helloWibu.o -o lib/shared/libmyShared.so

    
    --> Tạo ra file static: libmyShared.so
        +, Chú ý: file tạo cần có tên đầu file là lib

B3. Sử dụng shared:
    using:
        gcc -c -o ./obj/main.o main.c
        gcc  obj/main.o -Llib/shared -lmyShared -o use-shared-library
        sudo mv lib/shared/libmyShared.so /usr/lib
        sudo chmod 755 /usr/lib/libmyShared   
    --> Tạo ra file thực thi use-shared-library
    --> Ở file libmyShared.a ta tách lib ra và lấy "myshared" và ghép với đầu l
        --> Đầu "l" ở đây chỉ file static
    
    --> Đầu "L" chỉ thư mục chứa file static:  Llib/static

    --> Để có thể chạy được file thực thi này ta cần 2 lệnh để xét: 
        sudo mv lib/shared/libmyShared.so /usr/lib
	    sudo chmod 755 /usr/lib/libmyShared.so