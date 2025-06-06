#include "main.h"

int main(int argc, char** argv) {
	return vidu10(argc, argv);

	return 0;
}

/*
Cấu hình project C/C++ trên VS: (thư viện ngoài)
- các file .h/.hpp: 
	Project properties -> 
	C/C++ -> 
	general -> 
	Additional Include directoties -> 
	điền thư mục vào
- Các file .lib:
	Project properties -> 
	Linker ->
	Input ->
	Điền đường dẫn từng file
- Các file .dll:	
	Project properties -> 
	Debugging ->
	Environment ->
	Điền cú pháp: path=%path%;<thư mục file dll>

 nguyên tắc nói chung của ctr đồ họa, cụ thể GLUT:
 - Khởi tạo các tài nguyên
  + Tải các dữ liệu
  + Tạo các đối tượng để vẽ: cửa sổ, đối tượng dữ liệu...
 - Đăng ký các hàm callback
 - Khởi động vòng lặp chính:
hình dung vòng lặp chính:
 while (1) {
	xử lý các sự kiện: chuột, phím...	\
	cập nhật dữ liệu					| callback functions
	Hiển thị, phát âm thanh,..			/
 }
*/