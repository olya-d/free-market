# coding: utf-8

import numpy as np
from matplotlib import pyplot as plt
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages


supply = np.loadtxt('supply.txt')
demand = np.loadtxt('demand.txt')
price = np.loadtxt('price.txt')

pp = PdfPages('plots.pdf')

x = np.arange(0, 201, 1)

# price and log of demand
price_line, = plt.plot(x, price)
demand_line, = plt.plot(x, np.log(demand))
plt.legend([price_line, demand_line], ['Average price', 'Log(Demand)'])
plt.title('Average price and logarithm of demand with time')
# plt.show()
pp.savefig()

# supply and demand
supply_line, = plt.plot(x, supply)
demand_line, = plt.plot(x, demand)
plt.legend([supply_line, demand_line], ['Supply', 'Demand'])
plt.title('Supply and demand with time')
# plt.show()
pp.savefig()

pp.close()