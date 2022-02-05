import hw4
import sys
import snap
from heapq import heappush


def get_highest_degree_node(graph):
    node_heap = []
    # use max-heap to get nodes with highest degree centrality
    OutDegV = snap.TIntPrV()
    snap.GetNodeOutDegV(graph, OutDegV)
    for item in OutDegV:
        heappush(node_heap, (item.GetVal2(), item.GetVal1()))
    return node_heap[len(node_heap)-1][1]

def Q1_3_a(graph):
    V = set()
    for NI in graph.Nodes():
        V.add(NI.GetId())
    I = set()
    I.add(get_highest_degree_node(graph))
    running_total = 0
    for i in range(10):
        recovered_nodes = hw4.SIR_Model(graph, V.copy(), I.copy())
        running_total += (float(len(recovered_nodes)) / len(V) * 100)
    return running_total / 10


def Q1_3(graph):
    V = set()
    for NI in graph.Nodes():
        V.add(NI.GetId())
    I = set()
    I.add(get_highest_degree_node(graph))
    e = 0
    conditioned_running_total = 0
    conditioned_counter = 0
    unconditioned_running_total = 0
    for i in range(100):
        recovered_nodes = hw4.SIR_Model(graph, V.copy(), I.copy())
        percentage = float(len(recovered_nodes))/len(V) * 100
        if percentage > 50:
            e += 1
            conditioned_running_total += percentage
            conditioned_counter += 1
        unconditioned_running_total += percentage
    return e, conditioned_running_total / conditioned_counter, unconditioned_running_total / 100


def main():
    erdos_graph = snap.LoadEdgeList(snap.PUNGraph, "SIR_erdos_renyi.txt", 0, 1)
    pref_graph = snap.LoadEdgeList(snap.PUNGraph, "SIR_preferential_attachment.txt", 0, 1)
    actor_graph = snap.LoadEdgeList(snap.PUNGraph, "imdb_actor_edges.tsv", 0, 1)
    print("Erdos")
    e1, p1, p2 = Q1_3(erdos_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Preferential")
    e2, p1, p2 = Q1_3(pref_graph)
    print("%d trials resulted in epidemics" % e2)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Actors")
    e3, p1, p2 = Q1_3(actor_graph)
    print("%d trials resulted in epidemics" % e3)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)


if __name__ == '__main__':
    sys.exit(main())
