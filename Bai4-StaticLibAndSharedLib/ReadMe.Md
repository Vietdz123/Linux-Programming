> # StaicLib And ShareLib

> ## I. Sự khác nhau giữa ShareLib và StaicLib

> **1.1 Thời điểm Linking Time:**

> - **StaticLib**:
>    - Tất cả các modules trong thư viện sẽ được coppy vào trong file thực thi tại thời điểm biên dịch(compile time)>
>        - Dẫn đến khi ctrinh 3MB, các lib kia có dung lượng 4MB
>            - Thì tổng dung lượng ctrinh là 7MB
>            - Nhưng khi có nhiều file(Vd là 5 files) cùng đếu sử dụng file đó, thì tổng số dung lượng là: 3 + 4*5 = 23(MB)          
>    -  Khi chương trình được load vào bộ nhớ, OS chỉ đặt 1 file thực thi duy nhất gồm Source cide và thư viện được link(Static linking).
<div></div>

> - **Sharelib:**
       - Được sử dụng trong quá trình link khi cả file thực thi và file thưc viện đều được load vào bộ nhớ(run time). Một sharelib có thể được nhiều ctr sử dụng.
       - Khi nhiều file(Vd 5 file) đều sử dụng sharelib thì cũng chỉ tốn 4MB cho cả 5 file
       -   Bộ nhớ sharedlib đỡ tốn bộ nhớ hơn staticlib.

>**2.1 Extern file changes:**

> - **Với staticlib**:
>    - File thực thi cần recompile lại bất cứ khi nào có sự thay đổi trong static lib
<div></div>

> -  **Với sharedlib:**
>    - Không cần biên dịch lại file thực thi.
>      -   Vì tại thời điểm runtime, thì ctr với sharedlib mới link lại với nhau.

>**3.1 Time:**

> - staticlib tốn nhiều thời gian thực thi hơn ShareLib.
>    -  Vì staticlib ở trong ở cứng, nên khi nào cần tải dữ liệu ở staticlib lên ram sẽ tốn nhiều thời gian hơn với sharelib khi cả 2 đã đều ở sẵn trên ram rồi.
>    -  Nhưng với hệ thống có ít ram, thì sử dụng sharelib sẽ làm mất tài nguyên ram, nên họ vẫn dúng staticlib
