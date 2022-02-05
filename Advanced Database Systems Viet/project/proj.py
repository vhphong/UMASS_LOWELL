#!/usr/bin/python
#
###############################################################
# To generate 2 random network.  Graph these and collaboration
#	network and compare the difference.  Calculate Degre
#	Distribution and plot the graph.  Calculate  Excess
#	Degree Distribution and plot the graph.  Compare the
#	difference between two graphs.  Calculate expected
#	excess degree and expected degree.  Calculate clustering
#	coefficient.
# 
# To load Epinions and Email network from file into directed graph.
#	Calculate node position of specified node IDs using
#	bfstree fuction.  Pick 100 random nodes from each graph
#	and generate forward and backward bfstree graphs.  Plot
#	cummulative distributions of the nodes.  Calculate nodes
#	in SCC, IN, OUT, TENDRILS, DISCONNECTED from graphs.
#
#  Name:	Tuyen Nguyen
#  Course:	Advanced Database Systems
#  Number:	COMP6730
#  Professor:	Tingjian Ge
#  Project:	CEFL Hill-Climbing Algorithm Implementation
#
###############################################################
import snap
import matplotlib.pyplot as plt
import numpy as np
from collections import OrderedDict
from random import *

# Setup
Nodes = 12008
RandomEdges = 8000
smallWorld = None
collabNet = None


# Problem 1, 2, 3

def genCircle(N):
    """
    :param - N: number of nodes

    return type: snap.PNGraph
    return: Circle graph with N nodes and N edges. Imagine the nodes form a
        circle 
    """
    ############################################################################
    # TODO: Your code here!

    Graph = snap.PNGraph.New()
    for i in range(1, N+1):
     Graph.AddNode(i)
    for i in range(1, N):
     Graph.AddEdge(i, i+1)
    Graph.AddEdge(N, 1)

    ############################################################################
    return Graph


def connectNbrOfNbr(Graph):
    """
    :param - Graph: snap.PNGraph object representing a circle graph on N nodes

    return type: snap.PNGraph
    return: Graph object with additional N edges added by connecting each node
        to the neighbors of its neighbors
    """
    ############################################################################
    # TODO: Your code here!

    N = Graph.GetNodes()
    for i in range(1, N-1):
      Graph.AddEdge(i, i+2)
    Graph.AddEdge(N-1, 1)
    Graph.AddEdge(N, 2)

    ############################################################################
    return Graph


def connectRandomNodes(Graph, RE):
    """
    :param - Graph: snap.PNGraph object representing an undirected graph
    :param - RE: number of random edges to be added

    return type: snap.PNGraph
    return: Graph object with additional RE edges added by connecting RE randomly
        selected pairs of nodes not already connected.
    """
    ############################################################################
    # TODO: Your code here!

    N = Graph.GetNodes()
    for i in range(0, RE):
     nodeFrom = randint(1, N)
     nodeTo = randint(1, N)
     while Graph.IsEdge(nodeFrom, nodeTo) or nodeFrom==nodeTo:
      nodeFrom = randint(1, N)
      nodeTo = randint(1, N)
     Graph.AddEdge(nodeFrom, nodeTo)
     

    ############################################################################
    return Graph


def genSmallWorld(N,RE):
    """
    :param - N: number of nodes
    :param - RE: number of edges

    return type: snap.PNGraph
    return: Small-World graph with N nodes and E edges
    """
    Graph = genCircle(Nodes)
    Graph = connectNbrOfNbr(Graph)
    Graph = connectRandomNodes(Graph, RE)
    return Graph


def loadCollabNet(path):
    """
    :param - path: path to edge list file

    return type: snap.PNGraph
    return: Graph loaded from edge list at `path and self edges removed

    Do not forget to remove the self edges!
    """
    ############################################################################
    # TODO: Your code here!

    Graph = snap.LoadEdgeList(snap.PNGraph, path, 0, 1)
    snap.DelSelfEdges(Graph)

    ############################################################################
    return Graph


