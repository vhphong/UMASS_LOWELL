
//TODO: add a struct member representing a member in
//your system
//typedef Member Item;

//enum for read-ability
typedef enum {online,offline}status;
/**
  Struct representing a member holding info about name of account,name of user
  and also status of account
*/
struct Member
{
  char* username;
  char* name;
  status s;
};
typedef struct Member Item,* pItem;
typedef struct node Node,* pNode;
struct node
{
  Item item;
  pNode next;
};
/**
   Struct representing a linkedlist with
   holding only the front node of the 
   linkedlist
   front: the front node of the linkedlist
   size: the number of nodes in the linkedlist
*/
struct linkedlist
{
  pNode front;
  int size;
};
typedef struct linkedlist LinkedList, *pLinkedList;
/**
   Initializing the linkedlist
   Returning the address of the created linkedlist
*/
pLinkedList linkedlistInitDefault();
/**
   Returning the number of items in the linkedlist
 */
int linkedlistGetSize(pLinkedList list);
/**
   Adding a new item to the linkedlist
 */
void linkedlistAddNodeBack(pLinkedList list, Item item);
/**
   Destroying all the nodes in the linkedlist
 */
void linkedlistDestroy(pLinkedList *list);
/**
  Add a new user member to the linkedlist 
  Precondition:user input for account name, user's name 
  as well as instantiated list
  Postcondition:return a linkedlist with added member 
 */
pLinkedList create(char* userName,char* memberName,pLinkedList list);
/**
   Obtain member's info at a certain index number
   Precondition: receive instantiated list as well index number
   Postcondition: output the member's info
 */
Item getMemberAtIndex(pLinkedList list,int index);
/**
   Search the list and output member info if found
   Precondition: receive instantiated list 
   and index number of member
   Postcondition: output member info at indicated index location
 */
void searchbyUserName(char* searchString,pLinkedList list);
/**
  Traverse the list and print out all members inside list
  Precondition:receive list
  Postcondition: print out member info if any
 */
void printList(pLinkedList list);
/**
  Traverse the list and login to account 
  if match with existing username
  Precondition:receive list and username input
  Postcondition: none
 */
void login(pLinkedList *list,char* searchString);
/**
  Traverse the list and log out of account 
  if match with existing username
  Precondition:receive list and username input
  Postcondition: none
 */
void logout(pLinkedList *list,char* searchString);
/**
  Traverse the list and delete account 
  if match with existing username
  Precondition:receive list and username input
  Postcondition: none
 */
void deleteUser(pLinkedList *list,char* searchString);
/**
  Clear/destroy all linked list as well as all member info
  Precondition:receive list
  Postcondition:none
 */
void deleteAll(pLinkedList list); 
/**
  Output dash lines to improve read-ability 
 */ 
void printDivider();
void printTableDivider();
