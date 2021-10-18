#!/usr/bin/env python3

import fileinput
import matplotlib
import matplotlib.pyplot
matplotlib.rcParams['text.usetex'] = True

settings = dict()

xs = []
ys = []
for line in fileinput.input():
    if line[0] == '>':
        values = line[1:].split('=')
        settings[values[0]] = '='.join(values[1:])
    else:
        values = line.split(' ')
        values = [float(x) for x in values]
        xs.append(values[0])
        ys.append(values[1:])

show_legend = False
for i in range(len(ys[0])):
    title_key = 'title-{}'.format(i)
    if title_key in settings:
        matplotlib.pyplot.plot(xs, [t[i] for t in ys], label=settings[title_key])
        show_legend = True
    else:
        matplotlib.pyplot.plot(xs, [t[i] for t in ys])

if show_legend:
    matplotlib.pyplot.legend()

matplotlib.pyplot.title(settings['title'])
matplotlib.pyplot.xlabel(settings['x-axis'])
matplotlib.pyplot.ylabel(settings['y-axis'])

if 'x-min' in settings and 'x-max' in settings:
    matplotlib.pyplot.xlim(float(settings['x-min']), float(settings['x-max']))

if 'y-min' in settings and 'y-max' in settings:
    matplotlib.pyplot.ylim(float(settings['y-min']), float(settings['y-max']))

matplotlib.pyplot.show()