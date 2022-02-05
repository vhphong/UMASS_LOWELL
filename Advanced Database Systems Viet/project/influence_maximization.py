import snap
import sys
import random
import matplotlib.pyplot as plt
from heapq import heappush, nlargest


def generate_random_seed_set(graph, size):
    seed_set = set()
    while len(seed_set) < size:
        seed_id = graph.GetRndNId()
        if seed_id not in seed_set:
            seed_set.add(seed_id)
    return list(seed_set)


def get_influence(graph, seed_set):
    p = 0.01
    activated_node = set()
    visited = set()
    iterations = 100
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


def celf_greedy(graph, k):
    S = set()
    S_node_id = list()
    Q = list()
    for NI in graph.Nodes():
        seed_set = list()
        seed_set.append(NI.GetId())
        mg = get_influence(graph, seed_set)
        flag = 0
        node_id = NI.GetId()
        u = (mg, flag, node_id)
        Q.append(u)
    Q.sort(reverse=True)
    while len(S_node_id) < k:
        u = Q[0]
        if u[1] == len(S):
            S.add(u)
            S_node_id.append(u[2])
            Q.remove(u)
        else:
            s_seed_set = list()
            for item in S:
                s_seed_set.append(item[2])
            su_seed_set = list(s_seed_set)
            su_seed_set.append(u[2])
            mg = get_influence(graph, su_seed_set) - get_influence(graph, s_seed_set)
            flag = len(S)
            curr_node_id = Q[0][2]
            Q[0] = (mg, flag, curr_node_id)
            Q.sort(reverse=True)
    return S_node_id


def main():
    collab_net = snap.LoadEdgeList(snap.PUNGraph, "ca-HepPh.txt", 0, 1)
    random_xaxis = list()
    random_yaxis = list()
    central_yaxis = list()
    celf_yaxis = list()

    for target_set_size in range(31):
        seed_set = generate_random_seed_set(collab_net, target_set_size)
        random_yaxis.append(get_influence(collab_net, seed_set))
        random_xaxis.append(target_set_size)

        seed_set = generate_most_central_node_seed_set(collab_net, target_set_size)
        central_yaxis.append(get_influence(collab_net, seed_set))

        seed_set = celf_greedy(collab_net, target_set_size)
        celf_yaxis.append(get_influence(collab_net, seed_set))


    # for target_set_size in range(31):
    #     seed_set = generate_random_seed_set(collab_net, target_set_size)
    #     seed_set = activate_nodes(collab_net, seed_set)
    #     random_xaxis.append(target_set_size)
    #     random_yaxis.append(len(seed_set))
    #
    #     seed_set = generate_most_central_node_seed_set(collab_net, target_set_size)
    #     seed_set = activate_nodes(collab_net, seed_set)
    #     central_yaxis.append(len(seed_set))
    #
    #     seed_set = celf_greedy(collab_net, target_set_size)
    #     seed_set = activate_nodes(collab_net, seed_set)
    #     celf_yaxis.append(len(seed_set))
    plt.plot(random_xaxis, random_yaxis, linestyle='solid', color='r', label='Random')
    plt.plot(random_xaxis, central_yaxis, linestyle='solid', color='g', label='Central')
    plt.plot(random_xaxis, celf_yaxis, linestyle='solid', color='y', label='Greedy')
    plt.xlabel('Target set size')
    plt.ylabel('Active set size')

    plt.legend(loc=2)
    plt.show()

    print(random_yaxis)
    print(central_yaxis)
    print(celf_yaxis)


if __name__ == '__main__':
    sys.exit(main())