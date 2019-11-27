# Về báo cáo

**Đồ án 1: "Biểu diễn và tính toán số nguyên lớn"**
Môn `CSC10005`: Kiến trúc máy tính và hợp ngữ
Khoa CNTT – CTĐA, Trường ĐH KHTN – ĐHQG TP.HCM
`2019-11-08 ~ 2019-11-30`

Nhóm gồm 2 thành viên (thuộc lớp `18CLC6`):

-   `18127221`: Bùi Văn Thiện
-   `18127231`: Đoàn Đình Toàn



---



# Về đồ án (`QInt`)

| Công việc                           | Thành viên thực hiện |
| ----------------------------------- | :------------------: |
| Thiết lập đồ án (GitHub repo, v.v.) |      Văn Thiện       |
| Test chương trình (hardcore)        |      Đình Toàn       |
| Viết báo cáo                        | Đình Toàn, Văn Thiện |



### Tổng quan

-   Mức độ hoàn thiện: 100%; đã pass 100 test cases cơ bản được đính kèm theo yêu cầu đồ án.
-   Môi trường lập trình: Microsoft Visual Studio 2019 trên Windows 10 + JetBrains CLion 2019.2 trên Ubuntu 18.04.3 LTS



### Ý tưởng thiết kế

-   <backstory đi tìm cách lưu trữ; thử mảng bool, 4 biến int32_t, v.v.>
-   <tìm ra `std::bitset`>
-   <mọi thứ sẽ xử lý trên hệ 2; hệ 10 hay 16 chỉ là cách biểu diễn và là nhiệm vụ của các hàm chuyển đổi>
-   <gì gì đó>

-   Phạm vi biểu diễn của `QInt`: $-2^{127}$ tới $2^{127}-1$



### Các nguồn tham khảo

