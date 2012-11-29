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
 *  Test unit for  pkg_open()
 */

/* maximum number of digits on a port number */
#define MAX_DIGITS	5

/* system headers */
#include <string.h>
#include <stdio.h>

/* interface headers */
#include "bu.h"
#include "pkg.h"

/*  Verify test condition and print result.
 *  Mode == 1 is used when condition should be true in order to pass
 *  Mode == 0 is used condition  should  be   false in order to pass
 */
void display(struct pkg_conn *value, int mode, int *passedTests) {
    if (mode == 1) {
        if (value != PKC_ERROR) {
            printf ("\t\t\t [ PASSED ] \n");
            (*passedTests)++;
        } else {
            printf ("\t\t\t [ FAILED ]\n");
            return;
        }
    } else {
        if (value != PKC_ERROR) {
            printf ("\t\t\t [ FAILED ]\n");
	    } else {
            printf ("\t\t\t [ PASSED ] \n");
            (*passedTests)++;
	    }
    }
}

/**
 * print a usage statement when invoked with bad or no arguments
 */
void usage() {
    printf("\nUSAGE : test_pkg_open < port >\n");
    printf(" IN ORDER TO RUN THIS TEST YOU MUST  FIRST RUN ./tpkg -R -p < port >\n");
    printf(" PORT HAS TO BE THE EXACT SAME VALUE PASSED AS PARAMETER TO  test_pkg_open\n\n");
}

int test_pkg_open(char* cport) {
    struct pkg_conn *result;
    char *server;
    int port;

    /* okTests - Count the number of tests passed to determine the
     *  return status of the test function.
     */
    int okTests;
    char s_port[MAX_DIGITS + 1] = {0};

    usage();
    okTests = 0;
    port = atoi(cport);
    snprintf(s_port, MAX_DIGITS, "%d", port);

    server = (char *) bu_malloc(20 * sizeof(char), "server address");

    printf("TESTING PKG_OPEN...\n");
    strcpy(server, "127.0.0.1");
    printf("TESTING VALID SERVER ...");
    result = pkg_open(server, s_port, "tcp", NULL, NULL, NULL, NULL);
    display(result, 1, &okTests);

    printf("TESTING INVALID SERVER...");
    strcpy(server, "0.1.5.1");
    result = pkg_open(server, s_port, "tcp", NULL, NULL, NULL, NULL);
    display(result, 0, &okTests);

    strcpy(server, "127.0.0.1");
    printf("TESTING VALID PORT ...\t");
    result = pkg_open(server, s_port, "tcp", NULL, NULL, NULL, NULL);
    display(result, 1, &okTests);

    printf("TESTING INVALID PORT ...");
    port = 1;
    snprintf(s_port, MAX_DIGITS, "%d", port);
    result = pkg_open(server, s_port, "tcp", NULL, NULL, NULL, NULL);
    display(result, 0, &okTests);

    printf("TESTING VALID PROTOCOL...");
    port = atoi(cport);
    snprintf(s_port, MAX_DIGITS, "%d", port);
    result = pkg_open(server, s_port, "tcp", NULL, NULL, NULL, NULL);
    display(result, 1, &okTests);

    printf("TESTING INVALID PROTOCOL...");
    result = pkg_open(server, s_port, "null", NULL, NULL, NULL, NULL);
    display(result, 1, &okTests);

    bu_free(server, "server name string");

    if (okTests != 6) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[]) {
    int retVal;
    if (argc != 2) {
        usage();
        return 1;
    }
    retVal = test_pkg_open(argv[1]);
    return retVal;
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
