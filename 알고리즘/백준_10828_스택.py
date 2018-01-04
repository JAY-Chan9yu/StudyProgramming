N = int(input())

STACK = []
for i in range(0, N) :
    inputCmd = input()
    if 'push' in inputCmd :
        _cmd, num = inputCmd.split()
        STACK.append(int(num))
    elif inputCmd == 'pop' or inputCmd == 'top' :
        if not len(STACK) :
            print("-1")
        else :
            print(str(STACK[len(STACK) - 1]))
            if inputCmd == 'pop' :
                STACK.pop()
    elif inputCmd == 'size' :
        print(str(len(STACK)))
    elif inputCmd == 'empty' :
        if not len(STACK) :
            print('1')
        else :
            print('0')
