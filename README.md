# Pac-Man
Bá Lương - UET  
20020001 - K65 C CLC

## Introductino
Bài tập lớn - Game (môn học: Lập trình Nâng cao - INT2215 6)

### Table of Contents
**[Started](#started)**  
**[Overview](#overview)**  
**[Ghost AI](#ghost-ai)**  

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

## Control
Người chơi sử dụng 4 phím trên bàn phím để di chuyển Pacman.  
Hiện tại có 3 tổ hợp phím được hỗ trợ trong game:
- Tổ hợp phím mũi tên
- WASD
- IJKL

Ngoài ra việc sử dụng Menu cũng dựa vào bàn phím:
- Tổ hợp phím mũi tên để di chuyển button
- Phím Enter để lựa chọn button
- Phím ESC để thoát ra khỏi cửa sổ State hiện tại

## Ghost AI

### Ghost
Ghost là sub class của class Entity (1 phần tử di chuyển được trong game).  
Class Ghost là cơ sở cơ bản cho những Ghost ma sau này.  
Về cơ bản thì Ghost kế thừa tất cả những gì Entity có:
- Các thông số di chuyển, tốc độ, vị trí hiện tại, . . .
- Có thêm các trạng thái của Ghost như (đuổi, sợ, đi tuần, chết, . . )

### Ghost AI
Ghost AI là 1 header chứa các hàm giúp cho các Ghost di chuyển.  
Về cơ bản Ghost AI sẽ tính toán hướng đi tiếp theo tối ưu nhất cho Ghost bằng thuật toán: 
```C++
///Calculate new Direction
DIRECTION calcDirection(Ghost* ghost, Labyrinth* labyrinth)
{
    Point newTile;
    int dis, minDis;
    minDis = (int)1e9;
    int newDirection = 0;

    for (int i = UP; i <= LEFT; i++)
    {
        if (checkOpposite(ghost->getCurDirection(), DIRECTION_AT[i]))
        {
            continue;
        }

        dis = (int)1e9;

        if (labyrinth->ghostCanMove(ghost->getTile(), DIRECTION_AT[i]))
        {
            newTile = ghost->getTile() + DIRECTION_VALUE[i];

            ///Euclidean distance
            //dis = DISTANCE::Euclidean(newTile, ghost->getTarget());

            ///Manhattan distance
            dis = DISTANCE::Manhattan(newTile, ghost->getTarget());
        }

        if (minDis > dis)
        {
            minDis = dis;
            newDirection = i;
        }
    }

    return DIRECTION_AT[newDirection];
}
```
calcDirection sẽ tính toán hướng đi tiếp theo của Ghost nếu nó di chuyển tới ngã ba/ ngã tư hoặc không đi tiếp với hướng hiện tại được.  
Công thức tính toán sẽ là mô phỏng nếu Ghost đi 4 hướng cơ bản thì hướng nào tối ưu nhất để giúp Ghost gần hơn tứi Target của nó.  

Thuật toán trả về hướng đi tối ưu nhất cho Ghost để di chuyển trong hàm di chuyển sau:
```C++
void handleGhostMove(Ghost* ghost, Labyrinth* labyrinth)
{
    if (ghost->getBehavior() == GHOST_STAND)
        return;

    if (labyrinth->isIntersection(ghost->getTile()) || ghost->getCurDirection() == UNSET_DIRECTION)
    {
        if (ghost->isStop())
        {
            ghost->setDirection(calcDirection(ghost, labyrinth));
            ghost->setStop(false);
        }
    }
    else
        ghost->setStop(true);

    if (labyrinth->ghostCanMove(ghost->getTile(), ghost->getCurDirection()))
        ghost->loop();
    else
        ghost->setStop(true);
    return;
}
```
Việc di chuyển của Ghost khá đơn giản: 
- Nếu Ghost đang trong trạng thái đứng yên -> ko đi
- Nếu Ghost đang ở ngã ba hoặc ngã tư hoặc nó đang ko biết đi thế nào (UNSET_DIRECTION) -> tính toán hướng đi mới cho Ghost (nếu Ghost dừng lại được (isStop()) ngược lại nó có thể dừng lại được (setStop(true))
- Nếu Ghost đi được với hướng hiện tại -> cho Ghost đi (ghost->loop())
- Nếu Ghost ko đi được -> cho Ghost dừng lại (setStop(true))

### Blinky

### Pinky

### Inky

### Clyde

## Presentation
1. Chơi thử demo
2. Trình bày sources nguồn
