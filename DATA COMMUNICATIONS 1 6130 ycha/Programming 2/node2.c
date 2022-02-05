#include <stdio.h>

#define CURR_NODE 2

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

struct distance_table 
{
  int costs[4][4];
} dt2;


/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
   printf("rtinit2 called at %f.\n", clocktime);
   /* initialize all the elements of dt2 */
   int nodeNum = 0;
   int i, j;
   for(i = 0; i < 4; i++) {
      for(j = 0; j < 4; j++) {
         dt2.costs[j][i] = 999;   
      }
   }
   dt2.costs[0][CURR_NODE] = 3;
   dt2.costs[1][CURR_NODE] = 1;
   dt2.costs[2][CURR_NODE] = 0;
   dt2.costs[3][CURR_NODE] = 2;
   dt2.costs[0][0] = 3;
   dt2.costs[1][1] = 1;
   dt2.costs[3][3] = 2;
   printdt2(&dt2);
   
   /* Create rtpackets to be sent to neighbor nodes */
   struct rtpkt rp2[3];
   for( i = 0; i < 3; nodeNum++, i++) {
      if(nodeNum == CURR_NODE)
         nodeNum++;
      rp2[i].sourceid = CURR_NODE;
      rp2[i].destid = nodeNum;
      for(j = 0; j < 4; j++) 
         rp2[i].mincost[j] = dt2.costs[j][CURR_NODE];
      tolayer2(rp2[i]);
   }
   printf("\n");
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
   printf("rtupdate2 called at %f.  ", clocktime);
   int newCost;
   int i, j, nodeNum = 0;
   int updated = 0;
   int viaId = rcvdpkt->sourceid; 
   printf("Received rtpkt from node %d\n", viaId);
   
   /* check incomming packet route costs to see if distance table needs updating */
   for(i = 0; i < 4; i++) {
      newCost = dt2.costs[viaId][viaId] + rcvdpkt->mincost[i];
      if(rcvdpkt->mincost[i] != 999 && dt2.costs[i][viaId] != newCost) {     
         dt2.costs[i][viaId] = newCost;
         if(dt2.costs[i][CURR_NODE] > newCost) {
            updated = 1;
            dt2.costs[i][CURR_NODE] = newCost;
         }
      }
   }
   
   /* It its own minimum cost to another node changes as a result or the update, we inform its neighbors */
   printdt2(&dt2);
   if(updated) {
      printf("Node %d's minimum costs have been updated.\n", CURR_NODE);
      printf("Sending updates to ");
      struct rtpkt rp2[3];
      for( i = 0; i < 3; nodeNum++, i++) {
         if(nodeNum == CURR_NODE)
            nodeNum++;
         printf("%d ", nodeNum);
         rp2[i].sourceid = CURR_NODE;
         rp2[i].destid = nodeNum;
         for(j = 0; j < 4; j++) 
            rp2[i].mincost[j] = dt2.costs[j][CURR_NODE];
         tolayer2(rp2[i]);
      }
      printf(", contents: ");
      for(i = 0; i < 4; i++) {
         printf("%d ", dt2.costs[i][CURR_NODE]);  
      }
      printf("\n\n");
      return;
   }
   printf("Node %d's minimum costs have not been updated.\n\n", CURR_NODE);
}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







