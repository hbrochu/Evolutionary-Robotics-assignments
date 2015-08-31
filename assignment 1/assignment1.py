import matplotlib.pyplot as plt
from numpy import *
from pylab import *
from scipy import *
import random
import copy



def MatrixCreate(x,y) :
	v = zeros( [x,y] )
	return v

def MatrixRandomize(v) :
        s = v.size
        a = []
        for i in range(s):
            a.append(random.random())
        return a
def Fitness(v):
        s = len(v)
        x = sum(v[:])
        x = x/s
        return x

def MatrixPerturb(p, prob):
    newP = copy.deepcopy(p)
    s = len(newP)
    for i in range(s):
        if (random.random() < prob):
            newP[i] = random.random()
    return newP

def PlotVectorAsLine(a):
    plt.plot(a)

    
        
parent = MatrixCreate(1,50)
parent = MatrixRandomize(parent)
parentFit = Fitness(parent)
child = MatrixPerturb(parent, 0.05)
fits = []
Genes = MatrixCreate(50,5000)
w = 0
for currentGeneration in range(0,5000):
    ##print currentGeneration, parentFit
    child = MatrixPerturb(parent,0.05)
    childFit = Fitness(child)
    if (childFit > parentFit):
        parent = child
        parentFit = childFit
    fits.append(parentFit)
    for w in range(size(parent)):
           Genes[w][currentGeneration] = parent[w]
PlotVectorAsLine(fits)
plt.show()
#print Genes
imshow(Genes,cmap=cm.gray,aspect='auto',interpolation='nearest')
show()

for i in range(4):
        parent = MatrixCreate(1,50)
        parent = MatrixRandomize(parent)
        parentFit = Fitness(parent)
        child = MatrixPerturb(parent, 0.05)
        fits = []

        for currentGeneration in range(0,5000):
            ##print currentGeneration, parentFit
            child = MatrixPerturb(parent,0.05)
            childFit = Fitness(child)
            if (childFit > parentFit):
                parent = child
                parentFit = childFit
            fits.append(parentFit)
        PlotVectorAsLine(fits)
plt.show()


