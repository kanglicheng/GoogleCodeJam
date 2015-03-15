from bisect import bisect_right

def find_gt(a, x):
    i = bisect_right(a, x)
    if i != len(a):
        return i
    else:
        return None

def opt(A, lstB):
    B = list(lstB)
    score = 0
    for x in A:
        k = find_gt(B, x)
        if k == None:
            score += 1
            B = B[1:]
        else:
            del B[k]
    return score

def cheat_opt(A, B):
    score = 0
    i = 0
    j = 0
    while i < len(A) and j < len(B):
        if A[i] > B[j]:
            score += 1
            j += 1
        i += 1
    return score
            

        
T = int(raw_input())
for test in range(1, T + 1):
    N = int(raw_input())
    A = []
    B = []
    lstA = raw_input().split(' ')
    lstB = raw_input().split(' ')
    for x in lstA:
        A.append(float(x))
    for x in lstB:
        B.append(float(x))
    A.sort()
    B.sort()

    x = cheat_opt(A, B)
    y = opt(A, B)
    
    print "Case #%d: %d %d" % (test, x, y)
