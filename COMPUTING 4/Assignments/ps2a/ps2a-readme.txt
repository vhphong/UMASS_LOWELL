# Student name: Phong Hong Vo
This assignment is on LFSR.
My implementation is making up 3 extra bit strings besides the originally provided in the problem.
1. The first bit string: 1000110 with 7-bit length, is tapped at 2
Its sequent output is:
1 0 0 0 1 1 0	0
0 0 0 1 1 0 0	1
0 0 1 1 0 0 1	0
0 1 1 0 0 1 0	0
1 1 0 0 1 0 0	0
1 0 0 1 0 0 0	1
0 0 1 0 0 0 1	0
0 1 0 0 0 1 0	0
The generate function taking 6-bit length yields the result: 17

2. The second bit string: 1100010110 with 10-bit length, is tapped at 4
Its sequent output is:
1 1 0 0 0 1 0 1 1 0	0
1 0 0 0 1 0 1 1 0 0	1
0 0 0 1 0 1 1 0 0 1	1
0 0 1 0 1 1 0 0 1 1	1
0 1 0 1 1 0 0 1 1 1	0
1 0 1 1 0 0 1 1 1 0	1
0 1 1 0 0 1 1 1 0 1	1
1 1 0 0 1 1 1 0 1 1	0
The generate function taking 5-bit length yields the result: 14

3. The thired bit string: 101110100011010 with 15-bit length, is tapped at 11
Its sequent output is:
1 0 1 1 1 0 1 0 0 0 1 1 0 1 0   0
0 1 1 1 0 1 0 0 0 1 1 0 1 0 0	1
1 1 1 0 1 0 0 0 1 1 0 1 0 0 1	1
1 1 0 1 0 0 0 1 1 0 1 0 0 1 1	0
1 0 1 0 0 0 1 1 0 1 0 0 1 1 0	1
0 1 0 0 0 1 1 0 1 0 0 1 1 0 1	0
1 0 0 0 1 1 0 1 0 0 1 1 0 1 0	1
0 0 0 1 1 0 1 0 0 1 1 0 1 0 1	1
0 0 1 1 0 1 0 0 1 1 0 1 0 1 1	1
0 1 1 0 1 0 0 1 1 0 1 0 1 1 1	0
1 1 0 1 0 0 1 1 0 1 0 1 1 1 0	0
1 0 1 0 0 1 1 0 1 0 1 1 1 0 0	1
0 1 0 0 1 1 0 1 0 1 1 1 0 0 1	0
1 0 0 1 1 0 1 0 1 1 1 0 0 1 0	0
0 0 1 1 0 1 0 1 1 1 0 0 1 0 0	1
0 1 1 0 1 0 1 1 1 0 0 1 0 0 1	0
1 1 0 1 0 1 1 1 0 0 1 0 0 1 0	0
The generate function taking 7-bit length yields the result: 53
