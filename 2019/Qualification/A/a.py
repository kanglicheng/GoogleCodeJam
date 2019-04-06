def check_pow_10(num):
    if num[0] != "1":
        return False
    for c in num[1:]:
        if c != "0":
            return False
    return True

def solve():
    N = input()
    if check_pow_10(N):
        a = "1"
        b = "9" * (len(N) - 1)
    elif len(N) == 1:
        n = int(N)
        if n == 5:
            a = "2"
            b = "3"
        else:
            a = str(n - 1)
            b = "1"
    else:
        a = b = ""
        flag = True
        for c in N:
            if c == "4":
                a += "2"
                b += "2"
                flag = False
            elif flag:
                b += c
                flag = False
            else:
                a += c
                b += "0"
    return a + " " + b


if __name__ == "__main__":
    T = int(input())
    for t in range(1, T + 1):
        print("Case #{}: {}".format(t, solve()))
