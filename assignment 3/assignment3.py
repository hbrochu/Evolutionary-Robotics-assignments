import matplotlib.pyplot as plt
from numpy import *
from pylab import *
from scipy import *
import random
import copy



def MatrixCreate(x,y) :
	v = zeros( [x,y] )
	return v

def VectorCreate(width) :
	v = zeros(width, dtype='f')
	return v

def MatrixRandomize(v) :
        newV = copy.deepcopy(v)
        s = newV.size
        l = len(newV)
        h = s/l
        for i in range(h):
                for x in range(l):
                        newV[i,x] = random.uniform(-1.0,1.0)
        return newV
def Fitness2(neuronValues):
        diff = 0.0
        for i in range(0,9):
                for j in range(0,9):
                        diff = diff + abs(neuronValues[i,j]-neuronValues[i,j+1])
                        diff = diff + abs(neuronValues[i+1,j]-neuronValues[i,j])
        diff = diff/(2*9*9)
        f = 1 - diff
        return f
def Fitness(distance):
        
        f = 1 - distance
        return f
        

def MatrixPerturb(p, prob):
    newP = copy.deepcopy(p)
    s = newP.size/len(newP)
    #print s
    for i in range(s):
            for x in range(len(newP)):
                if (random.random() < prob):
                    newP[i,x] = random.random()
    return newP

def PlotVectorAsLine(a):
    plt.plot(a)

def Update(parent,neuronValues,i):
        j=0
        for j in range(len(neuronValues[0])):
                temp = 0
                x = 0
                for x in range(len(neuronValues[0])):
                        temp += (parent[j,x]*neuronValues[i-1,x])
                if(temp < 0):
                        temp = 0
                        neuronValues[i,j] = temp
                elif(temp >1):
                        temp = 1
                        neuronValues[i,j] = temp
                else:
                        neuronValues[i,j] = temp


                                
def NeuronUpdate(neuronValues, synapseValues):
        newNeuronValues = copy.deepcopy(neuronValues)
        newSynapseValues = copy.deepcopy(synapseValues)

        height = len(newSynapseValues)
        #print length
        #print newNeuronValues.size
        length = newSynapseValues.size/height
        print length
        print height
        tempMatrix = []
        tempMatrix[:] = []
        i = 0
        for i in range(height):
                x = 0
                for x in range(length):
                        tempMatrix.append(newSynapseValues[i,x])
                #print tempMatrix
                #print newNeuronValues
                newNeuronValues = np.concatenate((newNeuronValues,[tempMatrix]))
                tempMatrix[:] = []


        return newNeuronValues

def MeanDistance(v1,v2):
        sumV1 =  sum(v1)
        sumV2 = sum(v2)
        #print sumV1
        #print sumV2
        #print len(v1)
        #print len(v2)
        d = sum(abs(v2-v1)/10)
        return d               


    
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
##neuronValues = MatrixCreate(50,10)
##p = 0
##for p in range(0,10):
##        rand = random.random()
##        neuronValues[0,p] = rand
###print neuronValues
##                
##neuronPositions = MatrixCreate(2,10)
###print neuronPositions
##angle = 0.0
##numNeurons = 10
##angleUpdate = 2 * pi / numNeurons
##for i in range(0, numNeurons):
##        x = sin(angle)
##        y = cos(angle)
##        angle = angle + angleUpdate
##        neuronPositions[0,i] = x
##        neuronPositions[1,i] = y
####        neuronPositions = np.insert(neuronPositions,0, x)
####        neuronPositions = np.delete(neuronPositions, 9)
####        neuronPositions = np.insert(neuronPositions, 10,y)
####        neuronPositions = np.delete(neuronPositions, 20)
##        
###print neuronPositions
##
##j = 0
##for j in range(0,numNeurons):
##        plt.plot(neuronPositions[0,j],neuronPositions[1,j],'ko',markerfacecolor = [1,1,1],markersize=18)
##
##
###plt.show()
###################################### end of first image
##synapses = MatrixCreate(10,10)
##i = 0
##w = 0
##synapseAmount = len(synapses)
###print synapseAmount
##for i in range(synapseAmount):
##        for w in range(synapseAmount):
##                synapses[i,w] = random.uniform(-1.0,1)
###print synapses
##j = 0
##s = 0
####for j in range(0,numNeurons):
####        for s in range(0,numNeurons):
####                plt.plot([neuronPositions[0,j],neuronPositions[0,s]],[neuronPositions[1,j],neuronPositions[1,s]])
#####plt.show()
###################################### end of second image
##i = 0
##j = 0
####for i in range(synapseAmount):
####        for j in range(synapseAmount):
####                if(synapses[i,j] < 0):
####                        plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [.8,.8,.8])
####                else:
####                        plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [0,0,0])
###plt.show()
######################################end of third image
##i = 0
##j = 0
##for i in range(synapseAmount):
##        #for j in range(synapseAmount):
##                #w = int(10*abs(synapses[i,j]))+1
##                #if(synapses[i,j] < 0):
##                        #plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [.8,.8,.8], linewidth = w)
##                #else:
##                        #plt.plot([neuronPositions[0,i],neuronPositions[0,j]],[neuronPositions[1,i],neuronPositions[1,j]],color = [0,0,0], linewidth = w)
###plt.show()
######################################end of fourth image
##i = 0
##k = 0
##x = 0
##for i in range(50):
##        for x in range(10):
##                neuronValues[i,x] = random.random()
##                neuronValues[i,x] = Update(neuronValues, synapses, i,x)
###print neuronValues
###imshow(neuronValues,cmap=cm.gray,aspect='auto',interpolation='nearest')
###plt.show()

#################################### end assignment 2
numNeurons = 10
numUpdates = 0
parent = MatrixCreate(numNeurons,numNeurons)
#print parent
parent = MatrixRandomize(parent)
#print len(neuronValues)
neuronValues = MatrixCreate(numNeurons,numNeurons)




#print neuronValues
print parent

i = 0
for i in range(0,10):
        neuronValues[0,i] = 0.5
print neuronValues
i = 0
for i in range(numNeurons-1):
        Update(parent, neuronValues, i+1)
print neuronValues
##imshow(neuronValues,cmap=cm.gray,aspect='auto',interpolation='nearest')
##plt.show()

actualNeuronValues = neuronValues[9,:]
print actualNeuronValues
desiredNeuronValues = VectorCreate(10)
j = 0
for j in range(0,10,2):
        desiredNeuronValues[j] = 1
print desiredNeuronValues
distance = MeanDistance(desiredNeuronValues, actualNeuronValues)
parentFitness = Fitness2(neuronValues)
print parentFitness


plt.imshow(neuronValues,cmap=cm.gray,aspect='auto',interpolation='nearest')
plt.show()
fitnessVector = []
for currentGeneration in range(0,1000):
        #print currentGeneration, parentFitness
        child = MatrixPerturb(parent,0.05)
        temp = copy.deepcopy(neuronValues)
        i =0
        for i in range(numNeurons-1):
                Update(child, temp, i+1)
                
        actualNeuronValues = temp[9,:]
        distance = MeanDistance(desiredNeuronValues, actualNeuronValues)
        childFitness = Fitness2(temp)
        #print childFitness

        if ( childFitness > parentFitness):
                 parent = child
                 parentFitness = childFitness
                 neuronValues = temp
        fitnessVector.append(parentFitness)




print neuronValues
plt.imshow(neuronValues,cmap=cm.gray,aspect='auto',interpolation='nearest')
plt.show()
PlotVectorAsLine(fitnessVector)
plt.show()













