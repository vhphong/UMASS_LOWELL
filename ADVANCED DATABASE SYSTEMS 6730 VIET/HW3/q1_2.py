import snap
import sys
import q1_1
import random
import matplotlib.pyplot as plt


def get_two_random_edges(graph):
    edge_list = []
    for i in range(2):
        rnd_seed = snap.TRnd(graph.GetNodes() + 1)
        rnd_seed.Randomize()
        random_ni = graph.GetNI(graph.GetRndNId(rnd_seed))
        random_id = random_ni.GetId()
        # get random node
        rnd = random.randint(0, random_ni.GetOutDeg()-1)
        # select random number between 0 and out-deg of node
        edge_list.append((random_id, random_ni.GetOutNId(rnd)))
        # get out-node at rnd-th location
        # do this twice to get two random edges
    return edge_list[0], edge_list[1]


def rewire_edge(e):
    rnd = random.randint(0, 1)
    v1 = e[rnd]
    v2 = e[(rnd + 1) % len(e)]
    return v1, v2


def main():
    power_grid_graph = q1_1.load_power_grid_graph("USpowergrid_n4941.txt")
    x_axis = []
    y_axis = []
    for i in range(10000):
        e1, e2 = get_two_random_edges(power_grid_graph)
        u, v = rewire_edge(e1)
        w, x = rewire_edge(e2)
        if u == w or power_grid_graph.IsEdge(w, u) \
                or v == x or power_grid_graph.IsEdge(x, v):
            i -= 1
            continue
        power_grid_graph.AddEdge(u, w)
        power_grid_graph.AddEdge(v, x)
        power_grid_graph.DelEdge(e1[0], e1[1])
        power_grid_graph.DelEdge(e2[0], e2[1])
        if i % 100 is 0:
            c = snap.GetClustCf(power_grid_graph, -1)
            x_axis.append(i)
            y_axis.append(c)
    plt.plot(x_axis, y_axis, color='r', linestyle='dashed', label='')
    plt.xlabel("Number of iterations")
    plt.ylabel("Average clustering coefficient of rewired network")
    plt.title('Avg. clustering coeff. over 10,000 rewiring iterations')
    plt.legend()
    plt.show()


if __name__ == '__main__':
    sys.exit(main())
