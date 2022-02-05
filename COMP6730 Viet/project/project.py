import snap
import sys
import random
import matplotlib.pyplot as plt
from itertools import combinations


def connect_random_nodes(graph, m=8000):
    """
    :param - graph: snap.PUNGraph object representing an undirected graph
    :param - m: number of edges to be added

    return type: snap.PUNGraph
    return: Graph object with additional m edges added by connecting m randomly
        selected pairs of nodes not already connected.
    """
    ############################################################################
    # TODO: Your code here!
    nodes = snap.CntNonZNodes(graph)  # get total
    total_edges = graph.GetEdges() + m
    while snap.CntUniqUndirEdges(graph) < total_edges:
        node_src = random.randint(0, nodes - 1)
        node_dst = random.randint(0, nodes - 1)
        if abs(node_src - node_dst) > 3:
            graph.AddEdge(node_src, node_dst)
    ############################################################################
    return graph


def get_data_points_to_plot(graph):
    """
    :param - graph: snap.PUNGraph object representing an undirected graph

    return values:
    X: list of degrees
    Y: list of frequencies: Y[i] = fraction of nodes with degree X[i]
    """
    ############################################################################
    # TODO: Your code here!
    x, y = [], []
    deg_to_cnt_v = snap.TIntPrV()
    snap.GetDegCnt(graph, deg_to_cnt_v)
    for item in deg_to_cnt_v:
        x.append(item.GetVal1())
        y.append(item.GetVal2()/float(graph.GetNodes()))
    ############################################################################
    return x, y


def calcClusteringCoefficient(graph):
    """
    :param - Graph: snap.PUNGraph object representing an undirected graph

    return type: float
    returns: clustering coeffient of `Graph
    """
    ############################################################################
    # TODO: Your code here!
    C = 0.0
    node_neighbor = []
    total = 0
    for NI in graph.Nodes():
        e_i = 0
        i = 0
        c_node = 0
        try:
            while True:
                node_neighbor.append(NI.GetNbrNId(i))
                i += 1
        except RuntimeError:
            pass
        neighbor_node_pair = (list(combinations(node_neighbor, 2)))
        for item in neighbor_node_pair:
            if graph.IsEdge(item[0], item[1]) is True:
                e_i += 1
        deg = graph.GetNI(NI.GetId()).GetInDeg()
        if deg > 1:
            c_node = (2 * float(e_i) / (deg * (deg - 1)))
        total += c_node
        node_neighbor[:] = []
        neighbor_node_pair[:] = []
    C = total / graph.GetNodes()
    ############################################################################
    return C


def main():
    number_of_nodes = 12008
    small_world = snap.GenCircle(snap.PUNGraph, number_of_nodes, 2)
    connect_random_nodes(small_world, 8000)
    assert(small_world.GetEdges() == 32016)
    collab_net = snap.LoadEdgeList(snap.PNGraph, "ca-HepPh.txt", 0, 1)
    # assert(collab_net.GetNodes() == number_of_nodes)
    # assert(collab_net.GetEdges() == 237010)
    x_smallworld, y_smallworld = get_data_points_to_plot(small_world)
    plt.loglog(x_smallworld, y_smallworld, linestyle='dashed', color='r', label='Small World Network')
    x_collabnet, y_collabnet = get_data_points_to_plot(collab_net)
    plt.loglog(x_collabnet, y_collabnet, linestyle='dotted', color='b', label='Collaboration Network')
    plt.xlabel('Node Degree (log)')
    plt.ylabel('Proportion of Nodes with a Given Degree (log)')
    plt.title('Degree Distribution of Erdos Renyi, Small World, and Collaboration Networks')
    plt.legend()
    plt.show()
    c_smallworld = calcClusteringCoefficient(small_world)
    c_collabnet = calcClusteringCoefficient(collab_net)
    print('Clustering Coefficient for Small World Network: %f' % c_smallworld)
    print('Clustering Coefficient for Collaboration Network: %f' % c_collabnet)


if __name__ == '__main__':
    sys.exit(main())