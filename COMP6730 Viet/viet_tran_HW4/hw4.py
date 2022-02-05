import sys
import snap
import random
import scipy.stats


def SIR_Model(graph, V, I):
    S = set()
    S = V - I
    R = set()
    beta = 0.05
    delta = 0.5
    while I:
        S_prime = set()
        I_prime = set()
        J_prime = set()
        R_prime = set()
        for u in V:
            if u in S:
                u_NI = graph.GetNI(u)
                u_out_deg = u_NI.GetOutDeg()
                for j in range(u_out_deg):
                    neighbor_id = u_NI.GetOutNId(j)
                    if neighbor_id in I:
                        if random.random() <= beta:
                            S_prime.add(u)
                            I_prime.add(u)
                            break
            elif u in I:
                if random.random() <= delta:
                    J_prime.add(u)
                    R_prime.add(u)
        S -= S_prime
        I = I.union(I_prime)
        I -= J_prime
        R = R.union(R_prime)
    return R


def Q1_2(graph):
    V = set()
    for NI in graph.Nodes():
        V.add(NI.GetId())
    conditioned_running_total = 0
    conditioned_counter = 0
    unconditioned_running_total = 0
    e = 0
    for i in range(100):
        I = set()
        Rnd = snap.TRnd(100)
        Rnd.Randomize()
        I.add(graph.GetRndNId(Rnd))
        recovered_nodes = SIR_Model(graph, V.copy(), I.copy())
        percentage = float(len(recovered_nodes))/len(V) * 100
        if percentage > 50:
            e += 1
            conditioned_running_total += percentage
            conditioned_counter += 1
        unconditioned_running_total += percentage
    return e, conditioned_running_total/conditioned_counter, unconditioned_running_total/100


def main():
    erdos_graph = snap.LoadEdgeList(snap.PUNGraph, "SIR_erdos_renyi.txt", 0, 1)
    pref_graph = snap.LoadEdgeList(snap.PUNGraph, "SIR_preferential_attachment.txt", 0, 1)
    actor_graph = snap.LoadEdgeList(snap.PUNGraph, "imdb_actor_edges.tsv", 0, 1)
    print("Erdos")
    e1, p1, p2 = Q1_2(erdos_graph)
    print("%d trials resulted in epidemics" % e1)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Preferential")
    e2, p1, p2 = Q1_2(pref_graph)
    print("%d trials resulted in epidemics" % e2)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Actors")
    e3, p1, p2 = Q1_2(actor_graph)
    print("%d trials resulted in epidemics" % e3)
    print("Mean proportion infected with condition : %f" % p1)
    print("Mean proportion infected without conditioning : %f" % p2)

    print("Erdos vs Preferential")
    print(scipy.stats.chi2_contingency([[e1, 100-e1], [e2, 100-e2]]))
    print("Preferential vs Actor")
    print(scipy.stats.chi2_contingency([[e2, 100-e1], [e3, 100-e2]]))
    print("Erdos vs Actor")
    print(scipy.stats.chi2_contingency([[e1, 100-e1], [e3, 100-e3]]))


if __name__ == '__main__':
    sys.exit(main())
