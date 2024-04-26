# **CỜ CARO**
Họ và tên: Trương Văn Hải

Mã SV: 23020058
## Mục lục
## Kiến thức áp dụng để làm game
- Kiến thức về ngôn ngữ C++, thư viện đồ họa SDL2 qua slide LTNC, lazyfoo, Youtube.
- Kiến thức về lập trình hướng đối tượng qua Youtube, tra Google.
- Thuật toán Minimax, cắt tỉa Alpha, Beta.
## Giới thiệu về game
Cờ caro (Gomoku) là thể loại cờ đã gán liền với tuổi thơ của bao thế hệ, thường được các bạn nhỏ chơi trên các trang giấy ô ly. Game cờ caro dựa trên trò chơi này với giao diện thân thiện với người chơi và các chế độ hấp dẫn thử thách.
## Sơ lược luật chơi
- Với bàn cờ 3x3, người chơi chỉ có 10 giây suy nghĩ cho mỗi nước đi, người chơi sẽ thắng khi đánh được 3 ô liên tiếp.
- Với bàn cờ tiêu chuẩn 15x15, người chơi 45 giây suy nghĩ cho mỗi nước đi và sẽ thắng khi đánh được 5 ô liên tiếp.
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
## Về thuật toán cho máy
Sử dụng thuật toán minimax với cắt tỉa alpha, beta tìm hiểu trên Youtube và tra Google
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
  
  Hàm này duyệt cả bàn cờ, đến ô có X hay O sẽ xét 4 hướng và 5 ô liên tiếp, điểm là biến point sẽ được cộng vào điểm tổng val nếu là O(bot) hoặc bị trừ vào val nếu là X(người chơi) sau mỗi hướng.

  Có hai công thức tính cho 2 trường hợp liên tiếp (biến curR là số ô liên tiếp): liên tiếp chặn 1 đầu nhưng vẫn có khả năng tạo nước 5: pow(10, curR - 2) + 2 và liên tiếp không bị chặn: pow(10, curR - 1), có những trường hợp lợi thế vừa với công thức: pow(10, curR - 2) + 3, ngoài ra còn trường hợp curR = 1 cho điểm khi có xu hướng ở giữa bàn và xung quanh không bị chặn để nước đi đầu được chuẩn hơn.

  Với medium thì độ sâu là 0 tức là chỉ đánh thử 1 nước để đánh giá nên chặn yếu, lắm lúc chỉ biết công.

  
  Với hard thì độ sâu là 1, có thể công thủ, chặn và tạo nước đôi rất hay.
