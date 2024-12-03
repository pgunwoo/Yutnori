#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

#define MAX 13 // ���� ũ��
#define PLAYERS 4 // �ִ� �÷��̾� 4��
#define PIECES 2 // �÷��̾� �� �� 2��

// �÷��̾��� �� ��ġ ���� ����ü
typedef struct {
	int row, col; // ���� ���� ��ġ (��, ��)
	int isActive; // 0�̸� ��Ȱ��ȭ, 1�̸� Ȱ��ȭ, 2�̸� ���, 3�̸� ���� �� ������ ��ħ
}info;

info playersHorse[PLAYERS][PIECES]; // �� �÷��̾��� �� ��ġ ����

// ������ �� ���� ���� ����
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
// �ʱ� ������ ������ ���� �����ϱ� ���� ����
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

// ���� �̵��ϴ� �Լ�
void moveHoerse(int throwYut, int player, int choiceHorse, int playerTurn);
// ���� ������ �Լ�
int throw();
// ������ ����ϴ� �Լ�
void printBoard();
// �� ��ġ�� �ʱ�ȭ�ϴ� �Լ�
void horseReset(int player);
// ������ ���� �����Լ�
void gameStart(int player);
// ���� �� ����Լ�
void throwPrint(int throwYut);
// ���� ���� Ȯ�� �Լ�
void checkArr(int player);
// ����� ���� ��Ҵ��� Ȯ���ϴ� �Լ�
void catchHorse(int choiceHorse, int player, int playerTurn);
// �̺�Ʈ ĭ �Լ�
void event(int playerTurn, int choiceHorse, int player);
// ��ġ ��ȯ �̺�Ʈ �Լ�
void eventSwap(int playerTurn, int choiceHorse, int player);

