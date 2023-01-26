#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

/*---------------------------------------------------------------------*
 * PROCEDURES FOR MANIPULATING DOUBLY LINKED LISTS 
 * Each list contains a sentinal node, so that     
 * the first item in list l is l->flink.  If l is  
 * empty, then l->flink = l->blink = l.            
 *---------------------------------------------------------------------*/

Dllist new_dllist()
{
  Dllist d;

  d = malloc(sizeof(struct dllist));
  d->flink = d;
  d->blink = d;
  return d;
}

/** Inserts before a given node. */ 
void dll_insert_b(Dllist node, Jval v)
{
  Dllist newnode;

  newnode = (Dllist) malloc (sizeof(struct dllist));
  newnode->val = v;

  newnode->flink = node;
  newnode->blink = node->blink;
  newnode->flink->blink = newnode;
  newnode->blink->flink = newnode;
}

/** Inserts after a given node. */
void dll_insert_a(Dllist n, Jval val)
{
  dll_insert_b(n->flink, val);
}

/** Inserts at the end of the list. */
void dll_append(Dllist l, Jval val)
{
  dll_insert_b(l, val);
}

/** Inserts at the beginning of the list. */
void dll_prepend(Dllist l, Jval val)
{
  dll_insert_b(l->flink, val);
}

/** Deletes an arbitrary item. */
void dll_delete_node(Dllist node)
{
  node->flink->blink = node->blink;
  node->blink->flink = node->flink;
  free(node);
}

int dll_empty(Dllist l)
{
  return (l->flink == l);
}
 
void free_dllist(Dllist l)
{
  while (!dll_empty(l)) {
    dll_delete_node(dll_first(l));
  }
  free(l);
}

Jval dll_val(Dllist l)
{
  return l->val;
}
