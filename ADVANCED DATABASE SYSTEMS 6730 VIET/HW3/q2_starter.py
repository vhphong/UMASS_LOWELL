import snap
import random
import itertools
import math
from itertools import combinations
from collections import OrderedDict
import time

# Problem 2.1 Functions
def loadSigns(filename):
    """
    :param - filename: undirected graph with associated edge sign

    return type: dictionary (key = node pair (a,b), value = sign)
    return: Return sign associated with node pairs. Both pairs, (a,b) and (b,a)
    are stored as keys. Self-edges are NOT included.
    """
    signs = {}
    i = 0
    with open(filename, 'r') as ipfile:
        for line in ipfile:
            if line[0] != '#':
                line_arr = line.split()
                if line_arr[0] == line_arr[1]:
    				continue
                node1 = int(line_arr[0])
                node2 = int(line_arr[1])
                sign = int(line_arr[2])
                signs[(node1, node2)] = sign
                signs[(node2, node1)] = sign
                i += 1
    return signs


def determine_triad_type(triad, triad_count, signs):
    """
    :param triad: list of 3 connected nodes
    :param triad_count:
    :param signs: Dictionary of signs (key = node pair (a,b), value = sign)
    :return: type: List, each position representing count of t0, t1, t2, and t3, respectively.
    return: Return the counts for t0, t1, t2, and t3 triad types. Count each triad
    only once and do not count self edges.
    """
    triad_comb = (list(combinations(triad, 2)))
    balance_index = 0
    for val in triad_comb:
        if signs[val] > 0:
            balance_index += 1
        else:
            balance_index -= 1
    if balance_index == 3:
        triad_count[3] += 1
    if balance_index == 1:
        triad_count[2] += 1
    if balance_index == -1:
        triad_count[1] += 1
    if balance_index == -3:
        triad_count[0] += 1
    return triad_count


def computeTriadCounts(G, signs):
    """
    :param - G: graph
    :param - signs: Dictionary of signs (key = node pair (a,b), value = sign)

    return type: List, each position representing count of t0, t1, t2, and t3, respectively.
    return: Return the counts for t0, t1, t2, and t3 triad types. Count each triad
    only once and do not count self edges.
    """
    triad_count = [0, 0, 0, 0]
    # each position represents count of t0, t1, t2, t3, respectively
    ############################################################################
    # TODO: Your code here!
    triad_set = set()
    for NI in G.Nodes():
        if NI.GetOutDeg() > 1:
            out_degree_list = []
            for j in range((NI.GetOutDeg())):
                out_degree_list.append(NI.GetOutNId(j))
            neighbor_node_pair = (list(combinations(out_degree_list, 2)))
            for item in neighbor_node_pair:
                if G.IsEdge(item[0], item[1]) is True:
                    if NI.GetId() != item[0] and NI.GetId() != item[1] and item[0] != item[1]:
                        triad = [NI.GetId(), item[0], item[1]]
                        triad.sort()
                        triad = tuple(triad)
                        if triad not in triad_set:
                            # unique triad
                            triad_set.add(triad)
                            triad_count = determine_triad_type(triad, triad_count, signs)
    ############################################################################
    return triad_count


def get_triad_set(G):
    """
    :param G: graph
    :return: set of existing triad in graph
    """
    triad_set = set()
    for NI in G.Nodes():
        if NI.GetOutDeg() > 1:
            out_degree_list = []
            for j in range((NI.GetOutDeg())):
                out_degree_list.append(NI.GetOutNId(j))
            neighbor_node_pair = (list(combinations(out_degree_list, 2)))
            for item in neighbor_node_pair:
                if G.IsEdge(item[0], item[1]) is True:
                    if NI.GetId() != item[0] and NI.GetId() != item[1] and item[0] != item[1]:
                        triad = [NI.GetId(), item[0], item[1]]
                        triad.sort()
                        triad = tuple(triad)
                        if triad not in triad_set:
                            # unique triad
                            triad_set.add(triad)
    return triad_set


def optimalTriadCount(graph):
    i = 0
    triad_set = []
    triad = []
    for NI in graph.Nodes():
        if NI.GetOutDeg() > 1:
            for j in range((NI.GetOutDeg())):
                if graph.GetNI((NI.GetOutNId(j))).GetOutDeg() > 1:
                    # print(NI.GetId(), NI.GetOutNId(j))
                    Nbrs = snap.TIntV()
                    snap.GetCmnNbrs(graph, NI.GetId(), NI.GetOutNId(j), Nbrs)
                    if 2 > len(Nbrs) > 0:
                        triad.append(Nbrs[0])
                        triad.append(NI.GetId())
                        triad.append(NI.GetOutNId(j))
                        triad.sort()
                        if triad not in triad_set:
                            triad_set.append(triad)
                        triad = []
    print(len(triad_set))
    return triad_set


def displayStats(G, signs):
    '''
    :param - G: graph
    :param - signs: Dictionary of signs (key = node pair (a,b), value = sign)

    Computes and prints the fraction of positive edges and negative edges,
        and the probability of each type of triad.
    '''
    fracPos = 0
    fracNeg = 0
    probs = [0,0,0,0]

    ############################################################################
    # TODO: Your code here! (Note: you may not need both input parameters)
    positive_count = 0
    for EI in G.Edges():
        if signs[EI.GetSrcNId(), EI.GetDstNId()] > 0:
            positive_count += 1
    fracPos = positive_count / float(G.GetEdges())
    fracNeg = 1 - fracPos
    probs[0] = math.pow(fracNeg, 3)
    probs[3] = math.pow(fracPos, 3)
    probs[1] = fracPos * math.pow(fracNeg, 2) * 3
    probs[2] = fracNeg * math.pow(fracPos, 2) * 3
    ############################################################################

    print 'Fraction of Positive Edges: %0.4f' % (fracPos)
    print 'Fraction of Negative Edges: %0.4f' % (fracNeg)

    for i in range(4):
        print "Probability of Triad t%d: %0.4f" % (i, probs[i])


