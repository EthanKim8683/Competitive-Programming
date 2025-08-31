import matplotlib.pyplot as plt

X, Y = [], []
while True:
    try:
        x, y = map(float, input().split())
        X.append(x)
        Y.append(y)
    except:
        break

plt.scatter(X, Y)
plt.show()
