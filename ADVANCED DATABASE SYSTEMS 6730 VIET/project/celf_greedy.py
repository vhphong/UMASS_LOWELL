import snap
import sys
import random
import matplotlib.pyplot as plt


def get_influence(graph, seed_set):
    p = 0.01
    for seed in seed_set.copy():
        seed_out_deg = graph.GetNI(seed).GetOutDeg()
        for j in range(seed_out_deg):
            neighbor_id = graph.GetNI(seed).GetNbrNId(j)
            if random.random() < p:
                if neighbor_id not in seed_set:
                    seed_set.add(graph.GetNI(seed).GetNbrNId(j))
                    if len(seed_set) == graph.GetNodes():
                        return seed_set
    return seed_set


def celf_greedy(graph, k):
    S = set()
    S_node_id = set()
    Q = list()
    for NI in graph.Nodes():
        seed_set = set()
        seed_set.add(NI.GetId())
        mg = (len(get_influence(graph, seed_set)))
        flag = 0
        node_id = NI.GetId()
        u = (mg, flag, node_id)
        Q.append(u)
    Q.sort()
    while len(S_node_id) < k:
        u = Q[0]
        if u[1] == len(S):
            S.add(u)
            S_node_id.add(u[2])
            Q.remove(u)
        else:
            s_seed_set = set()
            for item in S:
                s_seed_set.add(item[2])
            su_seed_set = set(s_seed_set)
            su_seed_set.add(u[2])
            mg = len(get_influence(graph, su_seed_set) - get_influence(graph, s_seed_set))
            flag = len(S)
            curr_node_id = Q[0][2]
            Q[0] = (mg, flag, curr_node_id)
            Q.sort()
    return S_node_id


def main():
    collab_net = snap.LoadEdgeList(snap.PNGraph, "ca-HepPh.txt", 0, 1)
    celf_yaxis = list()
    random_xaxis = list()
    for target_set_size in range(30):
        seed_set = celf_greedy(collab_net, target_set_size)
        seed_set = get_influence(collab_net, seed_set)
        celf_yaxis.append(len(seed_set))
        random_xaxis.append(target_set_size)
    plt.plot(random_xaxis, celf_yaxis, linestyle='solid', color='y', label='CELF')
    plt.xlabel('Target set size')
    plt.ylabel('Active set size')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    sys.exit(main())