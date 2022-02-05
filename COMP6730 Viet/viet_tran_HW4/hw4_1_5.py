import snap
import sys
import hw4
import random
from heapq import heappush, nlargest


def generate_highest_degree_node_seed_set(graph, size):
    most_central_node_heap = []
    # use max-heap to get nodes with highest degree centrality
    OutDegV = snap.TIntPrV()
    snap.GetNodeOutDegV(graph, OutDegV)
    for item in OutDegV:
        heappush(most_central_node_heap, (item.GetVal2(), item.GetVal1()))
    central_node_id = set()
    for item in nlargest(size, most_central_node_heap):
        central_node_id.add(item[1])
    return central_node_id


def Q1_5_highest_degree(graph):
    e = 0
    V = set()
    for NI in graph.Nodes():
        V.add(NI.GetId())
    I = set()
    I = I.union(generate_highest_degree_node_seed_set(graph, 10))
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


def Q1_5_random(graph):
    e = 0
    V = set()
    for NI in graph.Nodes():
        V.add(NI.GetId())
    I = set()
    e = 0
    conditioned_running_total = 0
    conditioned_counter = 0
    unconditioned_running_total = 0
    for i in range(10):
        Rnd = snap.TRnd(random.randint(0, 100))
        Rnd.Randomize()
        I.add(graph.GetRndNId(Rnd))
    for i in range(100):
        print("Calculating at iteration %d" % i)
        recovered_nodes = hw4.SIR_Model(graph, V.copy(), I.copy())
        percentage = float(len(recovered_nodes)) / len(V) * 100
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
    print("Erdos Random Nodes")
    e1, p1, p2 = Q1_5_random(erdos_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Erdos Highest Deg Nodes")
    e1, p1, p2 = Q1_5_highest_degree(erdos_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Preferential Random Nodes")
    e1, p1, p2 = Q1_5_random(pref_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Preferential Highest Degree Nodes")
    e1, p1, p2 = Q1_5_highest_degree(erdos_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Actors Random Nodes")
    e1, p1, p2 = Q1_5_random(actor_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Actors Highest Degree Nodes")
    e1, p1, p2 = Q1_5_highest_degree(actor_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)


if __name__ == '__main__':
    sys.exit(main())

