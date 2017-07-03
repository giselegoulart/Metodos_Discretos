from __future__ import division
import numpy as np
import math
import pylab as pl

import equacoes
import metodos
###############################################################################

mc = MetodosContorno()
problema = Problema2()

M=200

tmax=100.0
theta, v, t= mc.Verlet(problema, M, tmax)


pl.plot(t,theta,'-')
