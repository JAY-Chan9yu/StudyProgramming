N = int(input())

numbers = []
numCnt = 0 # 수열 순서에 따라증가
stackNum = 1 # stack 집어넣는 숫자. push 할때마다 증가
STACK = []
output = []
flag = 0
# 수열 입력
for i in range(0, N) :
    numbers.append(int(input()))
    if numbers[i] > N or (len(STACK) != 0 and numbers[i] < STACK[len(STACK)-1]) :
        flag = 1
    while stackNum <= numbers[i] :
        STACK.append(stackNum) # 입력된 숫자까지 push
        output.append('+')
        stackNum += 1
    STACK.pop()
    output.append('-')

if flag :
    print('NO')
else :
    for i, out in enumerate(output) :
        print(out)
#print(numbers)
'''
STACK.append(stackNum) # 무조건 첫번째는 push
print('+')
while numCnt <= N :
    if STACK[len(STACK)-1] != numbers[numCnt] : # 수열의 x번째 순선와 스택의 top의 숫자가 다를 경우 push(pop X)
        stackNum += 1
        if numbers[numCnt] < stackNum :
            print('NO')
            break
        else :
            STACK.append(stackNum)
            print('+')
    else :
        STACK.pop()
        numCnt += 1 # 수열의 x+1번째로 넘어감
        print('-')
'''


'''while numCnt < N :
    if STACK[len(STACK) - 1] == numbers[numCnt] and len(STACK) - 1 > 0 :
        numCnt += 1
        print(str(STACK[len(STACK) - 1]) + ', -')
        #print('-')
        STACK.pop()
        if numCnt < N and len(STACK) - 1 > 0 :
            if STACK[len(STACK) - 1] != numbers[numCnt] and numbers[numCnt] < stackNum :
                #print("NO [" + str(STACK[len(STACK) - 1]) + ", " + str(numbers[numCnt]) + ", " + str(stackNum) + "]")
                print("NO")
                break
    else :
        if stackNum <= N :
            print("push " + str(stackNum))
            #print('+')
            STACK.append(stackNum)
            stackNum += 1
'''
    #if numCnt >= N :
        #break


'''class Test :
    a = 0

    def __init__(self) :
        Test.a += 1

    def _test(self, a) :
        self.A = a

    @classmethod
    def printCls(cls) :
        print("클래스변수 : " + str(cls.a))
        print("Test 변수 : " + str(Test.a))

    def printself(self) :
        print("self 변수 : " + str(self.a))

testV = 3
if testV is 2 :
    testV = 5

print(testV)

a = Test()
b = Test()
a.test = 5
c = Test()
a.printCls()
b.printCls()
a.printself()
print(a.test)
'''
