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

def Update(v,a,i,x):
        newV = copy.deepcopy(v)
        newA = copy.deepcopy(a)
        j = 0
        temp = 0
        for j in range(0,9):
                temp = temp + newA[x,j]*newV[i,j]
        if(temp < 0):
                temp = 0
        elif(temp >1):
                temp = 1
        return temp
                                
    
################################## assign 1       
##parent = MatrixCreate(1,50)
##parent = MatrixRandomize(parent)
##parentFit = Fitness(parent)
##child = MatrixPerturb(parent, 0.05)
##fits = []
##Genes = MatrixCreate(50,5000)
##w = 0
##for currentGeneration in range(0,5000):
##    ##print currentGeneration, parentFit
##    child = MatrixPerturb(parent,0.05)
##    childFit = Fitness(child)
##    if (childFit > parentFit):
##        parent = child
##        parentFit = childFit
##    fits.append(parentFit)
##    for w in range(size(parent)):
##           Genes[w][currentGeneration] = parent[w]
##PlotVectorAsLine(fits)
###plt.show()
###print Genes
##imshow(Genes,cmap=cm.gray,aspect='auto',interpolation='nearest')
###show()
##
##for i in range(4):
##        parent = MatrixCreate(1,50)
##        parent = MatrixRandomize(parent)
##        parentFit = Fitness(parent)
##        child = MatrixPerturb(parent, 0.05)
##        fits = []
##
##        for currentGeneration in range(0,5000):
##            ##print currentGeneration, parentFit
##            child = MatrixPerturb(parent,0.05)
##            childFit = Fitness(child)
##            if (childFit > parentFit):
##                parent = child
##                parentFit = childFit
##            fits.append(parentFit)
##        PlotVectorAsLine(fits)
###plt.show()
#################################### end assign 1
neuronValues = MatrixCreate(50,10)
p = 0
for p in range(0,10):
        rand = random.random()
        neuronValues[0,p] = rand
#print neuronValues
                
neuronPositions = MatrixCreate(2,10)
print neuronPositions
angle = 0.0
numNeurons = 10
angleUpdate = 2 * pi / numNeurons
for i in range(0, numNeurons):
        x = sin(angle)
        y = cos(angle)
        angle = angle + angleUpdate
        neuronPositions[0,i] = x
        neuronPositions[1,i] = y
##        neuronPositions = np.insert(neuronPositions,0, x)
##        neuronPositions = np.delete(neuronPositions, 9)
##        neuronPositions = np.insert(neuronPositions, 10,y)
##        neuronPositions = np.delete(neuronPositions, 20)
        
#print neuronPositions

j = 0
for j in range(0,numNeurons):
        plt.plot(neuronPositions[0,j],neuronPositions[1,j],'ko',markerfacecolor = [1,1,1],markersize=18)


#plt.show()
#################################### end of first image
synapses = MatrixCreate(10,10)
i = 0
w = 0
synapseAmount = len(synapses)
#print synapseAmount
for i in range(synapseAmount):
        for w in range(synapseAmount):
                synapses[i,w] = random.uniform(-1.0,1)
#print synapses
j = 0
s = 0
##for j in range(0,numNeurons):
##        for s in range(0,numNeurons):
##                plt.plot([neuronPositions[0,j],neuronPositions[0,s]],[neuronPositions[1,j],neuronPositions[1,s]])
###plt.show()
#################################### end of second image
i = 0
j = 0
for i in range(synapseAmount):
        for j in range(synapseAmount):
                if(synapses[i,j] < 0):
                        plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [.8,.8,.8])
                else:
                        plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [0,0,0])
#plt.show()
####################################end of third image
i = 0
j = 0
for i in range(synapseAmount):
        for j in range(synapseAmount):
                w = int(10*abs(synapses[i,j]))+1
                if(synapses[i,j] < 0):
                        plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [.8,.8,.8], linewidth = w)
                else:
                        plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [0,0,0], linewidth = w)
plt.show()
####################################end of fourth image
i = 0
k = 0
x = 0
for i in range(50):
        for x in range(10):
                neuronValues[i,x] = random.random()
                neuronValues[i,x] = Update(neuronValues, synapses, i,x)
print neuronValues
imshow(neuronValues,cmap=cm.gray,aspect='auto',interpolation='nearest')
plt.show()
