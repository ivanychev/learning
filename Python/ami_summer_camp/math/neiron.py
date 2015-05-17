__author__ = 'Sergey Ivanychev'

def nersum2(x1,x2,w1,w2):
	return w1*x1+w2*x2

def main():
    x = []
    y = []
    w11 = []
    w21 = []
    err = 1
    w11 = 0.5
    w21 = 0.5

    while (err>0.01) or (err < -0.01):
        x = list(map(int, input().split()))
        sum = nersum2(x[0],x[1], w11, w21)
        print(sum, end=" ")
        exp_result = list(map(int, input("expected? ").split()))
        err = exp_result[0] - sum
        if (err>0.01) or (err < -0.01):
            w11 = w11 + err*0.2
            w21 = w21 + err*0.3

    print("\nprint \" kill\" to kill me")
    print("if you want to save my life, write a pair of numbers")
    print("\n")
    print("please")

    lisx = input().split()
    while lisx[0] != "kill":
        x1 = float(lisx[0])
        x2 = float(lisx[1])
        print(nersum2(x1,x2,w11,w21))
        lisx = input().split()


    if lisx[0] == "kill":
        print("Le calmari est mort, vive le calmari!")
        return 0

main()
