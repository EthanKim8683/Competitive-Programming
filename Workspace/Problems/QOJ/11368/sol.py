# translated from sol.cpp

import sys


def main():
    sys.setrecursionlimit(10**7)

    LOGV = 60
    INF = 2 * 10**18

    input = sys.stdin.readline

    N, K = map(int, input().split())
    V = list(map(int, input().split()))

    def trim(V):
        return [e for e in V if e != 0]

    def brute(V):
        V = sorted(V)
        for i in range(len(V) - 1):
            V[i + 1] -= V[i]
        return trim(V)

    k = 0
    while k < K and len(V) > LOGV:
        V = brute(V)
        k += 1

    def binom(n, k):
        # exact integer binomial coefficient
        if k < 0 or k > n:
            return 0
        k = min(k, n - k)
        rv = 1
        for i in range(1, k + 1):
            rv = rv * (n - k + i) // i
        return rv

    def skip(V, k):
        if k == 0:
            return V
        V = sorted(V)
        rv = V[:]
        n = len(V)
        for i in range(n):
            for j in range(i + 1, n):
                sign = 1 if (j - i) % 2 == 0 else -1
                rv[j] += V[i] * binom(k - 1 + j - i, j - i) * sign
        return rv

    def safe(V):
        d = INF
        for i in range(len(V) - 1):
            if V[i] == 0:
                continue
            d = min(d, V[i + 1] // V[i])
        if d == INF:
            return INF

        def check(V2):
            for i in range(len(V2) - 1):
                if V2[i] > V2[i + 1]:
                    return False
            return True

        l, r = 0, d
        while l < r:
            m = l + (r - l + 1) // 2
            if check(skip(V, m)):
                l = m
            else:
                r = m - 1
        return l + 1

    while k < K:
        dk = min(safe(V), K - k)
        V = skip(V, dk)
        k += dk

    # output
    zeros = N - len(V)
    result = [0] * zeros + V
    print(*result)


if __name__ == "__main__":
    main()
