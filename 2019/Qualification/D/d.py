import sys
def solve():
    N, B, F = map(int, input().split())
    mask = (1 << F) - 1
    for i in range(F):
        send = "".join(map(str, [(((mask & x) >> i) & 1) for x in range(N)]))
        print(send)
    sys.stdout.flush()

    recv = [list(map(int, input())) for _ in range(F)]

    ans = []
    i = 0
    for x in range(N):
        if i == N - B:
            ans.append(x)
            continue
        xx = 0
        for j in range(F):
            xx |= (recv[j][i]) << j
        if xx == (x & mask):
            i += 1
        else:
            ans.append(x)
    print(" ".join(map(str, ans)))
    sys.stdout.flush()
    return int(input()) == 1

if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        if not solve():
            break
