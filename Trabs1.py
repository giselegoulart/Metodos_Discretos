# -*- coding: utf-8 -*-
"""
Created on Wed May  3 11:10:14 2017

@author: user
"""

from __future__ import division
import numpy as np
import pylab as pl
from scipy import optimize 

class CrescimentoLog():
    def __init__(self, sup=100):
        self.sup = sup
    
    def F(self,t,y):
        return (1.0-(1.0/self.sup)*y)*y

class Trab1():
    def F(self, t, y):
        return 1 + 2*np.exp(-t)*y - y**3
    def y0(self):
        return 3.0
    
class Trab2():
    def F(self, t, y):
        return 1 - np.sin(y)*(y + t)**2
    def y0(self):
        return 5.0
    
class MetodosDiscretos():
    def EulerExplicito(self, t_0, y_0, k, t_max, F):
        vy = [y_0]
        t = t_0
        
        while t <= t_max:
            vy.append(vy[-1]+k*F(t,vy[-1])) # vk[-1] pega o ultimo da lista
            t+=k
        
        return vy
        
    def EulerImplicito(self, t_0, y_0, k, t_max, F):
        vy = [y_0]
        t = t_0
        
        while t <= t_max:
            # y[i+1] - y[i] - k*F(t, y[i+1]) = 0
            func = lambda y1:y1-vy[-1]-k*F(t, y1) # y1 eh y[i+1]  
            vy.append(optimize.newton(func, vy[-1])) # Resolve o sistema pelo método de Newton
            t+=k
        
        return vy        
    
    def Runge_Kutta4(self, t_0, y_0, k, t_max, F):
        vy = [y_0]
        t = t_0
        
        while(t <= t_max):
            k1 = F(t, vy[-1])
            k2 = F(t, (vy[-1] + (k/2)*k1))
            k3 = F(t, (vy[-1] + (k/2)*k2))
            k4 = F(t, (vy[-1] + k*k3))
            
            vy.append(vy[-1] + (k/6)*(k1 + 2*k2 + 2*k3 + k4))
            
            t+=k
        
        return vy
    
    def Heun(self, t_0, y_0, k, t_max, F):
        vy = [y_0]
        t = t_0
        
        lamb = 1.0/2
        alpha1 = 1 - (1/(2*lamb))
        alpha2 = 1 - alpha1
        
        while(t <= t_max):
            k1 = F(t, vy[-1])
            k2 = F((t + lamb*k), (vy[-1] + lamb*k*k1))
            
            vy.append(vy[-1] + k*(alpha1*k1 + alpha2*k2))
            
            t+=k
        
        return vy
    
    
#problema = CrescimentoLog()
problema = Trab2()
t_0 = 0.0
y_0 = problema.y0()
M = 200
t_max = 5.0   
k = t_max/M

md = MetodosDiscretos()

y = md.EulerImplicito(t_0, y_0, k, t_max, problema.F)
vt = np.linspace(t_0, t_max, len(y))
pl.plot(vt, y, '-', color='blue')

y = md.EulerExplicito(t_0, y_0, 0.01, t_max, problema.F)
vt = np.linspace(t_0, t_max, len(y))
pl.plot(vt, y, '-', color ='red')

y = md.Runge_Kutta4(t_0, y_0, k, t_max, problema.F)
vt = np.linspace(t_0, t_max, len(y))
pl.plot(vt, y, '-', color='green')

y = md.Heun(t_0, y_0, k, t_max, problema.F)
vt = np.linspace(t_0, t_max, len(y))
pl.plot(vt, y, '-', color='pink')

legendas = ['Euler Implicito', 'Euler Explicito', 'Runge Kutta 4', 'Heun']

pl.legend(legendas)

pl.show()