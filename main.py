from __future__ import division
import numpy as np
import math
import pylab as pl

from equacoes import *
from metodos import *
###############################################################################

mc = MetodosContorno()
problema = Problema2()

M=200

tmax=100.0
theta, v, t= mc.Verlet(problema, M, tmax)


pl.plot(t,theta,'-')

theta2, v2, t2 = mc.RangeKutta4(problema, M, tmax)
pl.plot(t2,theta2,'-')
