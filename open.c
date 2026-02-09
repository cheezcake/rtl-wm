/*
 * Copyright 1988 by Siemens Research and Technology Laboratories, Princeton, NJ
 *
 *                         All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Siemens Research and Technology
 * Laboratories not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission.
 *
 *
 * SIEMENS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * SIEMENS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */
#include "copyright.h"

#include <stdio.h>
#include "std_defs.h"

static char *homenv;
static char *basenv;
static char *rtlenv;

extern char *getenv();

/* ------------------------------------------------------------ */

static void pathify( str, str1, str2 )
    char *str, *str1, *str2;
{
    strcpy( str, str1 );
    strcat( str, "/" );
    strcat( str, str2 );
}

/* ------------------------------------------------------------ */

void Open_Init()
{
    char *cur;
    char path[256];

    homenv = getenv("HOME");

    str_copy( basenv, homenv );
    cur = basenv + strlen(basenv);
    while ( *cur != '/' )
        cur--;
    *cur = '\0';    

    rtlenv = getenv("RTLENV");
    if ( rtlenv != NULL )
    {
        if ( rtlenv[0] == '~' )
        {
            if ( rtlenv[1] == '/' )
                pathify( path, homenv, rtlenv + 2 );
            else
                pathify( path, basenv, rtlenv + 1 );
            str_copy( rtlenv, path );
        }
	else if ( rtlenv[0] != '/' )
        {
	    pathify( path, homenv, rtlenv );
            str_copy( rtlenv, path );
        }
    }
}

/* ------------------------------------------------------------ */

FILE* Open_Read( filnam )
    char *filnam;
{
    char path[256];
    FILE *stream;

    if ( filnam == NULL )
        return (FILE *)NULL;

    if ( filnam[0] == '/' )
        return fopen( filnam, "r" );

    if ( filnam[0] == '~' )
    {
        if ( filnam[1] == '/' )
            pathify( path, homenv, filnam + 2 );
        else
            pathify( path, basenv, filnam + 1 );
        return fopen( path, "r" );
    }

    if ( rtlenv != NULL )
    {
        pathify( path, rtlenv, filnam );
        stream = fopen( path, "r" );
        if ( stream != NULL )
            return stream;
    }

    pathify( path, homenv, filnam );
    return fopen( path, "r" );
}

/* ------------------------------------------------------------ */

typedef bool	(*BoolFunc)();

bool Open_Read_With( filnam, fn )
    char *filnam;
    BoolFunc fn;
{
    char path[256];

    if ( filnam == NULL )
        return FALSE;

    if ( filnam[0] == '/' )
        return fn( filnam );

    if ( filnam[0] == '~' )
    {
        if ( filnam[1] == '/' )
            pathify( path, homenv, filnam + 2 );
        else
            pathify( path, basenv, filnam + 1 );
        return fn( path );
    }

    if ( rtlenv != NULL )
    {
        pathify( path, rtlenv, filnam );
        if ( fn(path) )
	    return TRUE;
    }

    pathify( path, homenv, filnam );
    return fn( path );
}

/* ------------------------------------------------------------ */

FILE* Open_Write( filnam )
    char *filnam;
{
    char path[256];

    if ( filnam == NULL )
        return (FILE *)NULL;

    if ( filnam[0] == '/' )
        return fopen( filnam, "w" );

    if ( filnam[0] == '~' )
    {
        if ( filnam[1] == '/' )
            pathify( path, homenv, filnam + 2 );
        else
            pathify( path, basenv, filnam + 1 );
        return fopen( path, "w" );
    }

    if ( rtlenv != NULL )
    {
        pathify( path, rtlenv, filnam );
        return fopen( path, "w" );
    }

    pathify( path, homenv, filnam );
    return fopen( path, "w" );
}

/* ------------------------------------------------------------ */

void Open_Execvp( filnam )
    char *filnam;
{
    char path[256];

    if ( filnam[0] == '/' )
        execl( filnam, filnam, 0 );

    else if ( filnam[0] == '~' )
    {
        if ( filnam[1] == '/' )
            pathify( path, homenv, filnam + 2 );
        else
            pathify( path, basenv, filnam + 1 );
        execl( path, path, 0 );
    }

    else
    {
        Open_Init();
        if ( rtlenv != NULL )
        {
            pathify( path, rtlenv, filnam );
            execl( path, path, 0 );
        }
    
        pathify( path, homenv, filnam );
        execl( path, path, 0 );
        
        execl( filnam, filnam, 0 );
    }
}

/* ------------------------------------------------------------ */

void Open_Exec( cmd )
    char *cmd;
{
    char cmdbuf[256];
    
    strcpy(cmdbuf, "exec ");
    strcat(cmdbuf, cmd);
    execl( "/bin/sh", "sh", "-c", cmdbuf, 0 );
}

