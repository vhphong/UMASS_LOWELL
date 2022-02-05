#include <stdio.h>

#define CURR_NODE 0

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
} dt0;


/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
   printf("rtinit0 called at %f.\n", clocktime);
   /* initialize all the elements of dt0 */
   int nodeNum = 1;
   int i, j;
   for(i = 1; i < 4; i++) {
      for(j = 0; j < 4; j++) {
         dt0.costs[j][i] = 999;   
      }
   }
   dt0.costs[0][CURR_NODE] = 0;
   dt0.costs[1][CURR_NODE] = 1;
   dt0.costs[2][CURR_NODE] = 3;
   dt0.costs[3][CURR_NODE] = 7;
   dt0.costs[1][1] = 1;
   dt0.costs[2][2] = 3;
   dt0.costs[3][3] = 7;
   printdt0(&dt0);
   
   /* Create rtpackets to be sent to neighbor nodes */
   struct rtpkt rp0[3];
   for(i = 0; i < 3; i++,nodeNum++) {
      rp0[i].sourceid = CURR_NODE;
      rp0[i].destid = nodeNum;
      for(j = 0; j < 4; j++) 
         rp0[i].mincost[j] = dt0.costs[j][CURR_NODE];
      tolayer2(rp0[i]);
   } 
   printf("\n");  
}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
   printf("rtupdate0 called at %f.  ", clocktime);
   int newCost;
   int i, j, nodeNum = 1;
   int updated = 0;
   int viaId = rcvdpkt->sourceid; 
   printf("Received rtpkt from node %d\n", viaId);
   
   /* check incomming packet route costs to see if distance table needs updating */
   for(i = 0; i < 4; i++) {
      newCost = dt0.costs[viaId][viaId] + rcvdpkt->mincost[i];
      if(rcvdpkt->mincost[i] != 999 && dt0.costs[i][viaId] != newCost) {         
         dt0.costs[i][viaId] = newCost;
         if(dt0.costs[i][CURR_NODE] > newCost){
            dt0.costs[i][CURR_NODE] = newCost;
            updated = 1;
         }
      }
   }
   
   /* It its own minimum cost to another node changes as a result or the update, we inform its neighbors */
   printdt0(&dt0);
   if(updated) {
      printf("Node %d's minimum costs have been updated.\n", CURR_NODE);
      printf("Sending updates to ");
      struct rtpkt rp0[3];
      for(i = 0; i < 3; i++,nodeNum++) {
         printf("%d ", nodeNum);
         rp0[i].sourceid = CURR_NODE;
         rp0[i].destid = nodeNum;
         for(j = 0; j < 4; j++) 
            rp0[i].mincost[j] = dt0.costs[j][CURR_NODE];
         tolayer2(rp0[i]);
      } 
      printf(", contents: ");
      for(i = 0; i < 4; i++) {
         printf("%d ", dt0.costs[i][CURR_NODE]);  
      }
      printf("\n\n");
      return;
   }
   printf("Node %d's minimum costs have not been updated.\n\n", CURR_NODE);  
}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

