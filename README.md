# Pac-Man
Bá Lương - UET  
20020001 - K65 C CLC

## Introductino
Bài tập lớn - Game (môn học: Lập trình Nâng cao - INT2215 6)

### Table of Contents
**[Started](#started)**  
**[References](#references)**  
**[Overview](#overview)**  
**[Ghost AI](#ghost-ai)**  
**[Demo Videos](#demo-videos)**  
**[Review](#review)**

## Started

### Ideas
Ý tưởng cho bài tập lớn là làm lại game Pacman (cổ điển) đồng thời thêm thắt những yếu tố sáng tạo cho game màu sắc riêng hơn.  
Phần Game cổ điển bao gồm:
- Pacman (nhân vật chính) có thể ăn các dot nhỏ để lấy điểm số và dot to để ăn lại các con ma.
- Ghost (bao gồm 4 nhân vật) là nhân vật sẽ đuổi Pacman -> nhằm không cho Pacman ăn các dot.
- Luật chơi rất đơn giản, bạn ăn nhiều số dot nhất có thể, cố gắng né tránh và sử dụng dot to để đối phó với các con ma. Khi bạn đẽ ăn hết số dot trên màn hình, bạn sẽ qua màn tiếp theo.

### Prepared
Để chuẩn bị cho bài tập lớn, em cần chuẩn bị những kiến thức sau:
- Kiến thức nền tảng: C++
- Kiến thức về OOP của C++ (chủ yếu là class)
- Kiến thức để sử dụng thư viện SDL2 (lazyfoo)
- Kiến thức về lập trình ứng dụng, cụ thể là game:
  - Cách tổ chức chương trình
  - Cách chia file
  - Cách quản lý các thành phần của game
- Tài nguyên của game:
  - Hình ảnh (texture -> png): Vẽ lại theo game gốc và thêm thắt sáng tạo
  - Âm thanh (wav): lấy từ game gốc và trên một số nguồn từ [freesound](http://freesound.org)
- Thời gian để thu thập những thứ trên

## References
Để chuẩn bị cho bài tập lớn em đã:
- Đoc tài liệu, slide và làm bài tập của cô Châu cùng thầy bài tập Linh để trau dồi kiến thức lâp trình nâng cao.
- Tham khảo về 1 chương trình SDL2 từ 1 series lập trình Game RPG với SDL2 của Youtuber: [Let's Make Games](https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g)  
  [Link tới danh sách phát](https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx)
- Tham khảo khung chương trình và cách tổ chức game từ 1 video làm game Pacman của Youtuber: [HexagonNico](https://www.youtube.com/watch?v=4AatUPAXrj8)  
  [Link tới Video](https://www.youtube.com/watch?v=4AatUPAXrj8)
- Để xây dựng và phát triển các con Ghost trong game, em đã tham khảo một video về Ai của game qua Youtube: [Pac-Man Ghost AI Explained](https://www.youtube.com/watch?v=ataGotQ7ir8)
- Một số tài liệu về OOP và Pointer trong C++ để hiểu rõ hơn.

## Overview

### Playing
Game gồm 8 level:
Mỗi level của game yêu cầu người chơi điều khiển Pacman di chuyển trên map để ăn toàn bộ các dot vàng. 
Khi toàn bộ số dot đã hết thì người chơi qua màn tiếp theo.
Sau level 2 thì các con ma sẽ tiến hóa thành con ma mới với nhiều khả năng đặc biệt:
- Blinky -> Deadly: giờ có thể làm Pacman mất 2 mạng khi cắn.
- Pinky -> Speedy: có thể tăng tốc nhưng khi đến gần Pacman sẽ đi chậm lại. Khi cắn Pacman sẽ khiến Pacman bị chậm lại.
- Inky -> Invisy: tàng hình trong 1.2s sau đó thoát ẩn, thoát hiện. Khi cắn Pacman sẽ khiến cho Pacman bị mù.
- Clyde -> Freezy: không có gì thay đổi trừ việc khi cắn Pacman sẽ khiến Pacman bị đóng băng.

### New Features
Những tính năng mới được thêm vào trong game:
- Dot lớn giờ được nâng cấp thành 4 dot riêng biệt:
  - Dot "P": là dot lớn ban đầu -> giúp Pacman có khả năng ăn được các con ma
  - Dot "S": là dot tốc độ -> giúp Pacman có siêu tốc độ
  - Dot "T": là dot đóng băng thời gian -> khiến cho các vật thể ngoài Pacman ngừng chuyển động
  - Dot "I": là dot tàng hình -> giúp Pacman tàng hình
- Pacman giờ có thêm 2 nhân vật:
  - Ms Pacman
  - Android Pacman
- Đã thêm tính năng chọn nhân vật Pacman (trong setting)
- Đã thêm tính năng Fruit bonus điểm cho trò chơi
- Đã random các Big dot trên màn chơi
- Đã thêm tính năng nhận biết power hiện tại của Pacman
- Đã thêm tính năng nhận biết effect xấu hiện tại của Pacman
- Đã thêm 4 Ghost mới (là bản nâng cấp của 4 Ghost cổ điển):
  - Deadly
  - Speedy
  - Invisy
  - Freezy
- Đã thêm Boss cuối của game: Golden (kết hợp bởi 4 ghost cũ):
  - Có khả năng thả dot nhỏ trên đường đi.
  - Có Ai né tránh khi Pacman tiến đến gần.
  - Khả năng tăng tốc khi bị Pacman rình.
  - Sau 3 lần tăng tốc, Golden sẽ mệt (Exhausted). -> Lúc đó Pacman có khả năng tấn công Golden
  - Golden có khả năng chịu đựng 5 lần tấn công từ Pacman.
  - Giết chết Golden bạn sẽ chiến thắng màn chơi!

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

## Presentation
1. Chơi thử demo
2. Trình bày sources nguồn

## Demo videos
[Link drive các video demo về game](https://drive.google.com/drive/folders/1wSHAdCgVVikGCHcD1pu0RlE2v475jzOv?usp=sharing)
Bao gồm 5 video:
- 2 video về màn chơi Boss
- 1 video về Menu và Setting của game
- 1 video về các lần Ghost được nâng cấp
- 1 video về demo gameplay của game từ level 1

## Review
Sau quãng thời gian dài làm bài tập lớn, em thấy mình tiến bộ hơn rất nhiều về cả kiến thức lẫn tư duy lập trình. Nếu có thêm thời gian e sẽ phát triển game trở nên hoàn thiện hơn ở một số điểm. Theo đánh giá cá nhân, em thấy mình xứng đáng với điểm 10 cho bài tập lớn này.
