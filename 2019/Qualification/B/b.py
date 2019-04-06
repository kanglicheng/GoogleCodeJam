def solve():
    N = int(input())
    S = input()
    ans = ""
    for c in S:
        ans += "E" if c == "S" else "S"
    return ans


if __name__ == "__main__":
    T = int(input())
    for t in range(1, T + 1):
        print("Case #{}: {}".format(t, solve()))
