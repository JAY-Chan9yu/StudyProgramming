/******************************************************************************/
/*                            알고리즘 문제                                   */
/* 주어진 배열에서 오른쪽, 아래 이렇게 두방향으로만 움직여서                  */
/* 시작점 : 0, 0  끝나는점 : 배열의 끝 ex) 현재 테스트 버퍼에서는 3, 3        */
/* 가장 많이 1(coin)을 가지는 경로를 탐색해 최대 몇개의 coin을 가질 수 있는지 */
/* 출력하는 알고리즘 문제 입니다.                                             */
/* 해결방안 : 재귀호출                                                        */
/******************************************************************************/
#include "stdafx.h"

int testBuf[4][4] = {
	{0,0,0,0},
	{1,0,1,1},
	{0,0,0,0},
	{1,1,1,1}
};


int result = 0;
 //            배열               결과값    탐색할 경로
void checkCoin(int _array[][4], int _result, int _surchX, int _surchY)
{
	int i, j, t;
	int checkX = 0, checkY = 0; // 배열의 깊이를 탐색하기 위한 변수
	int tempXSum = 0, tempYSum = 0;
	int tempSum = 0;
	int sumCoin = 0; // 코인 더하기

	// 배열의 범위를 넘어가면 재귀호출 종료
	if (_surchX > 3) return;
	if (_surchY > 3) return;
	checkX = _surchX;
	checkY = _surchY;
	sumCoin = _result;
	sumCoin += _array[checkY][checkX];
	
	//디버깅
	printf("X좌표 : %d, Y좌표 : %d, sumCoin : %d, resultCoin : %d \n", checkX, checkY, sumCoin, result);

	checkCoin(_array, sumCoin, checkX + 1, checkY);
	checkCoin(_array, sumCoin, checkX, checkY + 1);

	// 배열의 최고 깊이까지가서 지금까지 더한 값이 이전의 값보다 높을경우 업로드
	if (result < sumCoin) result = sumCoin;
}

int main()
{
	int x = 0, y = 0;
	// checkCoin(pro, 6, 7);
	checkCoin(testBuf, result, x, y);
	printf("*************************\n");
	printf("최종 결과값 : %d\n", result);
	printf("*************************\n");

    return 0;
}

/*
//----------------------------------- 이거 너무 쉽게 생각하다가 망한 거 ---------------------------------------//
// 1. 현재 위치를 기준으로 오른쪽 or 아래의 Coin의 개수를 체크
// 2. 더많은 쪽으로 이동
// 3. 반복
void checkCoin(int _array[][6], int _X, int _Y)
{
int i, j, t;
int checkX = 0, checkY = 0;
int tempXSum = 0, tempYSum = 0;
int SumCoin = 0; // 코인 더하기

while(checkX < 6 && checkY < 7) { // 정해진 배열의 크기를 벗어나기 전까지 체크
SumCoin += _array[checkY][checkX]; // 현재 위치의 코인을 더함
tempXSum = 0;
tempYSum = 0;

// 1부터 시작하는 이유는 현재위치의 값은 무조건 더하기 위해서(0 이든 1이든 현재값은 이미 체크한 값이므로)
for(i = checkX + 1; i < _X; i++) tempXSum += _array[checkY][i]; // 현재 X좌표 기준으로 오른쪽의 Coin 개수 체크
for (i = checkY + 1; i < _Y; i++) tempYSum += _array[i][checkX]; // 현재 Y좌표  기준으로 아래쪽의 Coin 개수 체크

// 값을 비교해서 코인이 더 많은쪽으로 이동
if (tempXSum > tempYSum) checkX++;
else if(tempXSum < tempYSum) checkY++;
else { // x, y의 코인의 개수가 같을 경우

}

}

printf("The Maximum Coin is %d \n", SumCoin);
}
*/