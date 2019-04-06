import math

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)

def solve():
    N, L = input().split()
    L = int(L)
    cipher = [int(x) for x in input().split()]
    lst = [0 for _ in range(L + 1)]
    for i in range(L - 1):
        if cipher[i] != cipher[i + 1]:
            k = gcd(cipher[i], cipher[i + 1])
            lst[i] = cipher[i] // k
            lst[i + 1] = k
            for j in range(i + 2, L + 1):
                lst[j] = cipher[j - 1] // lst[j - 1]
            for j in range(i - 1, -1, -1):
                lst[j] = cipher[j] // lst[j + 1]
            break

    alphabet = sorted(set(lst))
    dict = {}
    for i, p in enumerate(alphabet):
        dict[p] = chr(i + ord('A'))

    plain = ""
    for x in lst:
        plain += dict[x]
    return plain

if __name__ == "__main__":
    T = int(input())
    for t in range(1, T + 1):
        print("Case #{}: {}".format(t, solve()))