def getDataPointsToPlot(Graph):
    """
    :param - Graph: snap.PUNGraph object representing an undirected graph
    
    return values:
    X: list of degrees
    Y: list of frequencies: Y[i] = fraction of nodes with degree X[i]
    """
    ############################################################################
    # TODO: Your code here!

    X, Y = [], []
    N = Graph.GetNodes()
    DegToCntV = snap.TIntPrV()
    snap.GetDegCnt(Graph, DegToCntV)
    DegToCntV.Sort(True)
    for item in DegToCntV:
     X.append(item.GetVal1())
     Y.append(float(item.GetVal2())/float(N))

    ############################################################################
    return X, Y


def Q1_2_3():
    """
    Code for Project Q1, Q2, Q3
    """
    global smallWorld, collabNet
    smallWorld = genSmallWorld(Nodes,RandomEdges)
    collabNet = loadCollabNet("ca-HepPh.txt")

    x_smallWorld, y_smallWorld = getDataPointsToPlot(smallWorld)
    x_collabNet, y_collabNet = getDataPointsToPlot(collabNet)

    plt.loglog(x_smallWorld, y_smallWorld, linestyle = 'dashed', color = 'r', label = 'Small World Network')
    plt.loglog(x_collabNet, y_collabNet, linestyle = 'dotted', color = 'b', label = 'Collaboration Network')
    plt.xlabel('Node Degree (log)')
    plt.ylabel('Proportion of Nodes with a Given Degree (log)')
    plt.title('Degree Distribution of Small World, and Collaboration Networks')
    plt.legend()
    plt.show()


# Execute code for Q1, Q2, Q3
Q1_2_3()


# Find max degree of all 3 graphs for plotting (add 2 for padding)
maxdeg = max([smallWorld.GetNI((snap.GetMxDegNId(smallWorld))).GetDeg(),
               collabNet.GetNI((snap.GetMxDegNId(collabNet))).GetDeg()]) + 2


# Problem 4 - Clustering Coefficient

def calcClusteringCoefficient(Graph):
    """
    :param - Graph: snap.PUNGraph object representing an undirected graph

    return type: float
    returns: clustering coeffient of `Graph 
    """    
    ############################################################################
    # TODO: Your code here!
    C = 0.0

    C = 0.0
    N = Graph.GetNodes()
    for NI in Graph.Nodes():
     k = NI.GetDeg()
     triad = 0.0
     for i in range(k-1):
      for j in range(i+1, k):
       print NI.GetOutNId(i), NI.GetOutNId(j)
       if( Graph.IsEdge(NI.GetOutNId(i), NI.GetOutNId(j)) ):
        triad += 1.0
     if( k >= 2 ):
      C += 2.0 * triad / ( k * (k-1) )
    C /= N

    ############################################################################
    return C

def Q4():
    """
    Code for Q4
    """
   # C_smallWorld = calcClusteringCoefficient(smallWorld)
   # C_collabNet = calcClusteringCoefficient(collabNet)
    C_smallWorld = snap.GetClustCf(smallWorld,-1)
    C_collabNet = snap.GetClustCf(collabNet,-1)
    
    print('Clustering Coefficient for Small World Network: %f' % C_smallWorld)
    print('Clustering Coefficient for Collaboration Network: %f' % C_collabNet)
    print


# Execute code for Q4
#Q4()

#
#  Starting code for Q5_6
#

def HeuDegreeCentrality(Graph, k):
    """
    :param - Graph: snap.PNGraph object representing a directed graph
    :param - k:  number of initial nodes to pick 

    return type: S: array of k highest degree nodes

    """
    ############################################################################
    # TODO: Your code here!

    N = Graph.GetMxNId()
    S = []
    listDeg = [0 for i in range(N+1)]
    OutDegV = snap.TIntPrV()
    snap.GetNodeOutDegV(Graph, OutDegV)
    for nodeDeg in OutDegV:
     listDeg[nodeDeg.GetVal1()] = nodeDeg.GetVal2()
    OutDeg = max(listDeg)
    while ( len(S)<k ):
     for node in range(N+1):
      if listDeg[node]==OutDeg:
       S.append(node)
       if ( len(S)==k ):
        break
     OutDeg -= 1

    ############################################################################

    return S

