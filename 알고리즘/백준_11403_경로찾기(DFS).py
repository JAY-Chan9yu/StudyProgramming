    N = int(input())

inputMap = [[0 for col in range(0, N)] for row in range(0, N)]

for i in range(0, N) :
    for j, m in enumerate(map(int, input().split())) :
        inputMap[i][j] = m

#플로이드 워셜 알고리즘(Floyd Warshall Algorithm) 이용
for k in range(0, N) :
    for i in range(0, N) :
        for j in range(0, N):
            if inputMap[i][k] and inputMap[k][j] :
                inputMap[i][j] = 1

for i in range(0, N) :
    _str = ""
    for j in range(0, N) :
        _str += str(inputMap[i][j]) +  " "
    print(_str)
