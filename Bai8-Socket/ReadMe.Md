# Socket In Linux

# I. Giới thiệu về Socket
> - Thông tin được mô tả trong 1 file socket gồm:
>   - Domain
>   - Type
>   - Prococal

1. **Domain**: Được chia làm 2 loại 
    - Internet Domain: Được sử dụng để giao tiếp 2 máy khác nhau
      - IPv4
      - IPv6
    - Unix Domain: Được sử dụng để giao tiếp trong cùng 1 máy

2. **Type**: Là cơ chế truyền thông tin, Socket có 2 type phổ biến
   -  Stream(TCP).
   -  Datagram(UDP).

3. **Protocol**: Là cách đóng gói dữ liệu
- *chú ý:* Từ Domain và Type sẽ có 1 danh sách protocal tương ứng. Thông thường protocol để là "0"
