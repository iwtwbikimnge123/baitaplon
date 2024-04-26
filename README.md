# **CỜ CARO**
Họ và tên: Trương Văn Hải

Mã SV: 23020058
## Mục lục
 - [Kiến thức áp dụng để làm game](#kienthuc)
 - [Giới thiệu về game](#gioithieu)
 - [Sơ lược luật chơi](#luatchoi)
 - [Cách chơi game](#cachchoi)
 - [Source code](#code)
 - [Về thuật toán cho Bot](#thuattoan)
 - [Về đồ họa](#dohoa)
   
   ============================================================
<a name="kienthuc"></a>
## Kiến thức áp dụng để làm game 
- Kiến thức về ngôn ngữ C++, thư viện đồ họa SDL2 qua slide LTNC, lazyfoo, Youtube.
- Kiến thức về lập trình hướng đối tượng qua Youtube, tra Google.
- Thuật toán Minimax, cắt tỉa Alpha, Beta.
<a name="gioithieu"></a>
## Giới thiệu về game 
Cờ caro (Gomoku) là thể loại cờ đã gán liền với tuổi thơ của bao thế hệ, thường được các bạn nhỏ chơi trên các trang giấy ô ly. Game cờ caro dựa trên trò chơi này với giao diện thân thiện với người chơi và các chế độ hấp dẫn thử thách.
<a name="luatchoi"></a>
## Sơ lược luật chơi 
- Với bàn cờ 3x3, người chơi chỉ có 10 giây suy nghĩ cho mỗi nước đi, người chơi sẽ thắng khi đánh được 3 ô liên tiếp.
- Với bàn cờ tiêu chuẩn 15x15, người chơi 45 giây suy nghĩ cho mỗi nước đi và sẽ thắng khi đánh được 5 ô liên tiếp.
<a name="cachchoi"></a>
## Cách chơi game 
### 1. Menu bắt đầu
![anh](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163134.png)
- Người chơi nhấn chuột chọn chế độ hoặc để tắt âm thanh.
- Nhấn Start để bắt đầu.
### 2. Các chế độ chơi
- Khi bắt đầu chế độ nào cũng sẽ nhận được thông báo:

  ![anh](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163156.png)

  Người chơi phải nhấn chuột vào bất cứ đâu trên màn hình để vào chơi hay thực hiện các thao tác khác.
- Bàn cờ của các chế độ đều có các nút home và nút speaker.
- Khi nhấn nút home, một thông báo yes, no hiện ra. Nhấn yes, người chơi sẽ quay về menu bắt đầu và dữ liệu về tỉ số sẽ bị xóa, nhấn no sẽ tiếp tục chơi.
- Chế độ 2 người chơi:

  ![img](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163401.png)

  Hai người chơi lần lượt đi nước của mình trong thời gian suy nghĩ.

- Chế độ chơi với máy:

  ![img](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163216.png)
  ![img](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163310.png)

  Người chơi có thể nhấn chuột chọn các level (medium, hard) phù hợp với mình để luyện tập, nâng cao kĩ năng.
  
  Khi nhấn chuột chuyển level, một thông báo yes, no hiện ra. Nhấn yes, người chơi sẽ chuyển level và dữ liệu về tỉ số sẽ bị xóa, nhấn no sẽ tiếp tục chơi.
### 3. Menu kết thúc
- Khi hết thời gian suy nghĩ hay bị đánh số ô liên tiếp trước, ván đấu sẽ kết thúc, khi đó menu kết thúc hiện ra:
  ![img](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163322.png)
- Trong menu kết thúc sẽ có các nút continue (tiếp tục một ván đấu mới và tỉ số sẽ được cập nhật), return (quay trở lại menu bắt đầu) và nút replay.
### 4. Chế độ Replay
- Chế độ replay sẽ được kích hoạt khi ấn nút replay trong menu kết thúc, giúp người chơi xem lại ván đấu, từ đó nhận ra các nước đi chưa tốt hay những nước đi hay từ đó rút ra kinh nghiệm:
  
  ![img](https://github.com/iwtwbikimnge123/baitaplon/blob/main/tictactoe/img/Screenshot%202024-04-26%20163339.png)

  Người chơi nhấn chuột vào các biểu tượng để xem các nước đi tiếp, hay quay lại các nước đi trước đó.

  Khi xem xong, người chơi có thể nhấn chuột vào nút replay để quay lại menu kết thúc.
<a name="code"></a>
## Source code 
- Common:
  * Các biến toàn cục, kiểu enum.
  * bool Init(), void Close(): các hàm khởi tạo và đóng.
  * void RenderImage(std::string path, SDL_Rect rect): hàm render ảnh vào tọa độ rect trong màn hình.
  * bool CheckClick(SDL_Rect rect, int x, int y): check xem tọa độ có trong rect không (để check xem có click hay mousemotion có trong nút không).
- Text:
  * Các hàm:
        void SetText(const std::string& t);

	void SetColor(const SDL_Color& c);

	bool OpenFont(int fonsize, std::string path);

	void RenderText(int x, int y);

	SDL_Rect* GetRect() { return rect; }

có chức năng đúng như tên gọi của nó và 2 hàm khởi tạo và hủy.
- SwitchButton:
  * Các hàm:
        Button();
	~Button();

	void SetButtonType(const ButtonType& type);

	void SetPath();

	void SetRect(const int& x, const int& y, const int& w, const int& h);

	SDL_Rect GetRect();

	void RenderButton();

cũng có chức năng đúng như tên gọi của nó.
- StartMenu:
  * MenuStart(): hàm khởi tạo các nút, render màn hình.
  * void RenderBaseMenu(): render menu cơ bản.
  * void HandleEvent(SDL_Event& e, bool& quit): handleevent, hiệu ứng switch.
  * void RestartMenu(): Set lại các trạn thái ban đầu của menu.
- Game:
  * Game(): Khởi tạo các nút và bảng.
  * void DrawGrid(): vẽ bảng theo màu.
  * void SetN(const int& n): gán giá trị cho N (3 hoặc 15) và CELL_WIDTH, CELL_HEIGHT.
  * void SetTimeForEachMove(const int& n): 45s hoặc 10s.
  * void InitBoard(): reset lại bảng, trạng thái, timer,...
  * void ChangeTurn(): đổi lượt.
  * virtual void logic(SDL_Event& e, bool& quit): xử lý logic của game.
  * virtual void Click(): check click để xem đánh đúng không và cập nhật bảng.
  * virtual bool CheckWinRow(), virtual bool CheckWinCol(), virtual bool CheckWinDiag2(), virtual bool CheckWinDiag1():
    + Với 15x15: check xem tại xung quanh nước đi vừa đánh có 5 ô liên tiếp không theo các hướng.
    + Với 3x3: đơn giản là check xem có 3 ô liên tiếp không.
  * bool CheckTie(): xem bàn cờ full chưa, rồi thì là hòa.
  * void RenderRunningstate(): Render bảng hiện tại và các nút.
  * void DrawXCell(const int& i, const int& j), void DrawOCell(const int& i, const int& j): Render ô X, O với tọa độ i, j.
  * virtual void RenderEndStage(): Render trạng thái kết thúc.
  * virtual void RenderEndMenu(): Render menu kết thúc.
  * void CheckClickWinMenu(SDL_Event& e, bool& quit): handleevent cho menu kết thúc.
  * virtual void HandleEvent(SDL_Event& e, bool& quit): handleevent khi đang chơi.
- Game3x3:
   Kế thừa từ Game, định nghĩa lại các hàm checkwin, void RenderEndStage().
- Game3x3bot:
   * Kế thừa từ Game3x3, định nghĩa lại các hàm void logic(SDL_Event& e, bool& quit), void Click(), void HandleEvent(SDL_Event& e, bool& quit), void RenderRunningstate(), void RenderEndStage(), void RenderEndMenu().
   * Các hàm: int minimax(int depth_, bool isBotTurn, int alpha, int beta), virtual int value(bool isBotTurn): giải thích dưới.
   * void SetDepthMedium(const int& n), void SetDepthHard(const int& n): Set độ sâu cho các chế độ.
- Game15x15bot:
   * Kế thừa từ Game3x3bot: dùng các hàm checkwin của Game, định nghĩa lại void RenderEndStage();
   * bool checkinside(int i, int j): check xem tọa độ ô có trong bảng không.
   * int value(bool isBotTurn): giải thích bên dưới.
- PlayGame:
  * Các hàm void PlayGame(const int& n, SDL_Event& e, bool& quit), void PlayGameBot(const int& n, SDL_Event& e, bool& quit): Thực hiện các thao tác Set các thứ và chơi game.
<a name="thuattoan"></a>
## Về thuật toán cho Bot 
Sử dụng thuật toán minimax với cắt tỉa alpha, beta tìm hiểu trên Youtube và tra Google.
### Thuật toán Minimax
Là một thuật toán đệ quy áp dụng cho các loại cờ đánh theo lượt như cờ vua, cờ tướng, cờ caro, cờ vây,... nhằm tìm kiếm nước tốt nhất tiếp theo dựa trên giả sử rằng đối thủ cũng đi nước tốt nhất.
### Cắt tỉa Alpha, Beta
Nhằm loại bỏ các nhánh trong cây trò chơi mà kết quả xấu không cần thiết xét thêm.
### Hàm đánh giá
- Do là một thuật toán dạng đệ quy, quay lui nên độ phức tạp rất lớn để xét hết các trường hợp đến tận trạng thái kết thúc game thì máy sẽ bị đơ (trừ trường hợp với những game đơn giản như caro 3x3), do đó cần có một độ sâu để giới hạn, khi độ sâu bằng 0, hàm minimax sẽ trả về value()- hàm đánh giá trạng thái hiện tại của bàn cờ.
- Hàm đánh giá là rất quan trọng, có thể cho ta biết được độ mạnh của một con bot.
- Code hàm đánh giá 3x3:

  int Game3x3bot::value(bool isBotTurn) {
	if (CheckWinCol() || CheckWinRow() || CheckWinDiag1() || CheckWinDiag2()) {
		if (isBotTurn) return INT_MIN;
		else return INT_MAX;
	}
	else return 0;
}

Hàm đánh giá cho 3x3 rất đơn giản, nếu là trạng thái kết thúc mà đến lượt bot (sau khi người đánh đổi lượt luôn sang bot rồi mới gọi đệ quy nên checkwin mà true thì tức là người thắng, ngược lại tương tự) thì return INT_MIN, không phải thì return INT_MAX, còn nếu không phải trạng thái kết thúc thì trả về không.

Với 3x3 chế độ medium thì độ sâu là 1, chế độ hard thì độ sâu -1 (để hàm minimax chạy hết đến trạng thái kết thúc vì 3x3 rất đơn giản).
- Code hàm đánh giá 15x15:

  
const int di[4] = { 1, 1, 1, 0 };
const int dj[4] = { -1, 0, 1, 1 };

  int Game15x15bot::value(bool isBotTurn) {
	
	int val = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == PLAYER_X) {
				for (int k = 0; k < 4; k++) {
					int curR = 1;
					int point = 0;
					bool block = false;
					for (int m = 1; m < 5; m++) {
						//bi chan

						if (!checkinside(i + di[k] * m, j + dj[k] * m) ||
							board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) {

							block = true;

							if (!checkinside(i - di[k], j - dj[k]) ||
								board[i - di[k]][j - dj[k]] == PLAYER_O ||
								curR == 1) {
								point = 0;
							}
							else if (board[i + di[k] * (m - 1)][j + dj[k] * (m - 1)] == PLAYER_X) {
								if (curR == 2) point = 0;
								
								//__|XXXO_|
								else /*if (curR == 4 || (curR == 3 &&
									checkinside(i - di[k] * 2, j - dj[k] * 2) &&
									board[i - di[k] * 2][j - dj[k] * 2] == EMPTY))*/ point = pow(10, curR - 2) + 2;
							}
							else if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
								board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) {
								point = pow(10, curR - 1);
							}
							else point = pow(10, curR - 2) + 2;

							break;
						}	
						//o X

						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) curR++;
					}

					if (!block) {

						if (curR == 1) {
							if (checkinside(i - 5 * di[k], j - 5 * dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY &&
								board[i - 2 * di[k]][j - 2 * dj[k]] == EMPTY &&
								board[i - 3 * di[k]][j - 3 * dj[k]] == EMPTY && 
								board[i - 4 * di[k]][j - 4 * dj[k]] == EMPTY &&
								board[i - 5 * di[k]][j - 5 * dj[k]] == EMPTY ) point = 1;
							else point = 0;
						}
						else if (curR == 2) {
							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == PLAYER_X) point = 0;
								else point = pow(10, curR - 1);
							}
							else point = 0;
						}
						else if (curR == 5) point = 100000000;
						//_|_____|O


						else if (!checkinside(i + di[k] * 5, j + dj[k] * 5) ||
							board[i + di[k] * 5][j + dj[k] * 5] == PLAYER_O) {
							//_|_____|O
							if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) {
								// O|XXX__|O
								if (!checkinside(i - di[k], j - dj[k]) ||
									board[i - di[k]][j - dj[k]] == PLAYER_O) point = pow(10, curR - 2) + 2;
								//  _|X_XX_|O
								else point = pow(10, curR - 1);

							}
							//_|X___X|O
							else  point = pow(10, curR - 2) + 2;

						}

						//_____|_
						else if (board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {

							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == EMPTY) point = pow(10, curR - 1);
								else point = pow(10, curR - 2) + 3;
							}
							else point = pow(10, curR - 2) + 2;

						}
					}
					val -= point;
				}
			}
			else if (board[i][j] == PLAYER_O) {
				for (int k = 0; k < 4; k++) {
					int curR = 1;
					int point = 0;
					bool block = false;
					for (int m = 1; m < 5; m++) {
						//bi chan

						if (!checkinside(i + di[k] * m, j + dj[k] * m) ||
							board[i + di[k] * m][j + dj[k] * m] == PLAYER_X) {

							block = true;

							if (!checkinside(i - di[k], j - dj[k]) ||
								board[i - di[k]][j - dj[k]] == PLAYER_X ||
								curR == 1) {
								point = 0;
							}
							else if (board[i + di[k] * (m - 1)][j + dj[k] * (m - 1)] == PLAYER_O) {
								if (curR == 2) point = 0;
								else /*if (curR == 4 || (curR == 3 &&
									checkinside(i - di[k] * 2, j - dj[k] * 2) &&
									board[i - di[k] * 2][j - dj[k] * 2] == EMPTY))*/ point = pow(10, curR - 2) + 2;
							}
							else if (checkinside(i - di[k] * 2, j - dj[k] * 2) &&
								board[i - di[k] * 2][j - dj[k] * 2] == EMPTY) {
								point = pow(10, curR - 1);
							}
							else point = pow(10, curR - 2) + 2;

							break;
						}
						//o X

						else if (board[i + di[k] * m][j + dj[k] * m] == PLAYER_O) curR++;
					}

					if (!block) {

						if (curR == 1) {
							if (checkinside(i - 5 * di[k], j - 5 * dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY &&
								board[i - 2 * di[k]][j - 2 * dj[k]] == EMPTY &&
								board[i - 3 * di[k]][j - 3 * dj[k]] == EMPTY &&
								board[i - 4 * di[k]][j - 4 * dj[k]] == EMPTY &&
								board[i - 5 * di[k]][j - 5 * dj[k]] == EMPTY) point = 1;
							else point = 0;
						}
						else if (curR == 2) {
							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == PLAYER_X) point = 0;
								else point = pow(10, curR - 1);
							}
							else point = 0;
						}
						else if (curR == 5) point = 100000000;
						//_|_____|O


						else if (!checkinside(i + di[k] * 5, j + dj[k] * 5) ||
							board[i + di[k] * 5][j + dj[k] * 5] == PLAYER_X) {
							//_|_____|O
							if (board[i + di[k] * 4][j + dj[k] * 4] == EMPTY) {
								//O|XXX__|O
								if (!checkinside(i - di[k], j - dj[k]) ||
									board[i - di[k]][j - dj[k]] == PLAYER_X) point = pow(10, curR - 2) + 2;
								//_|X_XX_|O
								else point = pow(10, curR - 1);

							}
							//_|X___X|O
							else  point = pow(10, curR - 2) + 2;

						}

						//_____|_
						else if (board[i + di[k] * 5][j + dj[k] * 5] == EMPTY) {

							if (checkinside(i - di[k], j - dj[k]) &&
								board[i - di[k]][j - dj[k]] == EMPTY) {
								if (board[i + 4 * di[k]][j + 4 * dj[k]] == EMPTY) point = pow(10, curR - 1);
								else point = pow(10, curR - 2) + 3;
							}
							else point = pow(10, curR - 2) + 2;

						}
					}
					val += point;
				}
			}
		}
	}
	return val;
}
  
  Hàm này duyệt cả bàn cờ, đến ô có X hay O sẽ xét 4 hướng (không xét 4 hướng kia vì nó đã được xét ở những ô khác EMPTY trước) và 5 ô liên tiếp, điểm là biến point sẽ được cộng vào điểm tổng val nếu là O(bot) hoặc bị trừ vào val nếu là X(người chơi) sau mỗi hướng.

  Có hai công thức tính cho 2 trường hợp liên tiếp (biến curR là số ô liên tiếp): liên tiếp chặn 1 đầu nhưng vẫn có khả năng tạo nước 5: pow(10, curR - 2) + 2 và liên tiếp không bị chặn: pow(10, curR - 1), có những trường hợp lợi thế vừa với công thức: pow(10, curR - 2) + 3, ngoài ra còn trường hợp curR = 1 cho điểm khi có xu hướng ở giữa bàn và xung quanh không bị chặn để nước đi đầu được chuẩn hơn, và curR = 5 thì cho 100000000 cho nó to.

  Với medium thì độ sâu là 0 tức là chỉ đánh thử 1 nước để đánh giá nên chặn yếu, lắm lúc chỉ biết công.

  Với hard thì độ sâu là 1, có thể công thủ, chặn và tạo nước đôi rất hay.
  <a name="dohoa"></a>
  ## Về đồ họa 
  Các nút và hình nền đều là tự thiết kế bằng phần mềm Canva.
