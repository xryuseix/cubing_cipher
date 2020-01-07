import numpy as np
import matplotlib.pyplot as plt

# データを読み込む
train = np.loadtxt('./keylen.csv', delimiter=',', skiprows=1)
train_x = train[:,0]
train_y = train[:,1]

# 範囲指定
plt.xlim(0, 300)
plt.ylim(0, 100)

# 表示
plt.plot(train_x,train_y,'o')
plt.xlabel('Key length (characters)')
plt.ylabel('Transposition rate (%)')
# plt.show()
plt.savefig('figure.png')