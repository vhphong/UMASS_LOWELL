#include <stdio.h>

#define CURR_NODE 3

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
} dt3;

/* students to write the following two routines, and maybe some others */

void rtinit3() 
{
   printf("rtinit3 called at %f.\n", clocktime);
   /* initialize all the elements of dt3 */
   int nodeNum = 0;
   int i, j;
   for(i = 0; i < 4; i++) {
      for(j = 0; j < 4; j++) {
         dt3.costs[i][j] = 999;   
      }
   }
   dt3.costs[0][CURR_NODE] = 7;
   dt3.costs[1][CURR_NODE] = 999;
   dt3.costs[2][CURR_NODE] = 2;
   dt3.costs[3][CURR_NODE] = 0;
   dt3.costs[0][0] = 7;
   dt3.costs[1][1] = 999;
   dt3.costs[2][2] = 2;
   printdt3(&dt3);
   
   /* Create rtpackets to be sent to neighbor nodes */
   struct rtpkt rp3[2];
   for( i = 0; i < 2; i++,nodeNum++) {
      if(nodeNum == 1)
         nodeNum++;
      rp3[i].sourceid = CURR_NODE;
      rp3[i].destid = nodeNum;
      for(j = 0; j < 4; j++) 
         rp3[i].mincost[j] = dt3.costs[j][CURR_NODE];
      tolayer2(rp3[i]);
   } 
   printf("\n");
}



void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
   printf("rtupdate3 called at %f.  ", clocktime);
   int newCost;
   int i, j, nodeNum =0;
   int updated = 0;
   int viaId = rcvdpkt->sourceid; 
   printf("Received rtpkt from node %d\n", viaId);
   
   /* check incomming packet route costs to see if distance table needs updating */
   for(i = 0; i < 4; i++) {
      newCost = dt3.costs[viaId][viaId] + rcvdpkt->mincost[i];
      if(rcvdpkt->mincost[i] != 999 && dt3.costs[i][viaId] != newCost) {
         dt3.costs[i][viaId] = newCost;
         if(dt3.costs[i][CURR_NODE] > newCost) {
            updated = 1;
            dt3.costs[i][CURR_NODE] = newCost;
         }
      }
   }
   
   /* It its own minimum cost to another node changes as a result or the update, we inform its neighbors */
   printdt3(&dt3);
   if(updated) {
      printf("Node %d's minimum costs have been updated.\n", CURR_NODE);
      printf("Sending updates to ");
      struct rtpkt rp3[2];
      for( i = 0; i < 2; i++,nodeNum++) {
         if(nodeNum == 1)
            nodeNum++;
         printf("%d ", nodeNum);
         rp3[i].sourceid = CURR_NODE;
         rp3[i].destid = nodeNum;
         for(j = 0; j < 4; j++) 
            rp3[i].mincost[j] = dt3.costs[j][CURR_NODE];
         tolayer2(rp3[i]);
      } 
      printf(", contents: ");
      for(i = 0; i < 4; i++) {
         printf("%d ", dt3.costs[i][CURR_NODE]);  
      }
      printf("\n\n");
      return;
   }
   printf("Node %d's minimum costs have not been updated.\n\n", CURR_NODE);
}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







