/*                     T E S T _ P K G _ S T R E A M . C
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
 *  Test unit for  pkg_stream()
 */

#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bu.h"

#include <errno.h>
#include "pkg.h"

void printResult(int result , int tabsnumber) {
    int i;

    for (i = 0; i < tabsnumber; i++)
	printf("\t");

    if (result < 0)
        printf (" [ PASSED ]\n");
    else
        printf(" [ FAILED ] \n");
    return ;

}
int test_pkg_stream() {
    int result;
    struct pkg_conn *mock;
    mock = (struct pkg_conn *)
	bu_malloc(sizeof(struct pkg_conn), "mock");
    printf("TESTING PKG_STREAM...\n");

    result = pkg_stream(1, NULL, 0, mock);
    printf("TESTING type == 1");
    printResult(result, 6);
    result = pkg_stream(-5, NULL, 0, mock);
    printf("TESTING type < 0");
    printResult(result, 6);
    result = pkg_stream(99999999, NULL, 0, mock);
    printf("TESTING type = 99999999");
    printResult(result, 6);

    result = pkg_stream(1, " Test String ", 0, mock);
    printf("TESTING string non null and string len == 0");
    printResult(result, 3);
    result = pkg_stream(1, " Test String ", 12, mock);
    printf("TESTING string non null and string len correct");
    printResult(result, 3);
    result = pkg_stream(1, " Test String ", 12, NULL);
    printf("TESTING null pkg_conn parameter");
    printResult(result, 5);
    result = pkg_stream(1, " Test String ", -1, mock);
    printf("TESTING  non null string and string len negative");
    printResult(result, 2);

    printf("TESTING pkg_conn parameters\n");

    mock->pkc_fd = -1;
    result = pkg_stream(1, " Test String ", 12, mock);
    printf ("TESTING negative file descriptor parameter");
    printResult(result, 3);

    mock->pkc_fd = 10;
    result = pkg_stream(1, " Test String ",12, mock);
    printf ("TESTING positive file descriptor (small number ) parameter");
    printResult(result, 1);
    mock->pkc_fd = 9999999;
    result = pkg_stream(1, " Test String ",12, mock);
    printf ("TESTING positive file descriptor (large number ) parameter");
    printResult(result, 1);

    mock->pkc_len = -1;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative package length (pkc_len)");
    printResult(result, 3);
    mock->pkc_len = 0;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING null package length (pkc_len)");
    printResult(result, 4);
    mock->pkc_len = 9999999;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING large package length (pkc_len)");
    printResult(result, 4);

    mock->pkc_type = -9999;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative package type (pkc_type)");
    printResult(result, 3);
    mock->pkc_type = 0;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING null package type (pkc_type)");
    printResult(result, 4);

    mock->pkc_user_data = NULL;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING null user data (pkc_user_data)");
    printResult(result, 4);

    mock->pkc_magic = 0 ;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING null package magic(pkg_magic)");
    printResult(result, 4);
    mock->pkc_magic = 999999 ;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING large package magic(pkg_magic)");
    printResult(result, 4);

    mock->pkc_strpos = -1;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative string position(pkc_strpos)");
    printResult(result, 3);
    mock->pkc_incur = -1;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative current position(pkc_incur)");
    printResult(result, 3);
    mock->pkc_incur = 99999;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING large current position(pkc_incur)");
    printResult(result, 3);


    mock->pkc_inend = -1;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative first unused position(pkc_inend)");
    printResult(result, 2);
    mock->pkc_inend = 99999;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING large first unused position(pkc_inend)");
    printResult(result, 3);

    mock->pkc_inlen = -1;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative pkc_inbuf length (pkc_inlen)");
    printResult(result, 3);
    mock->pkc_inlen = 99999;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING large pkc_inbuf length (pkc_inlen)");
    printResult(result, 3);

    mock->pkc_left = -1;
    result = pkg_stream(1, " NULL",0, mock);
    printf ("TESTING negative bytes left to read parameter (pkc_left)");
    printResult(result, 1);
    bu_free(mock, "release memory used by pkg_conn");
    return 0;
}
int main () {
    int result ;

    result = - 1;
    result = test_pkg_stream();

    return result;
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
