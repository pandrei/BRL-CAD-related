/*                   T E S T _ R B T R E E . C
 * BRL-CAD
 *
 * Copyright (c) 1998-2012 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file test_rbtree.c
 *
 * Brief description
 *
 */

#include "common.h"

#include <stdlib.h>
#include <stdio.h>

#include "bu.h"
#include "./rb_internals.h"

/**
 * C M P F ()
 * Generic Comparison function that internally casts
 * the parameters to integers.
 *
 * Comment to be deleted if considered useless.
 */
int Cmpf(const void* a,const void* b) {
  if( *(int*)a > *(int*)b) return(1);
  if( *(int*)a < *(int*)b) return(-1);
  return(0);
}

/**
 * M O D I F F U N C T I O N ()
 * Function  to be applied to every node of the
 * red-black tree. It works as a display function
 * showing node value and node depth
 * Comment to be deleted if considered useless.
 */
void ModifFunction(void* data, int dep ){
  printf("Dep= %d Val =%s, ",dep,(char*)data);
}

int main(){

  struct bu_rb_tree *TestTree;
  void *searched_value;
  char *sources[] = {"h","e","a","l","l","o"};
  int i = 0; 
  int Diagnosis_option = 0;
  TestTree = bu_rb_create1("TestingTree",Cmpf);
  for (i = 0; i < 6; i++)
    bu_rb_insert(TestTree,sources[i]);

  printf("SEARCH TEST: \n"
	 "\tSEARCHING AN EXISTING VALUE:\n");

  searched_value = bu_rb_search(TestTree,0,"h");
  if(searched_value==NULL)
    {
      printf("\t\t\t[FAILED]\n"
	     "\t\t\tShould be h \n");
    }
  else
    printf("\t\t\t[PASSED]\n");


  printf("\tSEARCHING AN INEXISTANT VALUE:\n");
  searched_value = bu_rb_search(TestTree,0,"not");
  if(searched_value == NULL)
    {	printf("\t\t\t[PASSED]\n");
/**
* Fails this test on purpose , it should've been compared to
* rb_null(tree) instead. Comparison would probably require a cast.
* Let me know if I should change it .
*/
    }
  else
    printf("\t\t\t[FAILED]\n"
	   "\t\t\tShould be NULL\n");


  printf("DELETE TEST: \n"
	 "\tDELETING AN EXISTENT VALUE:\n");
  searched_value = bu_rb_search(TestTree,0,"a");
  bu_rb_delete(TestTree,0);

  printf("\tSEARCHING THE SAME VALUE AFTER DELETION \n");
  searched_value = bu_rb_search(TestTree,0,"h");
  if(searched_value == NULL)
    {	printf("\t\t\t[PASSED]\n");

    }
  else
    printf("\t\t\t[FAILED]\n"
	   "\t\t\tShould be NULL\n");



  printf("/RED-BLACK TREE WALKING TESTS :\n");
  printf("Input 1 to display the values walk or 0 for a more"
	 "detailed diagnosis display\n");
  scanf("%d",&Diagnosis_option);
  if (Diagnosis_option != 1 && Diagnosis_option != 0) {
																																																																																								
    printf("ERROR AT CHOICE INPUT\n");
    return 0;
  }
  if (Diagnosis_option == 1){
    printf("\nPREORDER:\n");
    bu_rb_walk(TestTree,0,ModifFunction,0);	
    searched_value = bu_rb_search(TestTree,0,"h");
    rb_rot_right(TestTree->rbt_current,0);
    printf("\nPREORDER AFTER ROTATE RIGH:\n");
    bu_rb_walk(TestTree,0,ModifFunction,0);
    printf("\nINORDER:\n");
    bu_rb_walk(TestTree,0,ModifFunction,1);
    printf("\n");
    printf("\nPOSTORDER\n");
    bu_rb_walk(TestTree,0,ModifFunction,2);
    printf("\n");
  }
  else {
    printf("\nPREORDER:\n");
    bu_rb_diagnose_tree(TestTree,0,0);
    searched_value = bu_rb_search(TestTree,0,"h");
    rb_rot_right(TestTree->rbt_current,0);
    printf("\nPREORDER AFTER ROTATE RIGH:\n");
    bu_rb_diagnose_tree(TestTree,0,0);
    printf("\nINORDER:\n");
    bu_rb_diagnose_tree(TestTree,0,1);
    printf("\nPOSTORDER\n");
    bu_rb_diagnose_tree(TestTree,0,2);
  }																																																																																																																																																											return 0;
}


/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
