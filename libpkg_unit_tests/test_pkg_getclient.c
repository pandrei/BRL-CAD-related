/*                     T E S T _ P K G _ G E T C L I E N T . C
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
 *  Test unit for  pkg_getclient()
 */


#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bu.h"

#include <errno.h>
#include "pkg.h"

#define MAGIC_ID	"TPKG"
#define MSG_HELO	1
#define MSG_DATA	2
#define MSG_CIAO	3

/*
 *  need to find a way to deal with duplication
 */

/* maximum number of digits on a port number */
#define MAX_DIGITS	5

void
server_helo(struct pkg_conn *UNUSED(connection), char *buf) {
    bu_log("Unexpected HELO encountered\n");
    free(buf);
}


/**
 * callback when a DATA message packet is received
 */
void server_data(struct pkg_conn *UNUSED(connection), char *buf) {
    bu_log("Received file data\n");
    free(buf);
}


/**
 * callback when a CIAO message packet is received
 */
void server_ciao(struct pkg_conn *UNUSED(connection), char *buf) {
    bu_log("CIAO encountered\n");
    free(buf);
}
void server_custom_msg(struct pkg_conn *UNUSED(connection), char *buf) {
    bu_log("Custom MSG encountered\n");
    free(buf);
}

void server_null_msg(struct pkg_conn *UNUSED(connection), char *buf) {
    bu_log("NULL MSG encountered\n");
    free(buf);
}

/* client = pkg_getclient(netfd, callbacks, NULL, 0); */
int test_pkg_getclient (char* portname) {
    struct pkg_switch callbacks[] = {
	{MSG_HELO, server_helo, "HELO", NULL},
	{MSG_DATA, server_data, "DATA", NULL},
	{MSG_CIAO, server_ciao, "CIAO", NULL},
	{0, 0, (char *)0, (void*)0}
    };
    struct pkg_switch wrongCallbacks[] = {
	{4, server_custom_msg, "Wrong", NULL},
	{5, server_null_msg, "", NULL},
	{0, 0, (char *)0, (void* )0 }
    };
    int netfd;
    struct pkg_conn *result;

    printf("TESTING PKG_GETCLIENT...\n");
    netfd = -1;
    result = pkg_getclient(netfd,callbacks, NULL, 0);
    printf("TESTING INVALID FILE DESCRIPTOR ");
    if (result  == PKC_NULL) {
        printf ("\t[ FAILED ]");
    } else {
        printf ("\t[ PASSED ]\n");
    }

    printf("TESTING INVALID CALLBACKS ");

    result = pkg_getclient(2, wrongCallbacks, NULL, 0);
    if (result  == PKC_NULL) {
        printf ("\t[ FAILED ]");
    } else {
        printf ("\t\t[ PASSED ]\n");
    }

    printf("TESTING VALID PARAMETERS ");
    netfd = pkg_permserver(portname, "tcp", 0, 0);
    result = pkg_getclient(3, callbacks, NULL, 0);
    if (result  == PKC_ERROR){
        printf ("\t\t[ PASSED ]\n");
    } else {
        printf ("\t[ FAILED ]\n");
    }


    return 0;
}


int main (int argc, char* argv[]) {
    test_pkg_getclient(argv[1]);
    printf("%d",argc);
    return 0;
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

