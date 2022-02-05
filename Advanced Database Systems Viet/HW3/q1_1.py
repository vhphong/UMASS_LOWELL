import snap
import sys
import random


def load_power_grid_graph(file_name):
    graph = snap.LoadEdgeList(snap.PUNGraph, file_name, 0, 1)
    snap.DelSelfEdges(graph)
    return graph


def create_random_graph(v, total_nodes):
    random.shuffle(v)
    random_graph = snap.GenRndGnm(snap.PUNGraph, total_nodes, 0)
    return v, random_graph


def create_array_v(graph):
    v = []
    out_degree_v = snap.TIntPrV()
    snap.GetNodeOutDegV(graph, out_degree_v)
    for item in out_degree_v:
        for i in range(0, item.GetVal2()):
            v.append(item.GetVal1())
    return v


def main():
    power_grid_graph = load_power_grid_graph("USpowergrid_n4941.txt")
    total_nodes = power_grid_graph.GetNodes() + 1
    v = create_array_v(power_grid_graph)
    total_coeff = 0
    for i in range(100):
        j = 0
        v, random_graph = create_random_graph(v, total_nodes)
        while j < len(v) - 1:
            if v[j] == v[j+1] or random_graph.IsEdge(v[j+1], v[j]):
                #  self-loop or multi-edges , reject graph
                j = 0
                v, random_graph = create_random_graph(v, total_nodes)
                continue
            random_graph.AddEdge(v[j], v[j+1])
            j += 2
        total_coeff += snap.GetClustCf(random_graph, -1)
    print(total_coeff/100)


if __name__ == '__main__':
    sys.exit(main())
