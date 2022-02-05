0:mar := pc; rd; 				{ main loop  }
1:pc := 1 + pc; rd; 				{ increment pc }
2:ir := mbr; if n then goto 28; 		{ save, decode mbr }
3:tir := lshift(ir + ir); if n then goto 19; 	
4:tir := lshift(tir); if n then goto 11; 	{ 000x or 001x? }
5:alu := tir; if n then goto 9; 		{ 0000 or 0001? }
6:mar := ir; rd; 				{ 0000 = LODD }
7:rd; 						
8:ac := mbr; goto 0; 				
9:mar := ir; mbr := ac; wr; 			{ 0001 = STOD }
10:wr; goto 0; 					
11:alu := tir; if n then goto 15; 		{ 0010 or 0011? }
12:mar := ir; rd; 				{ 0010 = ADDD }
13:rd; 						
14:ac := ac + mbr; goto 0; 			
15:mar := ir; rd; 				{ 0011 = SUBD }
16:ac := 1 + ac; rd; 				{ Note: x - y = x + 1 + not y }
17:a := inv(mbr); 				
18:ac := a + ac; goto 0; 			
19:tir := lshift(tir); if n then goto 25; 	{ 010x or 011x? }
20:alu := tir; if n then goto 23; 		{ 0100 or 0101? }
21:alu := ac; if n then goto 0; 		{ 0100 = JPOS }
22:pc := band(ir, amask); goto 0; 		{ perform the jump }
23:alu := ac; if z then goto 22; 		{ 0101 = JZER }
24:goto 0;					{ jump failed }
25:alu := tir; if n then goto 27; 		{ 0110 or 0111? }
26:pc := band(ir, amask); goto 0; 		{ 0110 = JUMP }
27:ac := band(ir, amask); goto 0; 		{ 0111 = LOCO }
28:tir := lshift(ir + ir); if n then goto 40; 	{ 10xx or 11xx? }
29:tir := lshift(tir); if n then goto 35; 	{ 100x or 101x? }
30:alu := tir; if n then goto 33; 		{ 1000 or 1001? }
31:a := sp + ir; 				{ 1000 = LODL }
32:mar := a; rd; goto 7; 			
33:a := sp + ir; 				{ 1001 = STOL }
34:mar := a; mbr := ac; wr; goto 10; 		
35:alu := tir; if n then goto 38; 		{ 1010 or 1011? }
36:a := sp + ir; 				{ 1010 = ADDL }
37:mar := a; rd; goto 13; 			
38:a := sp + ir; 				{ 1011 = SUBL }
39:mar := a; rd; goto 16; 			
40:tir := lshift(tir); if n then goto 46; 	{ 110x or 111x? }
41:alu := tir; if n then goto 44; 		{ 1100 or 1101? }
42:alu := ac; if n then goto 22; 		{ 1100 = JNEG }
43:goto 0; 					
44:alu := ac; if z then goto 0; 		{ 1101 = JNZE }
45:pc := band(ir, amask); goto 0; 		
46:tir := lshift(tir); if n then goto 50; 	
47:sp := sp + (-1); 				{ 1110 = CALL }
48:mar := sp; mbr := pc; wr; 			
49:pc := band(ir, amask); wr; goto 0; 		
50:tir := lshift(tir); if n then goto 65; 	{ 1111, examine addr }
51:tir := lshift(tir); if n then goto 59; 	
52:alu := tir; if n then goto 56; 		
53:mar := ac; rd; 				{ 1111000 = PSHI }
54:sp := sp + (-1); rd; 			
55:mar := sp; wr; goto 10; 			
56:mar := sp; sp := sp + 1; rd; 		{ 1111001 = POPI }
57:rd; 						
58:mar := ac; wr; goto 10; 			
59:alu := tir; if n then goto 62; 		
60:sp := sp + (-1); 				{ 1111010 = PUSH }
61:mar := sp; mbr := ac; wr; goto 10; 		
62:mar := sp; sp := sp + 1; rd; 		{ 1111011 = POP }
63:rd; 						
64:ac := mbr; goto 0; 				
65:tir := lshift(tir); if n then goto 73; 	
66:alu := tir; if n then goto 70; 		
67:mar := sp; sp := sp + 1; rd; 		{ 1111100 = RETN }
68:rd; 						
69:pc := mbr; goto 0; 				
70:a := ac; 					{ 1111101 = SWAP }
71:ac := sp; 					
72:sp := a; goto 0; 				
73:alu := tir; if n then goto 76; 		
74:a := band(ir, smask); 			{ 1111110 = INSP }
75:sp := sp + a; goto 0; 			
76:tir := tir + tir; if n then goto 80;		
77:a := band(ir, smask); 			{ 11111110 = DESP }
78:a := inv(a); 				
79:a := a + 1; goto 75; 			
80:tir := tir + tir; if n then goto 111;	{ 1111 1111 1x = HALT }
81:alu := tir + tir; if n then goto 103;        { 1111 1111 01 = RSHIFT }
82:a := lshift(1);				{ 1111 1111 00 = MULT }
83:a := lshift(a + 1);
84:a := lshift(a + 1);
85:a := lshift(a + 1);
86:a := lshift(a + 1);
87:a := a + 1                   		
88:b := band(ir, a);				{ build 6 bit mask and put multiplier in b }
89:mar := sp; rd;               
90:rd;
91:a := mbr;                    		{ get multiplicand (Mcnd) and put in a }
92:c := (-1)			   		{ set c to -1, if it's still -1 at the end result is neg }
93:d := 0			   		{ zero d, use as accumulating counter }
94:alu := a; if n then goto 97;    		{ if Mcnd is negative goto 97 }
95:c := c + 1; goto 97;            		{ if Mcnd is pos + 1 to c (c==0) goto 97 }
96:alu := c; if z then goto 100;   		{ if Mcnd is pos, this is OF, goto 100 }
97:b := b + (-1); if n then goto 101;		{ dec loop counter b, if done goto 101 }
98:d := d + a; if n then goto 96;  		{ add multiplicand to counter, OF goto 96 }
99:alu := c; if z then goto 97;    		{ if Mcnd is pos keep adding, goto 97 }
100:ac := (-1); goto 0;				{ OF error here, set AC = -1, return }
101:mar := sp; ac := 0;				{ success AC = 0, replace Mcnd with sum on stack }
102:mbr := d; wr; goto 10;			{ put sum into MBR and write, goto 10 to finish }
103:a := lshift(1);				{ 1111 1111 01 = RSHIFT }
104:a := lshift(a + 1);
105:a := lshift(a + 1);
106:a := a + 1;
107:b := band(ir, a);
108:b := b + (-1); if n then goto 0;
109:ac := rshift(ac); goto 108;
110:goto 0;
111:tir := tir + tir; if n then goto 155;	{ 1111 1111 1x = HALT }
112:d := 1				        { 1111 1111 10 = DIV  }
113:mar := sp; rd;
114:rd;
115:a := mbr;           			{ get dividend and put in a }
116:b := sp + 1;				{ location sp + 1 for divisor }
117:mar := b; rd;
118:rd;
119:b := mbr; if z then goto 147; 		{ if divisor is zero, goto 147 }
120:alu := a; if n then goto 123; 		{ if dividend is negative, goto 123 }
121:alu := b; if n then goto 125; 		{ if divisor is positive, goto 125 }
122:goto 129;  		       			{ if dividend and divisor are positive, goto 129}
123:a := inv(a);				{ inverse dividend }
124:a := a + 1; goto 127;      			
125:b := inv(b);				{ inverse divisor }
126:b := b + 1;                			
127:d := inv(d);				{ inverse flag }
128:d := d + 1; goto 120;      			
129:c := 0		       			{ quotient }
130:b := inv(b);
131:b := b + 1;		            		
132:e := a;		            		{ remainder }
133:a := a + b; if n then goto 135; 		{ if negative, goto 135 }
134:c := c + 1; goto 132;           		{ quotient increases 1, goto 132 }
135:f := sp + (-1);				{ location sp-1 for remainder }
136:mar := f;
137:mbr := e; wr;                   		{ push remainder }
138:wr;
139:alu := d; if n then goto 144;   		{ if negative, goto 144 }
140:f := f + (-1);                  		{ location sp-2 for quotient }
141:mar := f;
142:mbr := c; wr;                   		{ push quotient }
143:wr; goto 146;
144:c := inv(c);				{ inverse quotient }
145:c := c + 1; goto 140;          	 	
146:ac := 0; goto 0;                		{ devision is legal, ac = 0 }
147:f := sp + (-1);                       	{ illegal case, location sp-1 }
148:mar := f;
149:mbr := (-1); wr;                   		{ remainder = -1 }
150:wr;  
151:f := f + (-1);				{ illegal case, location sp-2 }
152:mar := f; ac := (-1);            		
153:mbr := 0; wr;                    		{ quotient = 0 }
154:wr;            
155:rd; wr;                          		{HALT}


