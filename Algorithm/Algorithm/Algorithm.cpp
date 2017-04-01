/******************************************************************************/
/*                            �˰��� ����                                   */
/* �־��� �迭���� ������, �Ʒ� �̷��� �ι������θ� ��������                  */
/* ������ : 0, 0  �������� : �迭�� �� ex) ���� �׽�Ʈ ���ۿ����� 3, 3        */
/* ���� ���� 1(coin)�� ������ ��θ� Ž���� �ִ� ��� coin�� ���� �� �ִ��� */
/* ����ϴ� �˰��� ���� �Դϴ�.                                             */
/* �ذ��� : ���ȣ��                                                        */
/******************************************************************************/
#include "stdafx.h"

int testBuf[4][4] = {
	{0,0,0,0},
	{1,0,1,1},
	{0,0,0,0},
	{1,1,1,1}
};


int result = 0;
 //            �迭               �����    Ž���� ���
void checkCoin(int _array[][4], int _result, int _surchX, int _surchY)
{
	int i, j, t;
	int checkX = 0, checkY = 0; // �迭�� ���̸� Ž���ϱ� ���� ����
	int tempXSum = 0, tempYSum = 0;
	int tempSum = 0;
	int sumCoin = 0; // ���� ���ϱ�

	// �迭�� ������ �Ѿ�� ���ȣ�� ����
	if (_surchX > 3) return;
	if (_surchY > 3) return;
	checkX = _surchX;
	checkY = _surchY;
	sumCoin = _result;
	sumCoin += _array[checkY][checkX];
	
	//�����
	printf("X��ǥ : %d, Y��ǥ : %d, sumCoin : %d, resultCoin : %d \n", checkX, checkY, sumCoin, result);

	checkCoin(_array, sumCoin, checkX + 1, checkY);
	checkCoin(_array, sumCoin, checkX, checkY + 1);

	// �迭�� �ְ� ���̱������� ���ݱ��� ���� ���� ������ ������ ������� ���ε�
	if (result < sumCoin) result = sumCoin;
}

int main()
{
	int x = 0, y = 0;
	// checkCoin(pro, 6, 7);
	checkCoin(testBuf, result, x, y);
	printf("*************************\n");
	printf("���� ����� : %d\n", result);
	printf("*************************\n");

    return 0;
}

/*
//----------------------------------- �̰� �ʹ� ���� �����ϴٰ� ���� �� ---------------------------------------//
// 1. ���� ��ġ�� �������� ������ or �Ʒ��� Coin�� ������ üũ
// 2. ������ ������ �̵�
// 3. �ݺ�
void checkCoin(int _array[][6], int _X, int _Y)
{
int i, j, t;
int checkX = 0, checkY = 0;
int tempXSum = 0, tempYSum = 0;
int SumCoin = 0; // ���� ���ϱ�

while(checkX < 6 && checkY < 7) { // ������ �迭�� ũ�⸦ ����� ������ üũ
SumCoin += _array[checkY][checkX]; // ���� ��ġ�� ������ ����
tempXSum = 0;
tempYSum = 0;

// 1���� �����ϴ� ������ ������ġ�� ���� ������ ���ϱ� ���ؼ�(0 �̵� 1�̵� ���簪�� �̹� üũ�� ���̹Ƿ�)
for(i = checkX + 1; i < _X; i++) tempXSum += _array[checkY][i]; // ���� X��ǥ �������� �������� Coin ���� üũ
for (i = checkY + 1; i < _Y; i++) tempYSum += _array[i][checkX]; // ���� Y��ǥ  �������� �Ʒ����� Coin ���� üũ

// ���� ���ؼ� ������ �� ���������� �̵�
if (tempXSum > tempYSum) checkX++;
else if(tempXSum < tempYSum) checkY++;
else { // x, y�� ������ ������ ���� ���

}

}

printf("The Maximum Coin is %d \n", SumCoin);
}
*/