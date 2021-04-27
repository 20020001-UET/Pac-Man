# Pac-Man
Bá Lương - UET  
20020001 - K65 C CLC

## Introductino
Bài tập lớn - Game (môn học: Lập trình Nâng cao - INT2215 6)

### Table of Contents
**[Started](#started)**
**[Overview](#overview)**

## Started

### Ideas
Ý tưởng cho bài tập lớn là làm lại game Pacman (cổ điển) đồng thời thêm thắt những yếu tố sáng tạo cho game màu sắc riêng hơn.  
Phần Game cổ điển bao gồm:
- Pacman (nhân vật chính) có thể ăn các dot nhỏ để lấy điểm số và dot to để ăn lại các con ma.
- Ghost (bao gồm 4 nhân vật) là nhân vật sẽ đuổi Pacman -> nhằm không cho Pacman ăn các dot.
- Luật chơi rất đơn giản, bạn ăn nhiều số dot nhất có thể, cố gắng né tránh và sử dụng dot to để đối phó với các con ma. Khi bạn đẽ ăn hết số dot trên màn hình, bạn sẽ qua màn tiếp theo.

### Requirements
Yêu cầu cho bài tập lớn là:
- Sử dụng ngôn ngữ C++
- Sử dụng thư viện đồ họa SDL2 
- Game có đồ họa 2D và âm thanh
- Game có ai cho quái

### Prepared
Để chuẩn bị cho bài tập lớn, mình cần chuẩn bị những kiến thức sau:
- Kiến thức nền tảng: C++
- Kiến thức về OOP của C++ (chủ yếu là class)
- Kiến thức để sử dụng thư viện SDL2 (lazyfoo)
- Kiến thức về lập trình ứng dụng, cụ thể là game:
  - Cách tổ chức chương trình
  - Cách chia file
  - Cách quản lý các thành phần của game
- Tài nguyên của game:
  - Hình ảnh (texture -> png): Vẽ lại theo game gốc và thêm thắt sáng tạo
  - Âm thanh (wav): lấy từ game gốc
- Thời gian để thu thập những thứ trên

## Overview

### Coding map
Sơ dồ tổ chức project:

### New Features
Những tính năng mới được thêm vào trong game:
- Dot lớn giờ được nâng cấp thành 4 dot riêng biệt:
  - Dot "P": là dot lớn ban đầu -> giúp Pacman có khả năng ăn được các con ma
  - Dot "S": là dot tốc độ -> giúp Pacman có siêu tốc độ
  - Dot "T": là dot đóng băng thời gian -> khiến cho các vật thể ngoài Pacman ngừng chuyển động
  - Dot "I": là dot tàng hình -> giúp Pacman tàng hình
-  Pacman giờ có thêm 2 nhân vật:
  -  Ms Pacman
  -  Android Pacman

Những tính năng đang trong kế hoạch thêm vào game:
- 1 Ghost mới tên là Golden là boss chính (kết hợp bởi 4 ghost cũ) có khả năng thả dot nhỏ trên đường đi và khả năng teleport nếu bị bắt. Khi Golden bị bắt đủ 3 lần nó sẽ chuyển sang trạng thái sợ hãi (frightened) và bạn sẽ được phép tấn công Golden. Golden có tổng cộng 3 mạng. 
- Random các Dot trên màn chơi
- Thêm tính năng Fruit bonus điểm cho trò chơi

