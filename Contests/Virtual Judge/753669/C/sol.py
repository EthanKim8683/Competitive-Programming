import math
import sys


def main():
    input_data = sys.stdin.read().strip().split()
    Theta = int(input_data[0])
    N = int(input_data[1])
    d = Theta * math.pi / 180

    ranges = []
    idx = 2
    for _ in range(N):
        X = int(input_data[idx])
        idx += 1
        H = int(input_data[idx])
        idx += 1
        r = X + H / math.tan(d)
        ranges.append((X, r))

    compressed = []
    for l, r in ranges:
        compressed.append(l)
        compressed.append(r)
    compressed = sorted(set(compressed))

    ranges_ = []
    for l, r in ranges:
        l_ = lower_bound(compressed, l)
        r_ = lower_bound(compressed, r)
        ranges_.append((l_, r_))

    ps = [0] * (len(compressed) + 1)
    for l, r in ranges_:
        ps[l] += 1
        ps[r + 1] -= 1

    for i in range(len(compressed)):
        ps[i + 1] += ps[i]

    ans = 0.0
    for i in range(len(compressed) - 1):
        if ps[i] > 0:
            ans += compressed[i + 1] - compressed[i]

    print(f"{ans:.14f}")


def lower_bound(arr, x):
    lo, hi = 0, len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] < x:
            lo = mid + 1
        else:
            hi = mid
    return lo


if __name__ == "__main__":
    main()