def HeuRandomNode(Graph, k):
    """
    :param - Graph: snap.PNGraph object representing a directed graph
    :param - k:  number of initial nodes to pick 

    return type: S: array of k nodes randomly pick from Graph

    """
    ############################################################################
    # TODO: Your code here!

    S = []
    N = Graph.GetMxNId()
    Rnd = snap.TRnd(N)
    Rnd.Randomize()
    for i in range(k):
     NId = Graph.GetRndNId(Rnd)
     while ( NId in S ):
      NId = Graph.GetRndNId(Rnd)
     S.append(NId)

    ############################################################################
    return S

def GetInfluence(Graph, S):
    """
    :param - Graph: snap.PNGraph object representing a directed graph
    :param - S: list of nodes

    return type: numInf: number of nodes that S influence

    """
    ############################################################################
    # TODO: Your code here!
    numInf = 0

    ############################################################################
    return numInf

def HeuCELF(Graph, k, p):
    """
    :param - Graph: snap.PNGraph object representing a directed graph
    :param - k:  number of initial nodes to pick 

    return type: S: array of k nodes have most influence

    """
    ############################################################################
    # TODO: Your code here!

    #N = Graph.GetMxNId()
    S = []
    newS = []
    Q = OrderedDict()
    mFlag = [0 for i in range(N+1)]
    for NId in Graph.Nodes():
        NI = NId.GetId()
        mGain = IndependentCascade(Graph,[NI], p)
        Q[NI] = mGain
    Q = OrderedDict(sorted(Q.items(), key=lambda (k,v):(v,k), reverse=True))
    while len(S) < k:
        NI, mGain = Q.keys()[0], Q.values()[0]
        if mFlag[NI] == len(S):
            S.append(NI)
            Q.popitem()
        else:
            newS = S
            newS.append(NI)
            mGain = IndependentCascade(Graph, newS, p) - IndependentCascade(Graph, S, p)
            Q = OrderedDict(sorted(Q.items(), key=lambda (k, v): (v, k), reverse=True))

    ############################################################################
    return S

def IndependentCascade(Graph, SeedNodes, p):
    """
    :param - Graph: snap.PNGraph object representing a directed graph
    :param - SeedNodes: list object represent init nodes
    :param - p: probability of node

    return type: len(S) - number of active nodes

    """
    ############################################################################
    # TODO: Your code here!

    S = set()
    activeNodes = SeedNodes
    visitNodes = set()
    while activeNodes:
      u = activeNodes.pop(0)
      S.add(u)
      visitNodes.add(u)
      uNI = Graph.GetNI(u)
      uOutDeg = uNI.GetOutDeg()
      for i in range(uOutDeg):
       v = uNI.GetOutNId(i)
       if ( v in visitNodes ):
        continue
       visitNodes.add(v)
       pe = random()
       if ( pe >= p ):
        continue
       if ( v not in S ):
        activeNodes.append(v)
    ############################################################################
    return len(S)

def plotHeuristic(Graph,k,p):
    """
    :param - Graph: snap.PNGraph object representing a directed graph
    :param - k: integer represent target size
    :param - p: node probability

    """
    DegCentrality  = [i for i in range(k+1)]
    RandomNode = [i for i in range(k+1)]
    CELF = [i for i in range(k+1)]

    DegCentrality[0] = 0
    RandomNode[0] = 0
    # init_nodesCELF = HeuCELF(Graph, 5, p)
    # CELF[i] = IndependentCascade(Graph, init_nodesCELF, p)
    for i in range(int(p)):
        init_nodesDegCentrality = HeuDegreeCentrality(Graph, i)
        DegCentrality[i] = IndependentCascade(Graph, init_nodesDegCentrality, p)
    plt.plot(range(k+1), DegCentrality, linestyle = 'dashed', color = 'r', label = 'Highest Degree')
    #plt.plot(range(k+1), RandomNode, linestyle = 'dotted', color = 'b', label = 'Random')
    #plt.plot(range(k+1), CELF, linestyle = '-', color = 'm', label = 'CELF')
    plt.xlabel('target on size K')
    plt.ylabel('f(Sk) active set size')
    plt.title('Graph with different heuristics')
    plt.legend()
    plt.show()


def Q5_6():
    """
    Code for Q5_6
    """
    p = 0.01
    targetSize = 5
#    plotHeuristic(smallWorld,targetSize,p)
    plotHeuristic(collabNet,targetSize,p)


# Execute code for Q5_6
Q5_6()