int main(void)
{
	int player;
	printf("�÷��̾� ���� �����Ͻÿ�(�ִ� 4��) : ");
	scanf("%d", &player);
	// �÷��̾� ���� �ùٸ��� Ȯ��
	if (player < 2 || player > 4) {
		printf("�ٽ� �÷��̾� ���� �����Ͻÿ�(�ּ� 2��, �ִ� 4��) : ");
		scanf("%d", &player);
	}
	// ������ �����ϴ� �Լ� ȣ��
	gameStart(player);
	return 0;
}
// ���� ���� Ȯ�� �Լ�
void checkArr(int player)
{
	// ���� �����ߴ��� Ȯ�� �� ���
	for (int i = 0; i < player; i++) {
		printf("�÷��̾� %d�� ����: ", i + 1);
		for (int j = 0; j < PIECES; j++) {
			if (playersHorse[i][j].isActive == 2) {
				printf("�� %d [����] ", j + 1);
			}
			else if (playersHorse[i][j].isActive == 1) {
				printf("�� %d [���� ��] ", j + 1);
			}
			else if (playersHorse[i][j].isActive == 0) {
				printf("�� %d [��� ��] ", j + 1);
			}
			else {
				printf("�� %d [������] ", j + 1);
			}
		}
		printf("\n");
		printf("\n");
	}
	printf("\n");
	printf("\n");
	// ���� �� �����ߴ��� Ȯ��
	for (int i = 0; i < player; i++) {
		int cleared = 1;
		// �� ���� �������� �ʾҴٸ� �ٸ� �÷��̾��� ���� Ȯ��
		for (int j = 0; j < PIECES; j++) {
			if (playersHorse[i][j].isActive != 2) {
				cleared = 0;
				break;
			}
		}
		// ��� �������� ���
		if (cleared) {
			printf("\n�÷��̾� %d�� ��� ���� �������׽��ϴ�! �¸�!\n", i + 1);
			exit(0); // ���� ����
		}
	}
}
// �̺�Ʈ ĭ�� �������� ��� �Լ� ����
void event(int playerTurn, int choiceHorse, int player)
{
	info* horse = &playersHorse[playerTurn][choiceHorse];

	srand(time(NULL)); // ���� �Լ� ����
	int n = rand() % 4; // 0 ~ 3 ������ ���� ��� ��ȯ

	// ��� ���� ����
	if (n == 0) {
		printf("��� ���� �׽��ϴ�.\n\n");
		// �÷��̾��� �� �ʱ�ȭ
		for (int i = 0; i < player; i++) {
			for (int j = 0; j < PIECES; j++) {
				// ������ ���� �ʱ�ȭ���� ����
				if (playersHorse[i][j].isActive != 2) {
					playersHorse[i][j].row = -1;
					playersHorse[i][j].col = -1;
					playersHorse[i][j].isActive = 0; // ��Ȱ��ȭ�� ����
				}
			}
		}
		// ���� �ʱ�ȭ
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				board[i][j] = reset_board[i][j];
			}
		}
		
		// �ʱ�ȭ�� ���¸� ȭ�鿡 ���
		printBoard();
		Sleep(2000); // 2�� ���
		system("cls");

		return;
	}
	// ��� ���� ��ġ �ٲٱ�
	else if (n == 1) {
		eventSwap(playerTurn, choiceHorse, player);
	}
	// ���ϴ� ��� �� ���� ���̱�
	else if (n == 2) {
		printf("���ϴ� ����� ���� ��� ���Դϴ�.\n\n");
		int killPlayer;

		// ���ϴ� �÷��̾� ����
		printf("���ϴ� �÷��̾ �����Ͻÿ� : ");
		scanf("%d", &killPlayer);

		// �߸� �Է����� ��� �ٽ� �Է¹���
		while (killPlayer < 1 || killPlayer > player || killPlayer - 1 == playerTurn) {
			printf("�߸��� �÷��̾� ��ȣ�Դϴ�. (1 ~ %d ���̿��� �մϴ�.) �ٽ� �Է�: ", player - 1);
			scanf("%d", &killPlayer);
		}

		// ���� �ִ� �ڸ� ����
		for (int i = 0; i < PIECES; i++) {
			if (playersHorse[killPlayer - 1][i].isActive == 1) {
				board[playersHorse[killPlayer - 1][i].row][playersHorse[killPlayer - 1][i].col] = 'o';
				playersHorse[killPlayer - 1][i].row = -1;
				playersHorse[killPlayer - 1][i].col = -1;
				playersHorse[killPlayer - 1][i].isActive = 0;
			}
		}
		printf("%d��° �÷��̾��� ��� ���� ��Ȱ��ȭ�߽��ϴ�.\n", killPlayer - 1);

		// ������ ����ϴ� �Լ� ȣ��
		printBoard();
		Sleep(500);
		system("cls");
	}
	// �� �� �� �� ������ �̵�
	else if (n == 3) {
		printf("���� �� �� �� �����ϴ�.\n");
		
		// ���� ���� ���� Ȯ��
		printf("���� �����ڽ��ϴ�.\n");
		Sleep(1000); // 1�� ������ �� ���� ����
		int yut = throw();

		// ���� ������ �Լ� ȣ�� �� ������ �̾Ҵ��� ���
		throwPrint(yut);

		// � ���� ������ ���� Ȯ��
		printf("�� ��° ���� ������ ������ �����ϼ���(1~2�� �� ����) : ");
		scanf("%d", &choiceHorse);

		// ���� �߸� �Է����� ��� �ٽ� �Է¹���
		while (choiceHorse < 1 || choiceHorse > 2 || playersHorse[playerTurn][choiceHorse - 1].isActive == 2) {
			printf("�ٽ� �Է��ϼ��� : ");
			scanf("%d", &choiceHorse);
		}

		// �� �����̱�
		moveHoerse(yut, player, choiceHorse - 1, playerTurn);
		Sleep(500);
		system("cls");

		// ������ ����ϴ� �Լ� ȣ��
		printBoard();

		// ���� ���� ���������� Ȯ��
		if ((playersHorse[playerTurn][0].row == playersHorse[playerTurn][1].row) && (playersHorse[playerTurn][0].col == playersHorse[playerTurn][1].col)) {
			for (int j = 0; j < PIECES; j++) {
				playersHorse[playerTurn][j].isActive = 3;
			}
		}

		// �ٸ� ���� ��Ҵ��� Ȯ��
		catchHorse(choiceHorse - 1, player, playerTurn);

		// �̺�Ʈ ĭ�� �����ߴ��� Ȯ���ϱ� �̺�Ʈ ĭ�� ���� �𼭸�ĭ�� �߾� ĭ
		if ((playersHorse[playerTurn][choiceHorse].row == 0 && playersHorse[playerTurn][choiceHorse].col == 12) &&
			(playersHorse[playerTurn][choiceHorse].row == 0 && playersHorse[playerTurn][choiceHorse].col == 0) &&
			(playersHorse[playerTurn][choiceHorse].row == 6 && playersHorse[playerTurn][choiceHorse].col == 6) &&
			(playersHorse[playerTurn][choiceHorse].row == 12 && playersHorse[playerTurn][choiceHorse].col == 0)) {
			// �̺�Ʈ �߻�
			printf("�̺�Ʈ ĭ�� �����߽��ϴ�!!\n\n");
			event(playerTurn, choiceHorse, player);
		}

		// �����ߴ��� Ȯ��
		checkArr(player);
	}
	else {
		printf("��!\n");
		return;
	}
}
// ��ġ ��ȯ �̺�Ʈ �Լ�
void eventSwap(int playerTurn, int choiceHorse, int player)
{
	info* currentHorse = &playersHorse[playerTurn][choiceHorse]; // ���� ���� ����

	// ���� ���� Ȱ��ȭ ���°� �ƴ� ���
	if (currentHorse->isActive != 1) {
		printf("���� ���õ� ���� Ȱ��ȭ�Ǿ� ���� �ʽ��ϴ�. ��ġ�� ��ȯ�� �� �����ϴ�.\n");
		return;
	}

	int targetPlayer;
	int targetHorse;
	int valid = 0; // ��ȿ�� �Է� ����

	// ��ȿ�� ��� �÷��̾� �Է¹ޱ�
	do {
		printf("��ġ�� ��ȯ�� ��� �÷��̾ �����ϼ��� (1 ~ %d): ", player);
		scanf("%d", &targetPlayer);

		// �÷��̾� ��ȣ Ȯ��
		if (targetPlayer < 1 || targetPlayer > PLAYERS || targetPlayer - 1 == playerTurn) {
			printf("�߸��� �÷��̾� ��ȣ�Դϴ�. �ٽ� �Է��ϼ���.\n");
		}
		else {
			valid = 1;
		}
	} while (!valid);

	// ��ȿ�� ��� �� �Է¹ޱ�
	valid = 0;
	do {
		printf("��� �÷��̾��� ���� �����ϼ��� (1 ~ %d): ", PIECES);
		scanf("%d", &targetHorse);

		// �� ��ȣ Ȯ��
		if (targetHorse < 1 || targetHorse > PIECES) {
			printf("�߸��� �� ��ȣ�Դϴ�. �ٽ� �Է��ϼ���.\n");
		}
		else {
			valid = 1;
		}
	} while (!valid);

	// ��� ���� ������ ������
	info* opponentHorse = &playersHorse[targetPlayer - 1][targetHorse - 1];

	// ��� ���� Ȱ��ȭ ���°� �ƴ� ���
	if (opponentHorse->isActive != 1) {
		printf("������ ��� �÷��̾��� ���� Ȱ��ȭ�Ǿ� ���� �ʽ��ϴ�. ��ġ�� ��ȯ�� �� �����ϴ�.\n");
		return;
	}

	// ���� ���� ��� ���� ��ġ ��ȯ
	int tempRow = currentHorse->row;
	int tempCol = currentHorse->col;
	currentHorse->row = opponentHorse->row;
	currentHorse->col = opponentHorse->col;
	opponentHorse->row = tempRow;
	opponentHorse->col = tempCol;

	printf("�÷��̾� %d�� %d��° ���� �÷��̾� %d�� %d��° ���� ��ġ�� ��ȯ�߽��ϴ�!\n",
		playerTurn + 1, choiceHorse + 1, targetPlayer, targetHorse);

	// ���� ���� ����
	char playerChar = 'A' + playerTurn;
	char targetChar = 'A' + (targetPlayer - 1);
	board[currentHorse->row][currentHorse->col] = playerChar;
	board[opponentHorse->row][opponentHorse->col] = targetChar;

	// ���� ��ġ �ʱ�ȭ
	board[tempRow][tempCol] = 'o';
	board[currentHorse->row][currentHorse->col] = playerChar;
}
// ���� ���� ����ϴ� �Լ� ����
void throwPrint(int throwYut)
{
	const char* results[] = { "��", "��", "��", "��", "��" };
	printf("���� ���: %s\n", results[throwYut - 1]);
}
// ���� ������ �Լ� ����
int throw()
{
	srand(time(NULL)); // ���� �Լ� ����
	int n = rand() % 5 + 1; // 1 ~ 5������ ���� ��� ��ȯ
	return n;
}
// �������� ����ϴ� �Լ� ����
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
// ���� ��ġ�� �ʱ�ȭ �ϴ� �Լ� ����
void horseReset(int player)
{
	// �÷��̾��� �� �ʱ�ȭ
	for (int i = 0; i < player; i++) {
		for (int j = 0; j < PIECES; j++) {
			playersHorse[i][j].row = -1;
			playersHorse[i][j].col = -1;
			playersHorse[i][j].isActive = 0;
		}
	}
	// ���� �ʱ�ȭ
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			board[i][j] = reset_board[i][j];
		}
	}
}
// ���� �̵��ϴ� �Լ� ����
void moveHoerse(int throwYut, int player, int choiceHorse, int playerTurn)
{
	// ó�� �̵��� �� ��ġ�� ����ϱ� ����
	if (playersHorse[playerTurn][choiceHorse].isActive == 0) {
		// ���� ��ġ�� ���������� ��ġ
		playersHorse[playerTurn][choiceHorse].row = 12;
		playersHorse[playerTurn][choiceHorse].col = 12;
		playersHorse[playerTurn][choiceHorse].isActive = 1;
	}

	// ���� ��ġ�� �ʱ�ȭ�� �ϴ� �κ�
	if (playersHorse[playerTurn][choiceHorse].row != -1 && 
		playersHorse[playerTurn][choiceHorse].col != -1 && 
		playersHorse[playerTurn][choiceHorse].row % 2 == 0 && 
		playersHorse[playerTurn][choiceHorse].col % 2 == 0) {
		board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = 'o';
	}

	int row = playersHorse[playerTurn][choiceHorse].row;
	int col = playersHorse[playerTurn][choiceHorse].col;

	// ���� ���� ���� ���������� Ȯ��
	int isMerged = 0;
	if ((playersHorse[playerTurn][0].row == playersHorse[playerTurn][1].row) &&
		(playersHorse[playerTurn][0].col == playersHorse[playerTurn][1].col)) {
		isMerged = 1;
		for (int j = 0; j < PIECES; j++) {
			playersHorse[playerTurn][j].isActive = 3; // ������ ����
		}
	}
	// ���� ���� ���� �������� ���
	if (playersHorse[playerTurn][0].isActive == 3 && playersHorse[playerTurn][1].isActive == 3) {
		// ���� ���� ���� ���缭 �̵�
		// ������ �������� ��ġ�ϰ� �̵��ؾ� �� ��
		if (row > 0 && col == 12) {
			for (int i = 0; i < throwYut; i++) {
				row -= 2;
				// ������ �� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 0 && col == 12 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col -= 2;
					}
					break;
				}
			}
		}
		// ������ �� �������� ��
		else if (row == 0 && col == 12) {
			for (int j = 0; j < throwYut; j++) {
				row += 2;
				col -= 2;
			}
		}
		// �� ������ ���� ��ġ�ϰ� �̵��ؾ� �� ��
		else if (row == 0 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col -= 2;
				// �� ���� �� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 0 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						row += 2;
					}
					break;
				}
			}
		}
		// ���� �� �������� ��
		else if (row == 0 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// ���� ������ ���� ��ġ�ϰ� �̵��ؾ� �� ��
		else if (row < 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				// �� ���� �Ʒ� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// ���� �Ʒ� �������� ��
		else if (row == 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// �Ʒ� ������ ���� ��ġ�ϰ� �̵��ؾ� �� ��
		else if (row == 12 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// ����� ���� ��
		else if (row == 6 && col == 6) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// ���� �Ʒ� �밢�� �������� ���� �̵��ؾ� �� ��
		else if (row != col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col -= 2;
				// �� ���� �Ʒ� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// ������ �Ʒ� �밢�� �������� ���� �̵��ؾ� �� ��
		else if (row == col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// ���� ó��
		if (row >= 12 && col >= 12) {
			playersHorse[playerTurn][choiceHorse].isActive = 2;
			printf("%d��° �÷��̾��� �� %d�� �����߽��ϴ�!\n", playerTurn + 1, choiceHorse + 1);
			board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = 'o';
		}
		// �̵��� ��ǥ�� ������Ʈ
		if (row >= 0 && row < MAX && col >= 0 && col < MAX) {
			// ��ǥ ����
			for (int i = 0; i < PIECES; i++) {
				playersHorse[playerTurn][i].row = row;
				playersHorse[playerTurn][i].col = col;
			}
		}
		// ��ġ ����
		char horseChar = 'A' + playerTurn;
		board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = horseChar;
	}
	// ���� ���Ϸ� ������ ��
	else {
		// ���� ���� ���� ���缭 �̵�
		// ������ �������� ��ġ�ϰ� �̵��ؾ� �� ��
		if (row > 0 && col == 12) {
			for (int i = 0; i < throwYut; i++) {
				row -= 2;
				// ������ �� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 0 && col == 12 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col -= 2;
					}
					break;
				}
			}
		}
		// ������ �� �������� ��
		else if (row == 0 && col == 12) {
			for (int j = 0; j < throwYut; j++) {
				row += 2;
				col -= 2;
			}
		}
		// �� ������ ���� ��ġ�ϰ� �̵��ؾ� �� ��
		else if (row == 0 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col -= 2;
				// �� ���� �� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 0 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						row += 2;
					}
					break;
				}
			}
		}
		// ���� �� �������� ��
		else if (row == 0 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// ���� ������ ���� ��ġ�ϰ� �̵��ؾ� �� ��
		else if (row < 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				// �� ���� �Ʒ� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// ���� �Ʒ� �������� ��
		else if (row == 12 && col == 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// �Ʒ� ������ ���� ��ġ�ϰ� �̵��ؾ� �� ��
		else if (row == 12 && col > 0) {
			for (int i = 0; i < throwYut; i++) {
				col += 2;
			}
		}
		// ����� ���� ��
		else if (row == 6 && col == 6) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// ���� �Ʒ� �밢�� �������� ���� �̵��ؾ� �� ��
		else if (row != col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col -= 2;
				// �� ���� �Ʒ� �������� ���������� �̵� Ƚ���� ������ ��
				if (row == 12 && col == 0 && throwYut - i > 1) {
					for (int j = 1; j < throwYut - i; j++) {
						col += 2;
					}
					break;
				}
			}
		}
		// ������ �Ʒ� �밢�� �������� ���� �̵��ؾ� �� ��
		else if (row == col) {
			for (int i = 0; i < throwYut; i++) {
				row += 2;
				col += 2;
			}
		}
		// ���� ó��
		if (row >= 12 && col >= 12) {
			playersHorse[playerTurn][choiceHorse].isActive = 2;
			printf("%d��° �÷��̾��� �� %d�� �����߽��ϴ�!\n", playerTurn + 1, choiceHorse + 1);
			board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = 'o';
		}
		// �̵��� ��ǥ�� ������Ʈ
		if (row >= 0 && row < MAX && col >= 0 && col < MAX) {
			playersHorse[playerTurn][choiceHorse].row = row;
			playersHorse[playerTurn][choiceHorse].col = col;
		}
		// ��ġ ����
		char horseChar = 'a' + playerTurn;
		board[playersHorse[playerTurn][choiceHorse].row][playersHorse[playerTurn][choiceHorse].col] = horseChar;
	}
}
// ����� ���� ��Ҵ��� Ȯ���ϴ� �Լ� ����
void catchHorse(int choiceHorse, int player, int playerTurn)
{
	info movedHorse = playersHorse[playerTurn][choiceHorse]; // ���� ������ ���� ����
	int catchFlag = 0; // ���� ��Ҵ��� ���� üũ (0: �� ����, 1: ����)

	// ������ ���� Ȱ��ȭ ���¸� Ȯ��
	if (movedHorse.isActive != 1) {
		return;
	}
	// �ڽ��� ������ �ٸ� ��� �÷��̾��� �� Ȯ��
	for (int i = 0; i < player; i++) {
		if (i == playerTurn) continue; // �ڱ� �ڽ��� ����

		for (int j = 0; j < PIECES; j++) {
			// ��� ���� ���� ��ġ�� �ְ� Ȱ��ȭ ������ ���
			if (playersHorse[i][j].row == movedHorse.row &&
				playersHorse[i][j].col == movedHorse.col &&
				playersHorse[i][j].isActive == 1) {

				// ��� �� ��Ȱ��ȭ
				printf("%d��° �÷��̾��� %d��° ���� ��ҽ��ϴ�!\n", i + 1, j + 1);
				playersHorse[i][j].row = -1;
				playersHorse[i][j].col = -1;
				playersHorse[i][j].isActive = 0;

				// ���� �÷��� ����
				catchFlag = 1;
			}
		}
	}

	// ���� ���� ��� ���� �� �� �� ������ �̵�
	if (catchFlag) {
		printf("���� ���� ��ȸ�� ������ϴ�.\n");
		Sleep(1000); // 1�� ��� �� ���� ����

		int yut = throw(); // ���� ����
		throwPrint(yut);   // �� ���� ��� ���

		int newChoiceHorse;
		do {
			printf("������ ���� �����ϼ��� (1~2�� �� ����): ");
			scanf("%d", &newChoiceHorse);
		} while (newChoiceHorse < 1 || newChoiceHorse > PIECES ||
			playersHorse[playerTurn][newChoiceHorse - 1].isActive == 2);

		moveHoerse(yut, player, newChoiceHorse - 1, playerTurn); // ���� ���õ� �� �̵�
		Sleep(500);
		system("cls");
		printBoard(); // ���ŵ� ���� ���
	}
}

void gameStart(int player)
{
	// ���� �ʱ�ȭ
	horseReset(player);
	int yut = 0;
	int choiceHorse = 0;
	while (1) {
		// �÷��̾� �������� ����
		for (int i = 0; i < player; i++) {
			printf("%d ��° �÷��̾� �����Դϴ�.\n", i + 1);

			int extraTurn = 1; // ���̳� �� ������ ��� �߰� ���� ���� ����
			while (extraTurn) {
				extraTurn = 0; // �⺻������ �߰� ���� ��Ȱ��ȭ

				// ���� ���� ���� Ȯ��
				printf("���� �����ڽ��ϴ�.\n");
				Sleep(1000); // 1�� ������ �� ���� ����
				yut = throw();

				// ���� ������ �Լ� ȣ�� �� ������ �̾Ҵ��� ���
				throwPrint(yut);

				// ���̳� �� ���� ��� �� �� �� ���� �� �ֵ��� ����
				if (yut == 4 || yut == 5) { // 4: ��, 5: ��
					printf("���̳� �� ���Խ��ϴ�! �� �� �� ���� ��ȸ�� ����ϴ�.\n");
					extraTurn = 1;
				}

				// � ���� ������ ���� Ȯ��
				printf("�� ��° ���� ������ ������ �����ϼ���(1~2�� �� ����) : ");
				scanf("%d", &choiceHorse);
				// ���� �߸� �Է����� ��� �ٽ� �Է¹���
				while (choiceHorse < 1 || choiceHorse > PIECES || playersHorse[i][choiceHorse - 1].isActive == 2) {
					printf("�ٽ� �Է��ϼ��� : ");
					scanf("%d", &choiceHorse);
				}

				// �� �����̱�
				moveHoerse(yut, player, choiceHorse - 1, i);
				Sleep(500);
				system("cls");

				// ������ ����ϴ� �Լ� ȣ��
				printBoard();

				// �ٸ� ���� ��Ҵ��� Ȯ��
				catchHorse(choiceHorse - 1, player, i);

				// �̺�Ʈ ĭ�� �����ߴ��� Ȯ���ϱ� �̺�Ʈ ĭ�� ���� �𼭸�ĭ�� �߾� ĭ
				if ((playersHorse[i][choiceHorse - 1].row == 0 && playersHorse[i][choiceHorse - 1].col == 12) ||
					(playersHorse[i][choiceHorse - 1].row == 0 && playersHorse[i][choiceHorse - 1].col == 0) ||
					(playersHorse[i][choiceHorse - 1].row == 6 && playersHorse[i][choiceHorse - 1].col == 6) ||
					(playersHorse[i][choiceHorse - 1].row == 12 && playersHorse[i][choiceHorse - 1].col == 0)) {
					// �̺�Ʈ �߻�
					printf("�̺�Ʈ ĭ�� �����߽��ϴ�!!\n\n");
					event(i, choiceHorse - 1, player);
				}

				// �����ߴ��� Ȯ��
				checkArr(player);
			}
		}
	}
}