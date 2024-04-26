# World's hardest game
- Game demo : 
- Game walkthrough (easy mode):
# Giới thiệu chung
**World's hardest game - Trò chơi khó nhất thế giới** là một trò chơi thuộc thể loại qua màn. Nhiệm vụ của bạn rất đơn giản : điều khiển khối vuông màu đỏ vượt qua các chướng ngại vật (các chấm màu xanh), đồng thời thu thập tất cả các đồng xu vàng cần thiết để qua màn. Game có tổng cộng 15 màn tất cả, với độ khó tăng dần đến mức bạn sẽ phải đập bàn phím sau khi chơi được một lúc.</br>

# 0. Cách tải game
## 0.1 Không bao gồm code

Tải game (được nén thành file zip) tại link : </br>
Giải nén game vào một thư mục, khởi động file **World's hardest game.exe** rồi tận hưởng game thôi nào !!!

## 0.2 Bao gồm code và có thể biên dịch

**Bước 1**: Clone repo này về (ở nhánh master 2)</br>
**Bước 2**: Tải IDE Visual Studio tại [đây](https://visualstudio.microsoft.com). Kéo xuống rồi chọn bản Community 2022 rồi tải về.</br>
**Bước 3**: Cài đặt thư viện `SDL2` tại [đây](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php). Áp dụng tương tự với các thư viện mở rộng như `SDL2_image`, `SDL2_ttf`,`SDL2_mixer`.</br>
**Bước 4**: Khởi động file **World's hardest game.sln**, sau đó chạy biên dịch và tận hưởng game thôi nào !!!

# 1. Bắt đầu game
Khi vào game, một intro game sẽ hiện ra trong vòng 5 giây</br>

Sau đó, giao diện game sẽ giống như sau:</br>

Khi bạn di chuyển chuột vào nút tương ứng, dòng chữ sẽ thay đổi từ màu trắng/đen thành màu đỏ đậm.
- Nếu bạn muốn bắt đầu chơi game , hãy bấm vào nút **PLAY GAME** .
- Nếu bạn muốn đọc hướng dẫn chơi và điều khiển game, hãy bấm vào nút **TUTORIAL**.
- Nếu bạn muốn thoát khỏi trò chơi, hãy bấm vào nút **EXIT GAME**.

# 2. Chọn chế độ
Có hai chế độ: chế độ Speedrun và chế độ Level Select.</br>

Ở chế độ Speedrun, bạn sẽ phải vượt qua tất cả các màn trong trò chơi với thời gian nhanh nhất có thể. Nếu bạn cần tập luyện từng màn để chơi Speedrun, bạn có thể chọn chế độ Level Select. Khi đó, giao diện chọn màn sẽ hiện lên.</br>
Lưu ý rằng, nếu bạn muốn quay trở lại giao diện menu chính, bạn có thể bấm vào nút **BACK TO PREVIOUS** hiện ở góc phải dưới của màn hình. 

- Để chọn chế độ Speedrun, hãy bấm vào nút **SPEEDRUN**.
- Để chọn chế độ Level Select, hãy bấm vào nút **LEVEL SELECT**.
# 3. Chọn màn
Nếu bạn chọn chế độ chọn màn, giao diện chọn màn sẽ hiện ra như sau:

Trò chơi sẽ bao gồm 15 màn tất cả, với độ khó tăng dần theo số màn hiện tại đến mức khó không thể tin nổi.</br>
Để chọn màn, di chuyển chuột đến ô màn tương ứng bạn muốn chọn. Sau đó chọn ô màn đó. Bạn cũng có thể chọn quay lại giao diện chọn chế độ bằng cách bấm vào nút **BACK TO PREVIOUS** hiện ở góc phải dưới của màn hình. 
# 4. Chọn độ khó
Có hai độ khó: dễ và khó.<br>

Ở chế độ dễ, các chướng ngại vật sẽ di chuyển chậm hơn, do đó sẽ dễ dàng qua màn hơn. Ở chế độ khó, tốc độ của chướng ngại vật sẽ tăng lên gấp đôi, khiến cho việc vượt qua các chướng ngại vật trở nên khó hơn.</br>
- Để chọn chế độ dễ, bấm vào nút **EASY**.
- Để chọn chế độ khó, bấm vào nút **HARD**.
- Nếu bạn muốn đổi chế độ chơi game hay muốn thay đổi màn chơi hiện tại (ở chế độ chọn màn), hãy bấm vào nút **BACK TO PREVIOUS** hiện ở góc phải dưới của màn hình. 
# 5. Các thành phần trong game
- Bố cục cơ bản của game sẽ như sau:

- Khối vuông màu đỏ (Red square): Là nhân vật chính mà người chơi sẽ di chuyển. 
- Chấm xanh (blue dots): Khi người chơi di chuyển vào chấm xanh, khối đỏ sẽ chết và di chuyển lại về khu vực checkpoint đã được lưu trước đó . Các chấm xanh có thể di chuyển theo chu kì hình chữ I, hình chữ L hay bất cứ chu kì nào bạn có thể tưởng tượng.
- Đồng xu (Coins): Là một vật phẩm quan trọng trong game. Để qua màn, bạn cần phải thu thập tất cả các đồng xu có trên bản đồ. Khi di chuyển vào một khu vực checkpoint nào đó, số đồng xu của bạn đã thu thập được sẽ được lưu lại. Lần sau khi chết, bạn sẽ không phải cất công đi nhặt lại những đồng xu kia nữa.
- Level : Bạn có thể xem số màn hiện tại của mình tại góc trên trái của màn hình game.
- Bộ đếm đồng xu (Coin counter) : Bạn có thể xem số đồng xu mình đã thu thập được ở phía giữa góc trên màn hình game.
- Bộ đếm số lần chết (Death counter): Bạn có thể xem số lần bạn đã chết ở góc trên trái của màn hình game. Số lượt chết sẽ cộng dồn qua từng màn (ở chế độ Speedrun).
- Bộ thời gian (Timer): Bạn có thể xem thời gian mình đã chơi bắt đầu từ lúc bắt đầu chơi tại phía giữa góc dưới màn hình game.
- Nút **BACK TO MAIN MENU**: Nếu cảm thấy chế độ chơi hiện tại quá khó, bạn có thể chọn quay lại giao diện menu chính của game bằng cách chọn nút trên tại góc phải dưới của màn hình game.
- Checkpoint : Có tác dụng lưu lại tiến trình game ở màn hiện tại khi bạn di chuyển khối vuông đỏ vào đây.

# 6. Hướng dẫn chơi game
Sử dụng 4 nút mũi tên &uarr;,&larr;, &rarr; và &darr; để điều khiển khối vuông màu đỏ di chuyển theo ý muốn của bạn. Bạn có thể kết hợp các nút với nhau để có thể di chuyển theo hướng tùy thích. Nhiệm vụ của bạn là vượt qua các chướng ngại vật (các chấm xanh), thu thập tất cả các đồng xu rồi di chuyển đến ô checkpoint cuối cùng để qua màn.</br>
Nếu bạn cảm thấy màn chơi hiện tại quá khó, bạn có thể bỏ cuộc, hoặc sử dụng **CHEAT CODE** bí mật mà tôi đã giấu trong game để có thể ngay lập tức qua màn.
#  7. Qua màn
Khi bạn qua một màn bất kì, bạn sẽ ngay lập tức được chuyển đến màn tiếp theo.</br>
Nếu màn hiện tại của bạn là màn cuối cùng của chế độ speedrun, giao diện của bạn sẽ hiện như sau:

Nếu bạn hoàn thành một màn bất kì trong chế độ Level Select, giao diện của bạn sẽ hiện như sau:

Sau đó, hãy chọn nút **BACK TO MAIN MENU** để quay lại giao diện menu chính của game ở góc phải dưới của màn hình game.
# 8. Về cơ chế hoạt động của game
- Trong file `Coin.cpp` và `Coin.hpp`:
    * cPosX: tọa độ theo chiều ngang của đồng xu.
    * cPosY: tọa độ theo chiều dọc của đồng xu.
    * cTexture: chứa Texture của đồng xu đó.
    * cAlpha: độ sáng của đồng xu.
    * cStatus: Trạng thái của đồng xu (0 nếu chưa bị thu thập, 1 nếu bị thu thập nhưng chưa được lưu, 2 nếu đã bị thu thập và đã được lưu ở checkpoint nào đó).
- Trong file `Movepath.cpp`:
- Trong file `Dot.cpp` và `Dot.hpp`:
- Trong file `HUD_Text.cpp` và `HUD_Text.hpp`:
- Trong file `HUD_Texture.cpp` và `HUD_Texture.hpp`:
- Trong file `Level.cpp` và `Level.hpp`:
- Trong file `Player.cpp` và `Player.hpp`:
- Trong file `UI.cpp` và `UI.hpp`:
- Trong file `main.cpp`:
# 9. Credits
- Thầy Lê Đức Trọng: vì đã giúp đỡ em rất nhiều trong khâu phát triển game.
- Trợ giảng thầy Trần Thủy: vì đã giúp đỡ em trong khâu thiết kế và đóng góp về game.
- Mentor Nguyễn Vũ Thanh Tùng: vì đã giúp đỡ em rất nhiều trong khâu sửa lỗi game, git, github repo.
- Lazyfoo SDL_2's tutorial : https://lazyfoo.net/tutorials/SDL/index.php.
- Resources, SFX and Music : https://github.com/danspage/worldshardestgame/tree/master?tab=readme-ov-file.
- Additional SFX: https://pixabay.com/vi/sound-effects/.
