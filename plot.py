# coding: utf-8

import numpy as np
supply = np.loadtxt('supply.txt')
supply
demand = np.loadtxt('demand.txt')
price = np.loadtxt('price.txt')
from matplotlib impot pyplot as plt
import matplotlib.pyplot as plt
plt.plot(price, [i for i in range(1001)])
plt.show()
plt.plot(np.arange(0, 1000, 1), price)
plt.plot(np.arange(0, 1001, 1), price)
plt.show()
price = np.loadtxt('price.txt')
plt.plot(np.arange(0, 10001, 1), price)
plt.show()
price = np.loadtxt('price.txt')
plt.plot(np.arange(0, 201, 1), price)
plt.show()
demand = np.loadtxt('demand.txt')
supply = np.loadtxt('supply.txt')
plt.plot(np.arange(0, 201, 1), price, demand, supply)
plt.show()
x = np.arange(0, 201, 1)
plt.plot(x, price, x, demand, x, supply)
plt.show()
plt.plot(x, price, x, np.log(demand), x, np.log(supply))
plt.plot(x, price, x, np.log(demand))
plt.show()
plt.plot(x, price, x, np.log(demand))
plt.show()
plt.plot(x, supply, x, demand)
plt.show()
