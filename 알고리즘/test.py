class TestMethod :
    instVal = 0

    def __init__(self) : # 초기자(c++의 생성자와는 조금 다름)
        # 객체가 생성 될 때마다 instVal 증가
        TestMethod.instVal += 1

    def selfAdd(self, num) :
        self.instVal += num

    def classAdd(self, num) :
        TestMethod.instVal += num

    def outputInst(self) :
        print("인스턴스변수(self) : ", self.instVal)
        print("인스턴스변수(class명) : ", TestMethod.instVal)

    @classmethod
    def outputClass(cls, num) :
        cls.instVal += num
        #TestMethod.instVal += num
        print("클래스변수 : ", cls.instVal)

    @staticmethod
    def outputStatic(num) :
        TestMethod.instVal += num
        print("스태틱변수 : ", TestMethod.instVal)

testA = TestMethod() # 객체생성 1
'''testB = TestMethod() # 객체생성 2
testC = TestMethod() # 객체생성 3

#print("TestMethod class의 instVal(인스턴스변수) : ", TestMethod.instVal)
print("testA의 instVal(인스턴스변수) : ", testA.instVal)
print("testB의 instVal(인스턴스변수) : ", testB.instVal)
print("testC의 instVal(인스턴스변수) : ", testC.instVal)
print('\n')
'''
#testA.outputStatic(100)
testA.outputClass(100)
TestMethod.outputStatic(100)
TestMethod.outputClass(100)
TestMethod.outputStatic(0)
TestMethod.outputStatic(100)
TestMethod.outputClass(0)

'''
testA.selfAdd(10)
testA.outputInst()
testB.outputInst()
testC.outputInst()
print('\n')

testA.instVal += 1000
testA.classAdd(20)
testA.outputInst()
testB.outputInst()
testC.outputInst()
print('\n')

testA.outputClass(100)
testB.outputClass(200)
testC.outputClass(300)
print('\n')

TestMethod.outputClass(700)
testA.outputStatic(1000)
testA.outputInst()
testB.outputInst()
testC.outputInst()
'''
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
