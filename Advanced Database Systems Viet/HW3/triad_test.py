import snap
import random
import itertools
from itertools import combinations
from collections import OrderedDict
import time


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
    i = 0
    triad_set = []
    triad = []
    for NI in G.Nodes():
        # if i > 5:
        #     break
        # i += 1
        if NI.GetOutDeg() > 1:
            out_degree_list = []
            for j in range((NI.GetOutDeg())):
                out_degree_list.append(NI.GetOutNId(j))
            k = 0
            neighbor_node_pair = []
            while k < len(out_degree_list)-1:
                neighbor_node_pair.append((out_degree_list[k], out_degree_list[k+1]))
                k += 1
            for item in neighbor_node_pair:

                if G.IsEdge(item[0], item[1]) is True:
                    if NI.GetId() != item[0] and NI.GetId() != item[1] and item[0] != item[1]:
                        triad.append(NI.GetId())
                        triad.append(item[0])
                        triad.append(item[1])
                        triad.sort()
                        if triad not in triad_set:
                            triad_set.append(triad)
                        triad = []
    # triad_list = map(list, set(map(tuple, triad_list)))
    #     edge_pair = list(combinations(item, 2))
    #     for key in signs.items():
    print(len(triad_set))


    ############################################################################
    return triad_count


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
                        triad = [Nbrs[0], NI.GetId(), NI.GetOutNId(j)]
                        triad.sort()
                        if triad not in triad_set:
                            triad_set.append(triad)
                            print(len(triad_set))
                        triad = []
    # print(triad_set)
    print(len(triad_set))


def main():
    start_time = time.time()

    graph = snap.GenRndGnm(snap.PUNGraph, 8, 0)
    # graph.AddEdge(1,3)
    # graph.AddEdge(1,2)
    # graph.AddEdge(1,5)
    # graph.AddEdge(2,3)
    # graph.AddEdge(2,4)
    # graph.AddEdge(2,5)
    # graph.AddEdge(6,3)
    # graph.AddEdge(6,7)
    # graph.AddEdge(7,3)

    # graph.AddEdge(0,1)
    # graph.AddEdge(0,2)
    # graph.AddEdge(0,3)
    # graph.AddEdge(2,1)
    # graph.AddEdge(2,3)
    filename = "epinions-signed.txt"
    # load Graph and Signs
    epinionsNetwork = snap.LoadEdgeList(snap.PUNGraph, filename, 0, 1)
    snap.DelSelfEdges(epinionsNetwork)
    print("snap")
    print(snap.GetTriads(epinionsNetwork))
    print("--- %s seconds ---" % (time.time() - start_time))
    signs = 0
    # Nbrs = snap.TIntV()
    #
    # snap.GetCmnNbrs(graph, 0, 1, Nbrs)
    # if 2 > len(Nbrs) > 0:
    #     print(0,Nbrs[0],1)
    # print(len(Nbrs))
    # computeTriadCounts(graph, signs)
    start_time = time.time()
    print("computeTriadCounts")
    optimalTriadCount(epinionsNetwork)
    print("--- %s seconds ---" % (time.time() - start_time))


if __name__ == '__main__':
    main()