-   [`std::bitset` trên CPlusPlus.com](http://www.cplusplus.com/reference/bitset/bitset/)
-   Dan Vanderkam, [Arbitrary Precision Hex <-> Dec converter in JavaScript](https://www.danvk.org/hex2dec.html)
-   Ernst W. Mayer (2016), "Efficient long division via Montgomery multiply", phiên bản 6 ([arXiv:1303.0328v6 [cs.DS]](https://arxiv.org/abs/1303.0328v6)).
    Có sẵn file đính kèm với báo cáo (`1303.0328.pdf`).



---



# Chức năng

| Chức năng                                                    | Thành viên cài đặt |   Đã hoàn thiện    |
| ------------------------------------------------------------ | :----------------: | :----------------: |
| Đọc/ghi file                                                 |     Văn Thiện      | :heavy_check_mark: |
| Chuyển đổi base (2 $\rightarrow$ 10, 2 $\leftrightarrow$ 16) |     Văn Thiện      | :heavy_check_mark: |
| Chuyển đổi base (10 $\rightarrow$ 2)                         |     Đình Toàn      | :heavy_check_mark: |
| `operator~` (NOT)                                            |     Văn Thiện      | :heavy_check_mark: |
| `rol()` (Xoay trái 1bit)                                     |     Văn Thiện      | :heavy_check_mark: |
| `ror()` (Xoay phải 1bit)                                     |     Văn Thiện      | :heavy_check_mark: |
| `operator&` (AND)                                            |     Văn Thiện      | :heavy_check_mark: |
| `operator|` (OR)                                             |     Văn Thiện      | :heavy_check_mark: |
| `operator^` (XOR)                                            |     Văn Thiện      | :heavy_check_mark: |
| `operator<<` (Shift trái)                                    |     Văn Thiện      | :heavy_check_mark: |
| `operator>>` (Shift phải số học)                             |     Đình Toàn      | :heavy_check_mark: |
| `operator+` (Phép cộng)                                      |     Văn Thiện      | :heavy_check_mark: |
| `operator-` (Phép trừ)                                       |     Văn Thiện      | :heavy_check_mark: |
| `operator*` (Phép nhân)                                      |     Đình Toàn      | :heavy_check_mark: |
| `operator/` (Phép chia)                                      |     Đình Toàn      | :heavy_check_mark: |



[Với mỗi chức năng: insert header, mô tả, ảnh chụp minh họa]



### Chuyển đổi cơ số

Việc chuyển đổi giữa các hệ cơ số được cài đặt trong constructor của `QInt` (chuyển từ string số hệ 2/10/16 sang biểu diễn nhị phân trong phần private của `QInt`, tức bitset) và hàm chuyển `toString` (chuyển từ bitset sang string số hệ 2/10/16.)



##### base2 $\rightarrow$ base10

Mỗi bit trong bitset sẽ có giá trị tương ứng trong hệ 10 là $2^k$, với $k = [0, 127]$.

Kiểu primitive int lớn nhất có thể có trong C(++) là 64-bit, nên việc tính toán và cộng dồn thông thường sẽ gây tràn số. Khi đó, để tính $2^k$ mà không gây tràn số/không bị giới hạn trong khoảng $2^{64}$, một "bảng $2^k$" sẽ được sử dụng. Bảng này…

-   được cài đặt dưới dạng tương tự mô hình singleton: bảng sẽ được lập ra và tính ngay trong lần đầu tiên một object `QInt` được khởi tạo, và sẽ tiếp tục tồn tại trong bộ nhớ cho đến khi kết thúc vòng đời chương trình (cách cài đặt này sẽ tiết kiệm được chi phí tính toán hơn việc tính $2^k$ riêng lẻ mỗi lần với $k$ bất kì);
-   gồm 128 mảng, tương ứng với 128 giá trị $2^k$ cần tính;
-   mỗi mảng gồm $\lceil \log_{10}(2^{128}) \rceil = 39$ phần tử, tương ứng với 39 chữ số (số chữ số của $2^{128}$), được ghi theo thứ tự trái-qua-phải (hàng đơn vị nằm ở đầu mảng);
-   có mảng đầu tiên chứa $2^0$, và các mảng tiếp theo sẽ bằng 2 lần giá trị từng phần tử của mảng trước đó; 
-   mỗi phần tử trong mảng nếu trong quá trình nhân 2 lên có giá trị lớn hơn 9 sẽ được lấy phần dư cộng dồn qua phần tử kế tiếp.

Khi đã có "bảng $2^k$", việc chuyển bitset thành số hệ 10 bây giờ chỉ còn là việc cộng dồn các giá trị $2^k$ với $k$ tương ứng các bit `1` (duyệt qua bitset từ bit thấp nhất lên), ghi ngược lại từng chữ số trong mảng thành một string, và loại bỏ đi các số 0 thừa ở đầu.



**base2 $\leftarrow$ base10**





##### base2 $\leftrightarrow$ base16

Mỗi 4 bit trong bitset sẽ tương ứng với 1 số trong hệ 16, nên việc chuyển đổi qua lại giữa 2 hệ này tương đối dễ dàng:

-   Duyệt qua bitset từ bit thấp nhất lên, lấy từng nhóm 4 bit mỗi lần
-   Tính giá trị của 4 bit đó ở hệ 10, sau đó so sánh với một mảng gồm 16 chữ số thập lục phân được sắp xếp từ `0` đến `F` để lấy kí tự tương ứng
-   Chèn kí tự đã lấy vào đầu string, và loại bỏ các số 0 thừa ở đầu một khi đã duyệt xong bitset.



##### base10 $\leftrightarrow$ base16

Vì đã có sẳn hàm để chuyển đổi từ hệ 2 sang 10/16, nên cách tiện nhất để chuyển đổi giữa hệ 10 và 16 là thông qua hệ 2 làm trung gian.



### Toán tử logic

Ngoại trừ những toán tử được mô tả bên dưới, các toán tử còn lại (`~`, `&`, `|`, `^` và `<<`) được thực hiện bởi các toán tử tương ứng có sẵn trong `std::bitset`.



##### `rol()`/`ror()` (Xoay trái/Xoay phải 1bit)

Việc xoay bit cơ bản là đánh dấu bit cao nhất (đối với `ror()`) / bit thấp nhất (đối với `rol()`), shift bitset hiện tại theo hướng ngược lại hướng đang xoay, và điền lại bit thấp nhất (đối với `ror()`) / bit cao nhất (đối với `rol()`).



##### `operator>>` (Shift phải số học)

Vì `operator>>` có sẵn trong `std::bitset` là phép shift phải logic nên cần phải xử lý thủ công việc điền các "lỗ trống" có được sau khi shift với bit cao nhất (MSB) thay vì bit `0` trước khi shift. Giải pháp được cài đặt:

-   Tạo một bitset với các bit cao cần điền với MSB đã được đánh dấu. Gọi bitset này là mask.
-   Shift phải bitset hiện tại với `operator>>` có sẵn trong `std::bitset`.
-   OR mask với bitset hiện tại, và trả về kết quả.



### Toán tử số học

##### `operator+` (Phép cộng)

Phép cộng này sẽ duyệt qua bitset của số gốc và số cần cộng, và sau đó thực hiện phép cộng trên từng bit một (kèm với bit nhớ.) Cách cài đặt phép cộng bit trong đây được dựa trên các "luật cộng bit" suy ra từ 8 trạng thái có thể của 3 bit: bit gốc, bit được cộng vào và bit nhớ:

| Bit gốc | Bit được cộng | Bit nhớ | Hành động              |
| ------- | ------------- | ------- | ---------------------- |
| 0       | 0             | 0       | Ghi 0                  |
| 0       | 1             | 0       | Ghi 1                  |
| 1       | 0             | 0       | Ghi 1                  |
| 1       | 1             | 0       | Ghi 0, nhớ 1           |
| 0       | 0             | 1       | Ghi 1, đặt lại bit nhớ |
| 0       | 1             | 1       | Ghi 0, nhớ 1           |
| 1       | 0             | 1       | Ghi 0, nhớ 1           |
| 1       | 1             | 1       | Ghi 1, nhớ 1           |



##### `operator-` (Phép trừ)

Bản chất phép trừ một số là phép cộng với bù 2 của số đó, nên toán tử này tận dụng được `operator+` và `operator~` đã được cài đặt trước đó.



##### `operator*` (Phép nhân)



##### `operator/` (Phép chia)