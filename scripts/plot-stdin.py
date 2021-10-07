#!/usr/bin/env python3

import fileinput
import matplotlib.pyplot

settings = dict()

xs = []
ys = []
for line in fileinput.input():
    if line[0] == '>':
        values = line[1:].split('=')
        settings[values[0]] = values[1]
    else:
        values = line.split(' ')
        values = [float(x) for x in values]
        xs.append(values[0])
        ys.append(values[1:])

for i in range(len(ys[0])):
    matplotlib.pyplot.plot(xs, [t[i] for t in ys])

matplotlib.pyplot.title(settings['title'])
matplotlib.pyplot.xlabel(settings['x-axis'])
matplotlib.pyplot.ylabel(settings['y-axis'])
matplotlib.pyplot.xlim(float(settings['x-min']), float(settings['x-max']))
# matplotlib.pyplot.ylim(float(settings['y-min']), float(settings['y-max']))
matplotlib.pyplot.show()