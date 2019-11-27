# Về báo cáo

**Đồ án 1: "Biểu diễn và tính toán số nguyên lớn"**
Môn `CSC10005`: Kiến trúc máy tính và hợp ngữ
Khoa CNTT – CTĐA, Trường ĐH KHTN – ĐHQG TP.HCM
`2019-11-08 ~ 2019-11-30`

Nhóm gồm 2 thành viên (thuộc lớp `18CLC6`):

-   `18127221`: Bùi Văn Thiện
-   `18127231`: Đoàn Đình Toàn



---



# Về đồ án

### Tổng quan

-   Mức độ hoàn thiện: 100%; đã pass 100 test cases cơ bản được đính kèm theo yêu cầu đồ án.
-   Môi trường lập trình: Microsoft Visual Studio 2019 trên Windows 10 + JetBrains CLion 2019.2 trên Ubuntu 18.04.3 LTS



### Ý tưởng thiết kế

-   <backstory đi tìm cách lưu trữ; thử mảng bool, 4 biến int32_t, v.v.>
-   <tìm ra std::bitset>
-   <mọi thứ sẽ xử lý trên hệ 2; hệ 10 hay 16 chỉ là cách biểu diễn và là nhiệm vụ của các hàm chuyển đổi>
-   <gì gì đó>

-   Phạm vi biểu diễn của `QInt`: $-2^{127}$ tới $2^{127}-1$



### Các nguồn tham khảo

-   [std::bitset trên CPlusPlus.com](http://www.cplusplus.com/reference/bitset/bitset/)
-   Ernst W. Mayer (2016), "Efficient long division via Montgomery multiply", phiên bản 6 ([arXiv:1303.0328v6 [cs.DS]](https://arxiv.org/abs/1303.0328v6)).
    Có sẵn file đính kèm với báo cáo (`1303.0328.pdf`).



---



# Chức năng

| Chức năng                                                    | Thành viên cài đặt | % hoàn thiện |
| ------------------------------------------------------------ | ------------------ | ------------ |
| Chuyển đổi base (2 $\rightarrow$ 10, 2 $\leftrightarrow$ 16) | Văn Thiện          | 100%         |
| Chuyển đổi base (10 $\rightarrow$ 2)                         | Đình Toàn          | 100%         |
| `operator~` (NOT)                                            | Văn Thiện          | 100%         |
| `rol()` (Xoay trái 1bit)                                     | Văn Thiện          | 100%         |
| `ror()` (Xoay phải 1bit)                                     | Văn Thiện          | 100%         |
| `operator&` (AND)                                            | Văn Thiện          | 100%         |
| `operator|` (OR)                                             | Văn Thiện          | 100%         |
| `operator^` (XOR)                                            | Văn Thiện          | 100%         |
| `operator<<` (Shift trái)                                    | Văn Thiện          | 100%         |
| `operator>>` (Shift phải số học)                             | Đình Toàn          | 100%         |
| `operator+` (Phép cộng)                                      | Văn Thiện          | 100%         |
| `operator-` (Phép trừ)                                       | Văn Thiện          | 100%         |
| `operator*` (Phép nhân)                                      | Đình Toàn          | 100%         |
| `operator/` (Phép chia)                                      | Đình Toàn          | 100%         |



[Với mỗi chức năng: insert header, mô tả, ảnh chụp minh họa]



### Chuyển đổi cơ số

Việc chuyển đổi giữa các hệ cơ ôngsố sẽ được cài đặt trong constructor của `QInt` (chuyển từ string số hệ 2/10/16 sang biểu diễn nhị phân trong phần private của `QInt`, tức bitset) và hàm chuyển `toString` (chuyển từ bitset sang string số hệ 2/10/16.)



##### base2 $\leftrightarrow$ base10



##### base2 $\leftrightarrow$ base16



##### base10 $\leftrightarrow$ base16

Vì đã có sẳn hàm để chuyển đổi từ hệ 10/16 sang 2, nên cách tiện nhất để chuyển đổi giữa hệ 10 và 16 là thông qua hệ 2 làm trung gian.



### Phép toán logic

##### `operator~` (NOT)



##### `rol()` (Xoay trái 1bit)



##### `ror()` (Xoay phải 1bit)



##### `operator&` (AND)



##### `operator|` (OR)



##### `operator^` (XOR)



##### `operator<<` (Shift trái)



##### `operator>>` (Shift phải số học)





### Phép toán số học

##### `operator+` (Phép cộng)



##### `operator-` (Phép trừ)



##### `operator*` (Phép nhân)



##### `operator/` (Phép chia)