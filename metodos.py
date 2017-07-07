from __future__ import division
import numpy as np
import math
import pylab as pl

import equacoes

class MetodosDiscretos():
    def EulerExplicito(self):
        return 0
    
    def RangeKutta2(self):
        return 0
        
    def RangeKutta4(self):
        return 0
        
class MetodosContorno():
    def Verlet(self, problema, M, tmax):
        dt = tmax/M
        
        theta = np.zeros((M+1, 1))
        v = np.zeros((M+1, 1))
        t = np.zeros((M+1, 1))
        
        contorno1 = problema.contorno_X()[0]
        contorno2 = problema.contorno_X()[1]
        theta[contorno1] = problema.contorno_Y()[0]
        v[contorno2] = problema.contorno_Y()[1]
        t[0] = 0
        
        # Consideramos a aceleracao constante entre os instantes t0 e t1 para
        # calcular theta[2] e conseguir aplicar Verlet.
        theta[1] = theta[0]+v[0]*dt+(1./2)*problema.funcao(t[0],theta[0])*dt**2
        t[1] = dt
        i=1
        for i in range(1,len(t)-1):
            theta[i+1] = problema.funcao(t[i],theta[i])[0]*dt**2+2*theta[i]-theta[i-1]
            v[i] = (theta[i+1]-theta[i-1])/(2*dt)
            t[i+1] = t[i]+dt
        v[i+1] = v[i]
        return theta,v,t
        
    def RangeKutta4(self, problema, M, tmax): #DUVIDAAAS
        h = tmax/M
        
        theta = np.zeros((M+1, 1))
        v = np.zeros((M+1, 1))
        t = np.zeros((M+1, 1))
        
        contorno1 = problema.contorno_X()[0]
        contorno2 = problema.contorno_X()[1]
        theta[contorno1] = problema.contorno_Y()[0]
        v[contorno2] = problema.contorno_Y()[1]
        t[0] = 0
        for i in range(0,len(t)-1):
            w1 = problema.funcao(t[i], theta[i])
            w2 = problema.funcao(t[i], theta[i] + (h/2)*w1)
            w3 = problema.funcao(t[i], theta[i] + (h/2)*w2)
            w4 = problema.funcao(t[i], theta[i] + (h)*w3)

            theta1 = v[i] 
            theta2 = v[i] + (h/2)*theta1
            theta3 = v[i] + (h/2)*theta2
            theta4 = v[i] + (h)*theta3
            
            v[i+1] = v[i] + (h/6)*(w1 + 2*w2 + 2*w3 + w4)
            theta[i+1] = theta[i] + (h/6)*(theta1 + 2*theta2 + 2*theta3 + theta4)
            t[i+1] = t[i]+h
            
        return theta, v, t