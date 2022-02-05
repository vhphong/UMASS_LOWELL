import snap
import sys
from heapq import heappush, nlargest
import random


def generate_random_seed_set(graph, size):
    seed_set = set()
    while len(seed_set) < size:
        seed_id = graph.GetRndNId()
        if seed_id not in seed_set:
            seed_set.add(seed_id)
    return list(seed_set)


def generate_most_central_node_seed_set(graph, size):
    most_central_node_heap = []
    # use max-heap to get nodes with highest degree centrality
    OutDegV = snap.TIntPrV()
    snap.GetNodeOutDegV(graph, OutDegV)
    for item in OutDegV:
        heappush(most_central_node_heap, (item.GetVal2(), item.GetVal1()))
    central_node_id = list()
    for item in nlargest(size, most_central_node_heap):
        central_node_id.append(item[1])
    return central_node_id


def get_influence(graph, seed_set):
    p = 0.01
    activated_node = set()
    visited = set()
    iterations = 1
    total = 0
    for i in range(iterations):
        while len(seed_set) > 0:
            seed = seed_set.pop(0)
            activated_node.add(seed)
            visited.add(seed)
            seed_out_deg = graph.GetNI(seed).GetOutDeg()
            for j in range(seed_out_deg):
                neighbor_id = graph.GetNI(seed).GetOutNId(j)
                if neighbor_id in visited:
                    continue
                visited.add(neighbor_id)
                if random.random() >= p:
                    continue
                if neighbor_id not in activated_node:
                    # a new seed has been activated, will need to iterate through
                    seed_set.append(graph.GetNI(seed).GetOutNId(j))
        total += len(activated_node)
    return total/iterations


def PKU_IC(g, A):
    res = 0.0
    IC_ITERATION = 100
    p = 0.01
    for _ in range(IC_ITERATION):
        total_activated_nodes = set()
        for u in A:
            l1 = {u}
            l2 = set()
            failed_node = set()
            activated_nodes = {u}
            while len(l1):
                for v in l1:
                    seed_out_deg = g.GetNI(v).GetOutDeg()
                    for j in range(seed_out_deg):
                        neighbor = g.GetNI(v).GetOutNId(j)
                        if neighbor not in failed_node and neighbor not in activated_nodes and random.random() > p:
                            l2.add(neighbor)
                            activated_nodes.add(neighbor)
                        else:
                            failed_node.add(neighbor)
                l1 = l2
                l2 = set()
            total_activated_nodes.update(activated_nodes)
        res += len(total_activated_nodes)
    return res / IC_ITERATION


def main():
    pku_degree_yaxis = list()
    degree_yaxis = list()
    random_yaxis = list()
    amazon_graph = snap.LoadEdgeList(snap.PUNGraph, "ca-HepPh.txt", 0, 1)
    # print(amazon_graph.GetEdges())
    for target_set_size in range(1, 15):
        seed_set = generate_most_central_node_seed_set(amazon_graph, target_set_size)
        pku_degree_yaxis.append(PKU_IC(amazon_graph, seed_set))
        # degree_yaxis.append(get_influence(amazon_graph, seed_set))
        # seed_set = generate_random_seed_set(amazon_graph, target_set_size)
        # random_yaxis.append(get_influence(amazon_graph, seed_set))

    print(degree_yaxis)
    print(pku_degree_yaxis)
    # print(random_yaxis)


if __name__ == '__main__':
    sys.exit(main())