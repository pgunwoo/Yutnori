#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

#define MAX 13 // 보드 크기
#define PLAYERS 4 // 최대 플레이어 4명
#define PIECES 2 // 플레이어 당 말 2개

// 플레이어의 말 위치 정보 구조체
typedef struct {
	int row, col; // 말의 현재 위치 (행, 열)
	int isActive; // 0이면 비활성화, 1이면 활성화, 2이면 통과, 3이면 같은 팀 말끼리 겹침
}info;

info playersHorse[PLAYERS][PIECES]; // 각 플레이어의 말 위치 정보

// 윷놀이 판 전역 변수 선언
char board[MAX][MAX] = {
		{'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o'},
		{'|', '\\', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '/', '|'},
		{'o', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', 'o'},
		{'|', ' ', ' ', '\\', ' ', ' ', ' ', ' ', ' ', '/', ' ', ' ', '|'},
		{'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o'},
		{'|', ' ', ' ', ' ', ' ', '\\', ' ', '/', ' ', ' ', ' ', ' ', '|'},
		{'o', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', 'o'},
		{'|', ' ', ' ', ' ', ' ', '/', ' ', '\\', ' ', ' ', ' ', ' ', '|'},
		{'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o'},
		{'|', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', '\\', ' ', ' ', '|'},
		{'o', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', 'o'},
		{'|', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\\', '|'},
		{'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o'}
};
// 초기 상태의 윷놀이 판을 유지하기 위해 선언
const char reset_board[MAX][MAX] = {
		{'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o'},
		{'|', '\\', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '/', '|'},
		{'o', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', 'o'},
		{'|', ' ', ' ', '\\', ' ', ' ', ' ', ' ', ' ', '/', ' ', ' ', '|'},
		{'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o'},
		{'|', ' ', ' ', ' ', ' ', '\\', ' ', '/', ' ', ' ', ' ', ' ', '|'},
		{'o', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', 'o'},
		{'|', ' ', ' ', ' ', ' ', '/', ' ', '\\', ' ', ' ', ' ', ' ', '|'},
		{'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'o'},
		{'|', ' ', ' ', '/', ' ', ' ', ' ', ' ', ' ', '\\', ' ', ' ', '|'},
		{'o', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', 'o'},
		{'|', '/', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\\', '|'},
		{'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o', '-', 'o'}
};

// 말을 이동하는 함수
void moveHoerse(int throwYut, int player, int choiceHorse, int playerTurn);
// 윷을 던지는 함수
int throw();
// 말판을 출력하는 함수
void printBoard();
// 말 위치를 초기화하는 함수
void horseReset(int player);
// 윷놀이 게임 시작함수
void gameStart(int player);
// 던진 윷 출력함수
void throwPrint(int throwYut);
// 도착 조건 확인 함수
void checkArr(int player);
// 상대편 말을 잡았는지 확인하는 함수
void catchHorse(int choiceHorse, int player, int playerTurn);
// 이벤트 칸 함수
void event(int playerTurn, int choiceHorse, int player);
// 위치 변환 이벤트 함수
void eventSwap(int playerTurn, int choiceHorse, int player);

int main(void)
{
	int player;
	printf("플레이어 수를 선택하시오(최대 4명) : ");
	scanf("%d", &player);
	// 플레이어 수가 올바른지 확인
	if (player < 2 || player > 4) {
		printf("다시 플레이어 수를 선택하시오(최소 2명, 최대 4명) : ");
		scanf("%d", &player);
	}
	// 게임을 시작하는 함수 호출
	gameStart(player);
	return 0;
}
// 도착 조건 확인 함수
void checkArr(int player)
{
	// 말이 도착했는지 확인 및 출력
	for (int i = 0; i < player; i++) {
		printf("플레이어 %d의 상태: ", i + 1);
		for (int j = 0; j < PIECES; j++) {
			if (playersHorse[i][j].isActive == 2) {
				printf("말 %d [도착] ", j + 1);
			}
			else if (playersHorse[i][j].isActive == 1) {
				printf("말 %d [진행 중] ", j + 1);
			}
			else if (playersHorse[i][j].isActive == 0) {
				printf("말 %d [대기 중] ", j + 1);
			}
			else {
				printf("말 %d [겹쳐짐] ", j + 1);
			}
		}
		printf("\n");
		printf("\n");
	}
	printf("\n");
	printf("\n");
	// 말이 다 도착했는지 확인
	for (int i = 0; i < player; i++) {
		int cleared = 1;
		// 한 개라도 도착하지 않았다면 다른 플레이어의 말을 확인
		for (int j = 0; j < PIECES; j++) {
			if (playersHorse[i][j].isActive != 2) {
				cleared = 0;
				break;
			}
		}
		// 모두 도착했을 경우
		if (cleared) {
			printf("\n플레이어 %d가 모든 말을 도착시켰습니다! 승리!\n", i + 1);
			exit(0); // 게임 종료
		}
	}
}
// 이벤트 칸에 도착했을 경우 함수 정의
void event(int playerTurn, int choiceHorse, int player)
{
	info* horse = &playersHorse[playerTurn][choiceHorse];

	srand(time(NULL)); // 랜덤 함수 선언
	int n = rand() % 4; // 0 ~ 3 사이의 수를 골라 반환

	// 모든 말이 죽음
	if (n == 0) {
		printf("모든 말이 죽습니다.\n\n");
		// 플레이어의 말 초기화
		for (int i = 0; i < player; i++) {
			for (int j = 0; j < PIECES; j++) {
				// 도착한 말은 초기화하지 않음
				if (playersHorse[i][j].isActive != 2) {
					playersHorse[i][j].row = -1;
					playersHorse[i][j].col = -1;
					playersHorse[i][j].isActive = 0; // 비활성화로 설정
				}
			}
		}
		// 보드 초기화
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				board[i][j] = reset_board[i][j];
			}
		}
		
		// 초기화된 상태를 화면에 출력
		printBoard();
		Sleep(2000); // 2초 대기
		system("cls");

		return;
	}
	// 상대 말과 위치 바꾸기
	else if (n == 1) {
		eventSwap(playerTurn, choiceHorse, player);
	}
	// 원하는 상대 말 전부 죽이기
	else if (n == 2) {
		printf("원하는 상대의 말을 모두 죽입니다.\n\n");
		int killPlayer;

		// 원하는 플레이어 선택
		printf("원하는 플레이어를 선택하시오 : ");
		scanf("%d", &killPlayer);

		// 잘못 입력했을 경우 다시 입력받음
		while (killPlayer < 1 || killPlayer > player || killPlayer - 1 == playerTurn) {
			printf("잘못된 플레이어 번호입니다. (1 ~ %d 사이여야 합니다.) 다시 입력: ", player - 1);
			scanf("%d", &killPlayer);
		}

		// 원래 있던 자리 리셋
		for (int i = 0; i < PIECES; i++) {
			if (playersHorse[killPlayer - 1][i].isActive == 1) {
				board[playersHorse[killPlayer - 1][i].row][playersHorse[killPlayer - 1][i].col] = 'o';
				playersHorse[killPlayer - 1][i].row = -1;
				playersHorse[killPlayer - 1][i].col = -1;
				playersHorse[killPlayer - 1][i].isActive = 0;
			}
		}
		printf("%d번째 플레이어의 모든 말을 비활성화했습니다.\n", killPlayer - 1);

		// 말판을 출력하는 함수 호출
		printBoard();
		Sleep(500);
		system("cls");
	}
	// 윷 한 번 더 던지고 이동
	else if (n == 3) {
		printf("윷을 한 번 더 던집니다.\n");
		
		// 윷을 던질 건지 확인
		printf("윷을 던지겠습니다.\n");
		Sleep(1000); // 1초 딜레이 후 윷을 던짐
		int yut = throw();

		// 윷을 던지는 함수 호출 후 무엇을 뽑았는지 출력
		throwPrint(yut);

		// 어떤 말을 움직일 건지 확인
		printf("몇 번째 말을 움직일 것인지 선택하세요(1~2번 중 선택) : ");
		scanf("%d", &choiceHorse);

		// 말을 잘못 입력했을 경우 다시 입력받음
		while (choiceHorse < 1 || choiceHorse > 2 || playersHorse[playerTurn][choiceHorse - 1].isActive == 2) {
			printf("다시 입력하세요 : ");
			scanf("%d", &choiceHorse);
		}

		// 말 움직이기
		moveHoerse(yut, player, choiceHorse - 1, playerTurn);
		Sleep(500);
		system("cls");

		// 말판을 출력하는 함수 호출
		printBoard();

		// 같은 말이 합쳐졌는지 확인
		if ((playersHorse[playerTurn][0].row == playersHorse[playerTurn][1].row) && (playersHorse[playerTurn][0].col == playersHorse[playerTurn][1].col)) {
			for (int j = 0; j < PIECES; j++) {
				playersHorse[playerTurn][j].isActive = 3;
			}
		}

		// 다른 말을 잡았는지 확인
		catchHorse(choiceHorse - 1, player, playerTurn);

		// 이벤트 칸에 도착했는지 확인하기 이벤트 칸은 양쪽 모서리칸과 중앙 칸
		if ((playersHorse[playerTurn][choiceHorse].row == 0 && playersHorse[playerTurn][choiceHorse].col == 12) &&
			(playersHorse[playerTurn][choiceHorse].row == 0 && playersHorse[playerTurn][choiceHorse].col == 0) &&
			(playersHorse[playerTurn][choiceHorse].row == 6 && playersHorse[playerTurn][choiceHorse].col == 6) &&
			(playersHorse[playerTurn][choiceHorse].row == 12 && playersHorse[playerTurn][choiceHorse].col == 0)) {
			// 이벤트 발생
			printf("이벤트 칸의 도착했습니다!!\n\n");
			event(playerTurn, choiceHorse, player);
		}

		// 도착했는지 확인
		checkArr(player);
	}
	else {
		printf("꽝!\n");
		return;
	}
}
// 위치 변환 이벤트 함수
void eventSwap(int playerTurn, int choiceHorse, int player)
{
	info* currentHorse = &playersHorse[playerTurn][choiceHorse]; // 현재 말의 정보

	// 현재 말이 활성화 상태가 아닌 경우
	if (currentHorse->isActive != 1) {
		printf("현재 선택된 말이 활성화되어 있지 않습니다. 위치를 교환할 수 없습니다.\n");
		return;
	}

	int targetPlayer;
	int targetHorse;
	int valid = 0; // 유효한 입력 여부

	// 유효한 상대 플레이어 입력받기
	do {
		printf("위치를 교환할 상대 플레이어를 선택하세요 (1 ~ %d): ", player);
		scanf("%d", &targetPlayer);

		// 플레이어 번호 확인
		if (targetPlayer < 1 || targetPlayer > PLAYERS || targetPlayer - 1 == playerTurn) {
			printf("잘못된 플레이어 번호입니다. 다시 입력하세요.\n");
		}
		else {
			valid = 1;
		}
	} while (!valid);

	// 유효한 상대 말 입력받기
	valid = 0;
	do {
		printf("상대 플레이어의 말을 선택하세요 (1 ~ %d): ", PIECES);
		scanf("%d", &targetHorse);

		// 말 번호 확인
		if (targetHorse < 1 || targetHorse > PIECES) {
			printf("잘못된 말 번호입니다. 다시 입력하세요.\n");
		}
		else {
			valid = 1;
		}
	} while (!valid);

	// 상대 말의 정보를 가져옴
	info* opponentHorse = &playersHorse[targetPlayer - 1][targetHorse - 1];

	// 상대 말이 활성화 상태가 아닌 경우
	if (opponentHorse->isActive != 1) {
		printf("선택한 상대 플레이어의 말이 활성화되어 있지 않습니다. 위치를 교환할 수 없습니다.\n");
		return;
	}

	// 현재 말과 상대 말의 위치 교환
	int tempRow = currentHorse->row;
	int tempCol = currentHorse->col;
	currentHorse->row = opponentHorse->row;
	currentHorse->col = opponentHorse->col;
	opponentHorse->row = tempRow;
	opponentHorse->col = tempCol;

	printf("플레이어 %d의 %d번째 말과 플레이어 %d의 %d번째 말이 위치를 교환했습니다!\n",
		playerTurn + 1, choiceHorse + 1, targetPlayer, targetHorse);

	// 보드 상태 갱신
	char playerChar = 'A' + playerTurn;
	char targetChar = 'A' + (targetPlayer - 1);
	board[currentHorse->row][currentHorse->col] = playerChar;
	board[opponentHorse->row][opponentHorse->col] = targetChar;

	// 이전 위치 초기화
	board[tempRow][tempCol] = 'o';
	board[currentHorse->row][currentHorse->col] = playerChar;
}
// 던진 윷을 출력하는 함수 정의
void throwPrint(int throwYut)
{
	const char* results[] = { "도", "개", "걸", "윷", "모" };
	printf("던진 결과: %s\n", results[throwYut - 1]);
}
// 윷을 던지는 함수 정의
int throw()
{
	srand(time(NULL)); // 랜덤 함수 선언
	int n = rand() % 5 + 1; // 1 ~ 5사이의 수를 골라 반환
	return n;
}
// 게임판을 출력하는 함수 정의
void printBoard()
{
	printf("\n");
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
// 말의 위치를 초기화 하는 함수 정의
void horseReset(int player)
{
	// 플레이어의 말 초기화
	for (int i = 0; i < player; i++) {
		for (int j = 0; j < PIECES; j++) {
			playersHorse[i][j].row = -1;
			playersHorse[i][j].col = -1;
			playersHorse[i][j].isActive = 0;
		}
	}
	// 보드 초기화
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			board[i][j] = reset_board[i][j];
		}
	}
}
// 말을 이동하는 함수 정의
void moveHoerse(int throwYut, int player, int choiceHorse, int playerTurn)
{
	// 처음 이동할 때 위치를 계산하기 위함
	if (playersHorse[playerTurn][choiceHorse].isActive == 0) {
		// 말의 위치를 시작점으로 위치
		playersHorse[playerTurn][choiceHorse].row = 12;
		playersHorse[playerTurn][choiceHorse].col = 12;
		playersHorse[playerTurn][choiceHorse].isActive = 1;
	}

	// 기존 위치를 초기화를 하는 부분
	if (playersHorse[playerTurn][choiceHorse].row != -1 && 
		playersHorse[playerTurn][choiceHorse].col != -1 && 
		playersHorse[playerTurn][choiceHorse].row % 2 == 0 && 
		playersHorse[playerTurn][choiceHorse].col % 2 == 0) {
		board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = 'o';
	}

	int row = playersHorse[playerTurn][choiceHorse].row;
	int col = playersHorse[playerTurn][choiceHorse].col;

	// 같은 팀의 말이 겹쳐졌는지 확인
	int isMerged = 0;
	if ((playersHorse[playerTurn][0].row == playersHorse[playerTurn][1].row) &&
		(playersHorse[playerTurn][0].col == playersHorse[playerTurn][1].col)) {
		isMerged = 1;
		for (int j = 0; j < PIECES; j++) {
			playersHorse[playerTurn][j].isActive = 3; // 합쳐진 상태
		}
	}
	// 같은 팀의 말이 겹쳐졌을 경우
	if (playersHorse[playerTurn][0].isActive == 3 && playersHorse[playerTurn][1].isActive == 3) {
		// 말을 나온 윷에 맞춰서 이동
		// 오른쪽 직선에서 위치하고 이동해야 할 때
		if (row > 0 && col == 12) {
			for (int i = 0; i < throwYut; i++) {
				row -= 2;
				// 오른쪽 위 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 0 && col == 12 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col -= 2;
					}
					break;
				}
			}
		}
		// 오른쪽 위 꼭짓점일 때
		else if (row == 0 && col == 12) {
			for (int j = 0; j < throwYut; j++) {
				row += 2;
				col -= 2;
			}
		}
		// 위 직선에 말이 위치하고 이동해야 할 때
		else if (row == 0 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col -= 2;
				// 맨 왼쪽 위 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 0 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						row += 2;
					}
					break;
				}
			}
		}
		// 왼쪽 위 꼭짓점일 때
		else if (row == 0 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// 왼쪽 직선에 말이 위치하고 이동해야 할 때
		else if (row < 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				// 맨 왼쪽 아래 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// 왼쪽 아래 꼭짓점일 때
		else if (row == 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// 아래 직선에 말이 위치하고 이동해야 할 때
		else if (row == 12 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// 정가운데 점일 때
		else if (row == 6 && col == 6) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// 왼쪽 아래 대각선 방향으로 말이 이동해야 할 때
		else if (row != col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col -= 2;
				// 맨 왼쪽 아래 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// 오른쪽 아래 대각선 방향으로 말이 이동해야 할 때
		else if (row == col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// 도착 처리
		if (row >= 12 && col >= 12) {
			playersHorse[playerTurn][choiceHorse].isActive = 2;
			printf("%d번째 플레이어의 말 %d가 도착했습니다!\n", playerTurn + 1, choiceHorse + 1);
			board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = 'o';
		}
		// 이동한 좌표를 업데이트
		if (row >= 0 && row < MAX && col >= 0 && col < MAX) {
			// 좌표 갱신
			for (int i = 0; i < PIECES; i++) {
				playersHorse[playerTurn][i].row = row;
				playersHorse[playerTurn][i].col = col;
			}
		}
		// 위치 갱신
		char horseChar = 'A' + playerTurn;
		board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = horseChar;
	}
	// 말이 단일로 존재할 때
	else {
		// 말을 나온 윷에 맞춰서 이동
		// 오른쪽 직선에서 위치하고 이동해야 할 때
		if (row > 0 && col == 12) {
			for (int i = 0; i < throwYut; i++) {
				row -= 2;
				// 오른쪽 위 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 0 && col == 12 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col -= 2;
					}
					break;
				}
			}
		}
		// 오른쪽 위 꼭짓점일 때
		else if (row == 0 && col == 12) {
			for (int j = 0; j < throwYut; j++) {
				row += 2;
				col -= 2;
			}
		}
		// 위 직선에 말이 위치하고 이동해야 할 때
		else if (row == 0 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col -= 2;
				// 맨 왼쪽 위 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 0 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						row += 2;
					}
					break;
				}
			}
		}
		// 왼쪽 위 꼭짓점일 때
		else if (row == 0 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// 왼쪽 직선에 말이 위치하고 이동해야 할 때
		else if (row < 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				// 맨 왼쪽 아래 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// 왼쪽 아래 꼭짓점일 때
		else if (row == 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// 아래 직선에 말이 위치하고 이동해야 할 때
		else if (row == 12 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// 정가운데 점일 때
		else if (row == 6 && col == 6) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// 왼쪽 아래 대각선 방향으로 말이 이동해야 할 때
		else if (row != col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col -= 2;
				// 맨 왼쪽 아래 꼭짓점에 도달했지만 이동 횟수가 남았을 때
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// 오른쪽 아래 대각선 방향으로 말이 이동해야 할 때
		else if (row == col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// 도착 처리
		if (row >= 12 && col >= 12) {
			playersHorse[playerTurn][choiceHorse].isActive = 2;
			printf("%d번째 플레이어의 말 %d가 도착했습니다!\n", playerTurn + 1, choiceHorse + 1);
			board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = 'o';
		}
		// 이동한 좌표를 업데이트
		if (row >= 0 && row < MAX && col >= 0 && col < MAX) {
			playersHorse[playerTurn][choiceHorse].row = row;
			playersHorse[playerTurn][choiceHorse].col = col;
		}
		// 위치 갱신
		char horseChar = 'a' + playerTurn;
		board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = horseChar;
	}
}
// 상대편 말을 잡았는지 확인하는 함수 정의
void catchHorse(int choiceHorse, int player, int playerTurn)
{
	info movedHorse = playersHorse[playerTurn][choiceHorse]; // 현재 움직인 말의 정보
	int catchFlag = 0; // 말을 잡았는지 여부 체크 (0: 못 잡음, 1: 잡음)

	// 움직인 말의 활성화 상태를 확인
	if (movedHorse.isActive != 1) {
		return;
	}
	// 자신을 제외한 다른 모든 플레이어의 말 확인
	for (int i = 0; i < player; i++) {
		if (i == playerTurn) continue; // 자기 자신은 제외

		for (int j = 0; j < PIECES; j++) {
			// 상대 말이 같은 위치에 있고 활성화 상태일 경우
			if (playersHorse[i][j].row == movedHorse.row &&
				playersHorse[i][j].col == movedHorse.col &&
				playersHorse[i][j].isActive == 1) {

				// 상대 말 비활성화
				printf("%d번째 플레이어의 %d번째 말을 잡았습니다!\n", i + 1, j + 1);
				playersHorse[i][j].row = -1;
				playersHorse[i][j].col = -1;
				playersHorse[i][j].isActive = 0;

				// 잡은 플래그 설정
				catchFlag = 1;
			}
		}
	}

	// 말을 잡은 경우 윷을 한 번 더 던지고 이동
	if (catchFlag) {
		printf("윷을 던질 기회를 얻었습니다.\n");
		Sleep(1000); // 1초 대기 후 윷을 던짐

		int yut = throw(); // 윷을 던짐
		throwPrint(yut);   // 윷 던진 결과 출력

		int newChoiceHorse;
		do {
			printf("움직일 말을 선택하세요 (1~2번 중 선택): ");
			scanf("%d", &newChoiceHorse);
		} while (newChoiceHorse < 1 || newChoiceHorse > PIECES ||
			playersHorse[playerTurn][newChoiceHorse - 1].isActive == 2);

		moveHoerse(yut, player, newChoiceHorse - 1, playerTurn); // 새로 선택된 말 이동
		Sleep(500);
		system("cls");
		printBoard(); // 갱신된 보드 출력
	}
}

void gameStart(int player)
{
	// 말판 초기화
	horseReset(player);
	int yut = 0;
	int choiceHorse = 0;
	while (1) {
		// 플레이어 순서마다 동작
		for (int i = 0; i < player; i++) {
			printf("%d 번째 플레이어 차례입니다.\n", i + 1);

			int extraTurn = 1; // 윷이나 모가 나왔을 경우 추가 턴을 위한 변수
			while (extraTurn) {
				extraTurn = 0; // 기본적으로 추가 턴을 비활성화

				// 윷을 던질 건지 확인
				printf("윷을 던지겠습니다.\n");
				Sleep(1000); // 1초 딜레이 후 윷을 던짐
				yut = throw();

				// 윷을 던지는 함수 호출 후 무엇을 뽑았는지 출력
				throwPrint(yut);

				// 윷이나 모가 나온 경우 한 번 더 던질 수 있도록 설정
				if (yut == 4 || yut == 5) { // 4: 윷, 5: 모
					printf("윷이나 모가 나왔습니다! 한 번 더 던질 기회를 얻습니다.\n");
					extraTurn = 1;
				}

				// 어떤 말을 움직일 건지 확인
				printf("몇 번째 말을 움직일 것인지 선택하세요(1~2번 중 선택) : ");
				scanf("%d", &choiceHorse);
				// 말을 잘못 입력했을 경우 다시 입력받음
				while (choiceHorse < 1 || choiceHorse > PIECES || playersHorse[i][choiceHorse - 1].isActive == 2) {
					printf("다시 입력하세요 : ");
					scanf("%d", &choiceHorse);
				}

				// 말 움직이기
				moveHoerse(yut, player, choiceHorse - 1, i);
				Sleep(500);
				system("cls");

				// 말판을 출력하는 함수 호출
				printBoard();

				// 다른 말을 잡았는지 확인
				catchHorse(choiceHorse - 1, player, i);

				// 이벤트 칸에 도착했는지 확인하기 이벤트 칸은 양쪽 모서리칸과 중앙 칸
				if ((playersHorse[i][choiceHorse - 1].row == 0 && playersHorse[i][choiceHorse - 1].col == 12) ||
					(playersHorse[i][choiceHorse - 1].row == 0 && playersHorse[i][choiceHorse - 1].col == 0) ||
					(playersHorse[i][choiceHorse - 1].row == 6 && playersHorse[i][choiceHorse - 1].col == 6) ||
					(playersHorse[i][choiceHorse - 1].row == 12 && playersHorse[i][choiceHorse - 1].col == 0)) {
					// 이벤트 발생
					printf("이벤트 칸의 도착했습니다!!\n\n");
					event(i, choiceHorse - 1, player);
				}

				// 도착했는지 확인
				checkArr(player);
			}
		}
	}
}