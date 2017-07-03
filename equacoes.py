from __future__ import division
import numpy as np
import math
import pylab as pl

class Problema1():
    def funcao1(self):
        return 0
    
    def funcao2(self):
        return 0
        
    def contono_X1(self):
        return 0
        
    def contorno_Y1(self):
        return 0
    
    def contorno_X2(self):
        return 0
        
    def contorno_Y2(self):
        return 0
        

class Problema2():
    def __init__(self, g=1, l=1):
        self.g = g
        self.l = l
        
    def funcao(self, t, y):
        #y=[theta,v]
        g=self.g
        l=self.l
        return np.array([-(g/l)*np.sin(y[0])])
       
    def contorno_X(self):
        return np.array([0, 0])
        
    def contorno_Y(self):
        return np.array([np.pi/4, 0])