# -*- coding: utf-8 -*-
"""
Created on Wed Jun  7 10:33:38 2017

@author: gisele
"""

from __future__ import division
import numpy as np
import pylab as pl
from scipy import optimize 

class contorno1:
    def p(self, x):
      return -100*x**2  
    def q(self, x):
      return -100
    def f(self, x):
       return 0
    def contornoX(self):
       return ([0.0,1.0])
    def contornoY(self):
       return ([1.0,1.0])
    
class upwind:
    def solucao(self, m, h, edo):
      p = edo.p
      q = edo.q
      f = edo.f
      A = np.zeros([m+1,m+1])
      Z = np.zeros(m+1)
      y = np.zeros(m+1)
      t = np.zeros(m+1)
        
      contornoX = edo.contornoX()
      contornoY = edo.contornoY()
      
      # primeira linha
      if(p(0)>0):
        A[0][0] = -2 +  h**2*q(contornoX[0]) - p(contornoX[0])*h
        A[0][1] = 1 + p(contornoX[0])*h
        Z[0] = h**2*f(contornoX[0]) - contornoY[0]*(1+p(contornoX[0])*h) 
      else:
        A[0][0] = -2 +  h**2*q(contornoX[0]) + p(contornoX[0])*h
        A[0][1] = 1 
        Z[0] = h**2*f(contornoX[0]) - contornoY[0]*1 
      t[0] = 0
      # ultima linha
      if(p(0)>0):
        A[m][m-1] = 1 
        A[m][m] = -2 + h**2*q(contornoX[1]) - p(contornoX[1])*h
        Z[m] = h**2*f(contornoX[1]) - contornoY[1]*(1+p(contornoX[1])*h)
      else:
        A[m][m-1] = 1 + p(contornoX[1])*h
        A[m][m] = -2 + h**2*q(contornoX[1]) + p(contornoX[1])*h
        Z[m] = h**2*f(contornoX[1]) - contornoY[1]*1
      t[m] = 1
      # linhas centrais
      
      for i in range(1,m):
        if (p(h*i)>0):
          A[i][i-1] = 1
          A[i][i] = -2 + h**2*q(h*i) - p(h*i)*h
          A[i][i+1] = 1 + p(h*i)*h   
        else:
          A[i][i-1] = 1 + p(h*i)*h
          A[i][i] = -2 + h**2*q(h*i) + p(h*i)*h
          A[i][i+1] = 1 
        
        Z[i] = h**2*f(h*i)
        t[i] = h*i
        
      y = np.linalg.solve(A,Z)
      return t,y
        
        
########################################################################

m = 20000
h = 1.0/m

problema = contorno1()
metodo = upwind()
t,solucao = metodo.solucao(m,h,problema)
#pl.xlim(1,1.1)
#pl.ylim(1,1.1)
pl.plot(t,solucao)
      