/*                     T E S T _ P K G _ P E R M S E R V . C
 * BRL-CAD
 *
 * Copyright (c) 2012 United States Government as represented by
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
 /*
  *  Test unit for  pkg_permserver() and pkg permserver_ip()
  */

#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bu.h"

#include <errno.h>
#include "pkg.h"

void display(int ret_val, int mode, int *passed_tests_cnt) {
    if (mode == 0) {
	   if (ret_val >= 0) {
	       printf(" [ FAILED ] \n");
	   } else {
            printf(" [ PASSED ] \n ");
            (*passed_tests_cnt)++;
	   }
    } else {
	   if (ret_val < 0) {
	       printf(" [ FAILED ] \n");
	   } else {
	       printf(" [ PASSED ] \n");
            (*passed_tests_cnt)++;
	   }
    }
}

int test_permserv(char *port) {
    int return_val;
    int num_port;
    char *chr_port;
    int nr_test_passed;
    chr_port = (char *) bu_malloc(8 * sizeof(char), "port string");
    nr_test_passed = 0;
    printf("TESTING  PKG_PERMSERVER...\n");

    printf("TESTING VALID PORT...\t\t\t");
    return_val = pkg_permserver(port, "tcp", 0, 0);
    display(return_val, 1, &nr_test_passed);

    printf("TESTING INVALID PORT...\t\t\t");
    num_port = -1;
    sprintf(chr_port, "%d", num_port);
    return_val = pkg_permserver(chr_port, "tcp", 0, 0);
    display(return_val, 0, &nr_test_passed);

    printf("TESTING VALID PROTOCOL...\t\t");
    num_port = atoi(port) + 1;
    sprintf(chr_port, "%d", num_port);
    return_val = pkg_permserver(chr_port, "tcp", 0, 0);
    display(return_val, 1, &nr_test_passed);

    printf("TESTING INVALID PROTOCOL...\t\t");
    num_port++;
    sprintf(chr_port, "%d", num_port);
    return_val = pkg_permserver(chr_port, "not_valid", 0, 0);
    display(return_val, 1, &nr_test_passed);

    printf("TESTING VALID BACKLOG...\t\t");
    num_port++;
    sprintf(chr_port, "%d", num_port);
    return_val = pkg_permserver(chr_port, "tcp", 0, 0);
    display(return_val, 1, &nr_test_passed);

    printf("TESTING INVALID NEGATIVE BACKLOG...\t");
    num_port++;
    sprintf(chr_port, "%d", num_port);
    return_val = pkg_permserver(chr_port, "tcp", -1, 0);
    display(return_val, 1, &nr_test_passed);

    printf("TESTING INVALID POSITIVE BACKLOG...\t");
    num_port++;
    sprintf(chr_port, "%d", num_port);
    return_val = pkg_permserver(chr_port, "tcp", 9999, 0);
    display(return_val, 1, &nr_test_passed);

    bu_free(chr_port, "String port");
    if (nr_test_passed != 7)
	   return 1;
    else
	   return 0;
}

int test_permserv_ip(char *port) {
    int return_val;
    int ok_tests;
    printf("TESTING  PKG_PERMSERVER_IP...\n TESTING VALID IP...\t\t\t");
    ok_tests = 0;
    return_val = pkg_permserver_ip("127.0.0.1", port ,"tcp", 0, 0);
    display(return_val, 1, &ok_tests);
    printf("TESTING INVALID IP...\t\t\t");
    return_val = pkg_permserver_ip("203.0.133.1", port, "tcp", 0, 0);
    display(return_val, 0, &ok_tests);
    if (ok_tests != 2)
	   return 1;
    else
	   return 0;
}

int main(int argc, char *argv[]) {
    int val1, val2, num_port;
    char *chr_port;
    printf("\nUSAGE : ./test_pkg_permserver < AVAILABLE_PORT >  \n\n");
    if (argc != 2)
	   return -1;
    num_port = atoi(argv[1]);
    num_port = num_port + 100;
    chr_port = (char *) bu_malloc(8 * sizeof(char), "port string");
    sprintf(chr_port, "%d", num_port);
    val1 = test_permserv(argv[1]);
    val2 = test_permserv_ip(chr_port);
    bu_free(chr_port, "String port");
    if (val1 == 0 && val2 == 0)
	   return 0;
    return 1;
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
