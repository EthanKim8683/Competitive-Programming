import re

N = int(input())

for _ in range(N):
    S = input()

    S = re.sub(r"c(?=[aou]|[^aeiouhy]|$)", "!", S)
    S = re.sub(r"c(?=[eiy])", "@", S)
    S = re.sub(r"ch", "#", S)

    S = re.sub("!", "k", S)
    S = re.sub("@", "s", S)
    S = re.sub("#", "c", S)

    print(S)
