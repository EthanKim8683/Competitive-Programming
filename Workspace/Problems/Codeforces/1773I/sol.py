from types import GeneratorType

# https://codeforces.com/blog/entry/80158?#comment-662130
def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to
    return wrappedfunc

MAXL = 20000
MAXN = 5982

trie = []
trie.append({})
f = 1
t = 1
for n in range(1, MAXN+1):
    f *= n
    s = str(f)
    # s += "0"*(MAXL-len(s))

    a = 0
    for c in s:
        if not c in trie[a]:
            trie[a][c] = t
            t += 1
            trie.append({})
        a = trie[a][c]

print(t)

# max_count = 0
# @bootstrap
# def dfs(a, count):
#     global max_count
#     if len(trie[a]) > 1:
#         count += 1
#     max_count = max(max_count, count)
#     for b in trie[a].values():
#         yield dfs(b, count)
#     yield
# dfs(0, 0)
# print(max_count)
