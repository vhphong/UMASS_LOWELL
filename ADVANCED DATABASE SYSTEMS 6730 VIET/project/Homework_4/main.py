from func import *
from time import clock
import sys
import random

def main():

    # g = read_from_txt('Karate Club network.txt')
    g = read_from_txt('Amazon.txt')
    # print g
    # print IC(g, {1, 34})
    # print greedy(g, 2)
    # print CELF(g, 2)
    # print degree(g, 2)
    # for k in range(1, 5):
    #     start = clock()
    #     print str(greedy(g, k)[1]) + '\t',
    #     finish = clock()
    #     print finish - start
    for k in range(1, 2):
        # start = clock()
        # print str(CELF(g, k)[1]) + '\t',
        # finish = clock()
        # print str(finish - start) + '\t',
        # start = clock()
        print str(degree(g, k)[0]) + '\t',
        # finish = clock()
        # print str(finish - start) + '\t',
        # start = clock()
        # print str(rand(g, k)[1]) + '\t',
        # finish = clock()
        # print finish - start


if __name__ == '__main__':
    sys.exit(main())