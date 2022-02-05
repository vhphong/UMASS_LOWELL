#include <stdio.h>

#define CURR_NODE 1

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };


extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */


rtinit1() 
{
   printf("rtinit1 called at %f.\n", clocktime);
   /* initialize all the elements of dt1 */
   int nodeNum = 0;
   int i, j;
   for(i = 0; i < 4; i++) {
      for(j = 0; j < 4; j++) {
         dt1.costs[j][i] = 999;   
      }
   }
   dt1.costs[0][CURR_NODE] = 1;
   dt1.costs[1][CURR_NODE] = 0;
   dt1.costs[2][CURR_NODE] = 1;
   dt1.costs[3][CURR_NODE] = 999;
   dt1.costs[0][0] = 1;
   dt1.costs[2][2] = 1;
   printdt1(&dt1);
      
   /* Create rtpackets to be sent to neighbor nodes */
   struct rtpkt rp1[2];
   for( i = 0; i < 2; i++, nodeNum++) {
      if(nodeNum == CURR_NODE)
         nodeNum++;
      rp1[i].sourceid = CURR_NODE;
      rp1[i].destid = nodeNum;
      for(j = 0; j < 4; j++) 
         rp1[i].mincost[j] = dt1.costs[j][CURR_NODE];
      tolayer2(rp1[i]);
   }  
   printf("\n");
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;  
{
   printf("rtupdate1 called at %f.  ", clocktime);
   int newCost;
   int i, j, nodeNum = 0;
   int updated = 0;
   int viaId = rcvdpkt->sourceid; 
   printf("Received rtpkt from node %d\n", viaId);
   
   /* check incomming packet route costs to see if distance table needs updating */
   for(i = 0; i < 4; i++) {
      newCost = dt1.costs[viaId][viaId] + rcvdpkt->mincost[i];
      if(rcvdpkt->mincost[i] != 999 && dt1.costs[i][viaId] != newCost) {         
         dt1.costs[i][viaId] = newCost;
         if(dt1.costs[i][CURR_NODE] > newCost) {
            updated = 1;
            dt1.costs[i][CURR_NODE] = newCost;
         }
      }
   }
   
   /* It its own minimum cost to another node changes as a result or the update, we inform its neighbors */
   printdt1(&dt1);
   if(updated) {
      printf("Node %d's minimum costs have been updated.\n", CURR_NODE);
      printf("Sending updates to ");
      struct rtpkt rp1[2];
      for( i = 0; i < 2; i++, nodeNum++) {
         if(nodeNum == CURR_NODE)
            nodeNum++;
         printf("%d ", nodeNum);
         rp1[i].sourceid = CURR_NODE;
         rp1[i].destid = nodeNum;
         for(j = 0; j < 4; j++) 
            rp1[i].mincost[j] = dt1.costs[j][CURR_NODE];
         tolayer2(rp1[i]);
      }   
      printf(", contents: ");
      for(i = 0; i < 4; i++) {
         printf("%d ", dt1.costs[i][CURR_NODE]);  
      }
      printf("\n\n");
      return;
   }
   printf("Node %d's minimum costs have not been updated.\n\n", CURR_NODE);
}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


