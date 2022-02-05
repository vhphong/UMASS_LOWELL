import snap
import sys
from heapq import heappush, nlargest
from tqdm import tqdm
import random
import matplotlib as plt

# making graph global because of constant use
collab_network = snap.LoadEdgeList(snap.PUNGraph, "ca-HepPh.txt", 0, 1)
snap.DelSelfEdges(collab_network)


def generate_random_seed_set(graph, size):
    """

    :param graph: snap.PUNGraph object representing an undirected graph
    :param size: desired size of output seed set
    :return: set of random nodes
    """
    seed_set = set()
    while len(seed_set) < size:
        seed_id = graph.GetRndNId()
        if seed_id not in seed_set:
            seed_set.add(seed_id)
    return seed_set


def heapify_graph(graph):
    """

    :param graph: snap.PUNGraph object representing an undirected graph
    :return: heap of nodes in the graph sorted by centrality
    """
    most_central_node_heap = []
    # use max-heap to get nodes with highest degree centrality
    OutDegV = snap.TIntPrV()
    snap.GetNodeOutDegV(graph, OutDegV)
    for item in OutDegV:
        heappush(most_central_node_heap, (item.GetVal2(), item.GetVal1()))
    return most_central_node_heap


def generate_most_central_node_seed_set(heap, size):
    """

    :param heap: heap of node sorted by centrality
    :param size: desired size of output seed set
    :return: set of node with highest centrality
    """
    central_node_id = list()
    for item in nlargest(size, heap):
        central_node_id.append(item[1])
    return central_node_id


def populate_q(graph):
    """

    :param graph: snap.PUNGraph object representing an undirected graph
    :return: tuple of each node and its marginal gain
    """
    pbar = tqdm(total=graph.GetNodes())
    pbar.set_description("Populating Q")
    Q = list()
    for NI in (graph.Nodes()):
        pbar.update(1)
        seed_set = list()
        seed_set.append(NI.GetId())
        mg, mg_set = IC(graph, seed_set)
        flag = 0
        u = (mg, flag, NI.GetId(), mg_set)
        Q.append(u)
    pbar.close()
    Q.sort(reverse=True)
    return Q


def recursive_binary_search(aList, target, start, end):
    """

    :param aList: list of items
    :param target: item to search for
    :param start: start index
    :param end: end index
    :return:
    """
    if end-start+1 <= 0:
        return False
    else:
        midpoint = start + (end - start) // 2
        if aList[midpoint][2] == target:
            return midpoint
        else:
            if target < aList[midpoint]:
                return recursive_binary_search(aList, target, start, midpoint-1)
            else:
                return recursive_binary_search(aList, target, midpoint+1, end)


def lv_celf(graph, k, Q):
    """
    Implemented lv_celf according the provided paper due to better performance than
    regular CELF
    :param graph: snap.PUNGraph object representing an undirected graph
    :param k: size of desired activated node
    :param Q: tuple of each node and its marginal gain
    :return: set of activated nodes with biggest marginal gain according to CELF
    """
    S_node_id = set()
    pbar = tqdm(total=k)
    pbar.set_description("CELF Progress")
    while len(S_node_id) < k and len(Q) > 0:
        u = Q[0]
        if u[1] == len(S_node_id):
            S_node_id.add(u[2])
            for item in u[3]:
                index = recursive_binary_search(Q, item, 0, len(Q))
                if index is not False:
                    Q.remove(Q[index])
            prev_mg, prev_mg_set = IC(graph, S_node_id)
            pbar.update(1)
        else:
            su_seed_set = set(S_node_id)
            su_seed_set.add(u[2])
            curr_mg, curr_mg_set = IC(graph, su_seed_set)
            mg = curr_mg_set - prev_mg_set
            Q[0] = (len(mg), len(S_node_id), u[2], mg)
            Q.sort(reverse=True)
    pbar.close()
    return S_node_id


def IC(g, A):
    """

    :param g: desired size of output seed set
    :param A: original activated node(seed set)
    :return: length of activated node and the set of activated node
    """
    res = 0.0
    p = 0.01
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
                    if neighbor not in failed_node and neighbor not in activated_nodes and edge_dict[v][neighbor]<=p:
                        l2.add(neighbor)
                        activated_nodes.add(neighbor)
                    else:
                        failed_node.add(neighbor)
            l1 = l2
            l2 = set()
        total_activated_nodes.update(activated_nodes)
    res += len(total_activated_nodes)
    return res, total_activated_nodes


def generate_edge_dict(graph):
    """

    :param graph: snap.PUNGraph object representing an undirected graph
    :return: dictionary of each edge going to another with probability
    """
    edge_dict = {}
    pbar = tqdm(total=graph.GetEdges())
    pbar.set_description("Creating Edge Dict")
    for EI in graph.Edges():
        r = random.random()
        if EI.GetSrcNId() in edge_dict.keys():
            edge_dict[EI.GetSrcNId()][EI.GetDstNId()] = r
        else:
            edge_dict[EI.GetSrcNId()] = {EI.GetDstNId(): r}
        if EI.GetDstNId() in edge_dict.keys():
            edge_dict[EI.GetDstNId()][EI.GetSrcNId()] = r
        else:
            edge_dict[EI.GetDstNId()] = {EI.GetSrcNId(): r}
        pbar.update(1)
    pbar.close()
    return edge_dict


# making edge dict global because of constant use by IC
edge_dict = generate_edge_dict(collab_network)


def influence_maximization(graph):
    """

    :param graph: snap.PUNGraph object representing an undirected graph
    :return: None
    """
    degree_yaxis = list()
    random_yaxis = list()
    celf_yaxis = list()
    x_axis = list(range(0, 31))
    Q = populate_q(collab_network)
    iteration = 31
    pbar = tqdm(total=iteration-1)
    pbar.set_description("Main Loop")
    most_central_node_heap = heapify_graph(collab_network)
    for target_set_size in (range(0, iteration)):
        pbar.write("Seed size %d" % target_set_size)
        pbar.write("RANDOM")
        seed_set = generate_random_seed_set(collab_network, target_set_size)
        random_yaxis.append(IC(collab_network, seed_set)[0])
        pbar.write("finished!" + str(random_yaxis))
        pbar.write("CENTRAL")
        seed_set = generate_most_central_node_seed_set(most_central_node_heap, target_set_size)
        degree_yaxis.append(IC(collab_network, seed_set)[0])
        pbar.write("finished!" + str(degree_yaxis))
        pbar.write("CELF")
        seed_set = lv_celf(collab_network, target_set_size, list(Q))
        celf_yaxis.append(IC(collab_network, seed_set)[0])
        pbar.write("finished!" + str(celf_yaxis))
        pbar.update(1)
    pbar.close()
    plt.plot(x_axis, random_yaxis, linestyle='dashed', color='r', label='Random')
    plt.plot(x_axis, degree_yaxis, linestyle='dotted', color='g', label='Centrality')
    plt.plot(x_axis, celf_yaxis, linestyle='-.', color='b', label='CELF')
    plt.xlabel('Target set size')
    plt.ylabel('Active nodes count')
    plt.title('Heuristics Comparison with p = 0.01 under IC model')
    plt.legend()
    plt.show()


def main():
    influence_maximization(collab_network)


if __name__ == '__main__':
    sys.exit(main())