# Problem 2.4 Functions
def createCompleteNetwork(networkSize):
    """
    :param - networkSize: Desired number of nodes in network

    return type: Graph
    return: Returns complete network on networkSize
    """
    completeNetwork = None
    ############################################################################
    # TODO: Your code here!
    completeNetwork = snap.GenFull(snap.PUNGraph, networkSize)
    ############################################################################
    return completeNetwork


def assignRandomSigns(G):
    """
    :param - G: Graph

    return type: dictionary (key = node pair (a,b), value = sign)
    return: For each edge, a sign (+, -) is chosen at random (p = 1/2).
    """
    signs = {}
    ############################################################################
    # TODO: Your code here!
    sign_list = [-1, 1]
    for EI in G.Edges():
        sign = random.sample(sign_list, 1)
        signs[EI.GetSrcNId(), EI.GetDstNId()] = sign
        signs[EI.GetDstNId(), EI.GetSrcNId()] = sign
    ############################################################################
    return signs


def get_random_edge(G):
    """
    :param G: Graph

    :return: src and dst node ID of a random edge
    """
    rnd_seed = snap.TRnd(G.GetNodes() + 1)
    rnd_seed.Randomize()
    random_ni = G.GetNI(G.GetRndNId(rnd_seed))
    random_id = random_ni.GetId()
    # get random node
    rnd = random.randint(0, random_ni.GetOutDeg() - 1)
    # select random number between 0 and out-deg of node
    return random_id, random_ni.GetOutNId(rnd)


def runDynamicProcess(G, signs, num_iterations):
    """
    :param - G: Graph
    :param - signs: Dictionary of signs (key = node pair (a,b), value = sign)
    :param - num_iterations: number of iterations to run dynamic process

    Runs the dynamic process described in problem 2.3 for num_iterations iterations.
    """
    ############################################################################
    # TODO: Your code here!
    for i in range(num_iterations):
        src, dst = get_random_edge(G)
        signs[src, dst] *= -1
        signs[dst, src] *= -1
    ############################################################################


def get_balance_index(triad, signs):
    triad_comb = (list(combinations(triad, 2)))
    balance_index = 0
    for val in triad_comb:
        if signs[val] > 0:
            balance_index += 1
        else:
            balance_index -= 1
    return balance_index


def isBalancedNetwork(G, signs):
    """
    :param - G: Graph
    :param - signs: Dictionary of signs (key = node pair (a,b), value = sign)

    return type: Boolean
    return: Returns whether G is balanced (True) or not (False).
    """
    isBalanced = False
    ############################################################################
    # TODO: Your code here!
    triad_set = get_triad_set(G)
    for item in triad_set:
        # + + + or - - + triad (1 + 1 + 1 or - 1 - 1 + 1)
        if get_balance_index(item, signs) != -1 or get_balance_index(item, signs) != 3:
            return True
    ############################################################################
    return isBalanced


def computeNumBalancedNetworks(numSimulations):
    """
    :param - numSimulations: number of simulations to run

    return type: Integer
    return: Returns number of networks that end up balanced.
    """
    numBalancedNetworks = 0

    for iteration in range(0, numSimulations):
        # (I) Create complete network on 10 nodes
        simulationNetwork = createCompleteNetwork(10)

        # (II) For each edge, choose a sign (+,-) at random (p = 1/2)
        signs = assignRandomSigns(simulationNetwork)

        # (III) Run dynamic process
        num_iterations = 1000000
        runDynamicProcess(simulationNetwork, signs, num_iterations)

        # determine whether network is balanced
        if isBalancedNetwork(simulationNetwork, signs):
            numBalancedNetworks += 1
        if numBalancedNetworks == numSimulations:
            break

    return numBalancedNetworks


def main():
    filename = "epinions-signed.txt"

    # load Graph and Signs
    epinionsNetwork = snap.LoadEdgeList(snap.PUNGraph, filename, 0, 1)
    signs = loadSigns(filename)
    snap.DelSelfEdges(epinionsNetwork)
    # Compute Triad Counts
    # start_time = time.time()
    # triad_count = computeTriadCounts(epinionsNetwork, signs)
    # print("--- %s seconds ---" % (time.time() - start_time))
    # # Problem 2.1a
    # print "Problem 2.1a"
    # for i in range(4):
    #     print "Count of Triad t%d: %d" % (i, triad_count[i])
    #
    # total_triads = float(sum(triad_count)) if sum(triad_count) != 0 else 1
    # for i in range(4):
    #     print "Fraction of Triad t%d: %0.4f" % (i, triad_count[i]/total_triads)

    # Problem 2.1b
    # print "Problem 2.1b"
    # displayStats(epinionsNetwork, signs)
    # Problem 2.4
    start_time = time.time()
    print "Problem 2.4"
    networkSize = 10
    numSimulations = 100
    numBalancedNetworks = computeNumBalancedNetworks(numSimulations)
    print("--- %s seconds ---" % (time.time() - start_time))
    print "Fraction of Balanced Networks: %0.4f" % (float(numBalancedNetworks)/float(numSimulations))

if __name__ == '__main__':
    main()
