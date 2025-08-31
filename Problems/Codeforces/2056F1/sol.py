T = int(input())
for _ in range(T):
    K, M = map(int, input().split())
    N = input()

    def pow(x, y):
        rv = 1
        for c in y[::-1]:
            if c == '1':
                rv *= x
            x *= x
        return rv
    
    fact = [0] * (M + 1)
    fact[0] = 1
    for i in range(1, M + 1):
        fact[i] = fact[i - 1] * i

    def binom(n, k):
        return fact[n] // (fact[n - k] * fact[k])

    seqs = [0] * (M + 1)
    for i in range(1, M + 1):
        if bin(i * (i - 1) // 2)[2:] > N:
            break

        dp = [0] * (i + 1)
        for j in range(1, i + 1):
            dp[j] = pow(j, N) // j ** (i * (i - 1) // 2)
            for k in range(1, j):
                dp[j] -= dp[k] * binom(j, k)

    ans = 0
    for i in range(1, M + 1):
        if seqs[i] // fact[i] % 2 == 1:
            for j in range(M):
                m = (i - 1) // 2
                if binom(j, m) * binom(M - 1 - j, i - 1 - m) % 2 == 1:
                    ans ^= j
    print()
    print(ans)
