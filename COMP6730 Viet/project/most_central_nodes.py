import sys
import snap
import random
from heapq import heappush, nlargest


def generate_most_central_node_seed_set(graph, size):
    most_central_node_heap = []
    # use max-heap to get nodes with highest degree centrality
    OutDegV = snap.TIntPrV()
    snap.GetNodeOutDegV(graph, OutDegV)
    for item in OutDegV:
        heappush(most_central_node_heap, (item.GetVal2(), item.GetVal1()))
    central_node_id = list()
    for item in nlargest(size, most_central_node_heap):
        central_node_id.append((item[1]))
    return central_node_id


def get_influence(graph, seed_set):
    p = 0.01
    activated_node = set()
    visited = set()
    iterations = 100
    total = 0
    seeds = list(seed_set)
    for i in range(iterations):
        while len(seeds) > 0:
            seed = seeds.pop(0)
            activated_node.add(seed)  # all seeds are activated nodes
            visited.add(seed)  # otherwise, visit nodes and add to visited set
            seed_ni = graph.GetNI(seed)
            seed_out_deg = seed_ni.GetOutDeg()
            for j in range(seed_out_deg):
                neighbor_id = seed_ni.GetOutNId(j)
                if neighbor_id in visited:
                    continue  # if already visited, skip to the end
                visited.add(neighbor_id)  # add neighbor to visited
                if random.random() >= p:
                    continue
                if neighbor_id not in activated_node:
                    seeds.append(seed_ni.GetOutNId(j))
        total += len(activated_node)
    return total/iterations


def new_get_influence(graph, seed_set):
    p = 0.01
    active_nodes = list(seed_set)
    activated_node = set()
    visited = set()
    iterations = 100
    total = 0
    for _ in range(iterations):
        while active_nodes:
            seed = active_nodes.pop(0)
            activated_node.add(seed)
            visited.add(seed)
            seed_ni = graph.GetNI(seed)
            seed_out_deg = seed_ni.GetOutDeg()
            for i in range(seed_out_deg):
                neighbor_id = seed_ni.GetOutNId(i)
                if neighbor_id in visited:
                    continue
                visited.add(neighbor_id)
                if random.random() >= p:
                    continue
                if neighbor_id not in activated_node:
                    active_nodes.append(neighbor_id)
        total += len(activated_node)
    return total / iterations


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
       pe = random.random()
       if ( pe >= p ):
        continue
       if ( v not in S ):
        activeNodes.append(v)
    ############################################################################
    return len(S)

def main():
    collab_net = snap.LoadEdgeList(snap.PUNGraph, "ca-HepPh.txt", 0, 1)
    random_xaxis = list()
    central_yaxis = list()
    tuyen_central_yaxis = list()
    for target_set_size in range(31):
        seed_set = generate_most_central_node_seed_set(collab_net, target_set_size)
        random_xaxis.append(target_set_size)
        central_yaxis.append(new_get_influence(collab_net, seed_set))
        tuyen_central_yaxis.append(IndependentCascade(collab_net, seed_set, 0.01))
    print(central_yaxis)
    print(tuyen_central_yaxis)


if __name__ == '__main__':
    sys.exit(main())
