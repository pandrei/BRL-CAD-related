/*                     T E S T _ P K G _ C L O S E . C
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
 *  Test unit for  pkg_close()
 */

#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bu.h"

#include <errno.h>
#include "pkg.h"


int test_pkg_close (void ) {
    struct pkg_conn *tester;

    tester = (struct pkg_conn *)
	bu_malloc(sizeof(struct pkg_conn), "tester");
    printf("TESTING PKG_CLOSE..\n");

    printf("TESTING pkg_conn parameters\n");
    tester->pkc_magic = PKG_MAGIC;
    /*
     * Error case was solved by adding a condition in pkg.c - pkg_close();

    printf ("TESTING negative file descriptor parameter...\n");
    tester->pkc_fd = -1;
    pkg_close(tester);

    */

    /* Error case was solved by adding a condition in pkg.c - pkg_close();

    printf ("TESTING positive file descriptor (small number ) parameter...\n");
    tester->pkc_fd = 10;
    pkg_close(tester);

    */

    /*
     * Error case was solved by adding a condition in pkg.c - pkg_close();

    tester->pkc_fd = 10;
    tester->pkc_magic = PKG_MAGIC;
    printf ("TESTING positive file descriptor (large number ) parameter...\n");
    tester->pkc_fd = 50000;
    pkg_close(tester);

    */


    tester = (struct pkg_conn *)
    	bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    printf ("TESTING negative package length (pkc_len)...\n");
    tester->pkc_len = -1;
    pkg_close(tester);





    tester = (struct pkg_conn *)
        	bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING null package length (pkc_len)...\n");
    tester->pkc_len = 0;
    pkg_close(tester);



    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING large package length (pkc_len)...\n");
    tester->pkc_len = 999999;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING negative package type (pkc_type)...\n");
    tester->pkc_type = -9999;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING null package type (pkc_type)...\n");
    tester->pkc_type = 0;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING null user data (pkc_user_data)...\n");
    tester->pkc_user_data = NULL;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING negative string position(pkc_strpos)...\n");
    tester->pkc_strpos = -1;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING negative current position(pkc_incur)...\n");
    tester->pkc_incur = -1;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING large current position(pkc_incur)...\n");
    tester->pkc_incur = 99999;
    pkg_close(tester);

    tester = (struct pkg_conn *)
           	bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING negative first unused position(pkc_inend)...\n");
    tester->pkc_inend = -1;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING large first unused position(pkc_inend)...\n");
    tester->pkc_inend = 99999;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING negative pkc_inbuf length (pkc_inlen)...\n");
    tester->pkc_inlen = -1;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING large pkc_inbuf length (pkc_inlen)...\n");
    tester->pkc_inlen = 99999;
    pkg_close(tester);

    tester = (struct pkg_conn *)
            bu_malloc(sizeof(struct pkg_conn), "tester");
    tester->pkc_magic = PKG_MAGIC;
    tester->pkc_fd = 10;
    printf ("TESTING negative bytes left to read parameter (pkc_left)...\n");
    tester->pkc_left = -1;
    pkg_close(tester);

    printf("All tests succeeded !\n");
    return 0;
}

int main () {
    test_pkg_close();
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
