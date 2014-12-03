# coding: utf-8
import numpy as np
from matplotlib import pyplot as plt
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

import json
from jsoncomment import JsonComment

configuration_file = open('config.json', 'r')
parser = JsonComment(json)
config = parser.loads(configuration_file.read())
configuration_file.close()


supply = np.loadtxt(config['supply_file'])
demand = np.loadtxt(config['demand_file'])
price = np.loadtxt(config['price_file'])

pp = PdfPages('plots.pdf')

x = np.arange(0, config['duration'], 1)

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