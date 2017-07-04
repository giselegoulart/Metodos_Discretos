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
#        if(M==0):
#            print 'divisão por zero'
#        else if(M<0):
#            print 'intervalo inválido'
#        else:
#            contorno1 = problema.contorno_X()[0]
#            contorno2 = problema.contorno_X()[1]
#            h = (xn - x0)/M
#            for i in range()
#            k_1 = h*problema.funcao(contorno1, contorno2) # k_1 = h*problema.funcao(xn, yn)
#            k_2 = h*problema.funcao(xn + (1/2)*h, yn + (1/2)*k_1)
#            k_3 = h*problema.funcao(xn + (1/2)*h, yn + (1/2)*k_2)
#            k_4 = h*problema.funcao(xn + h, yn + k_3)
#            
#            y = yn + (1/6)*(K_1 + 2*k_2 + 2*k_3 + k_4)
        return 0