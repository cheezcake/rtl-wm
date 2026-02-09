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

#include "basetype.h"

#include "client.h"
#include "tilemenu.h"

extern FILE* Open_Read();

/* ------------------------------------------------------------ */

typedef struct {

    char *menu_name;
    char *cmd_line;
    
} Tool;

#define ToolMax 60

static int numtools = 0;

Tool tool[ToolMax];
                                    
/* ------------------------------------------------------------ */

bool Tool_Init( manager_tool_menu, invoker )
    TileMenu manager_tool_menu;
    VoidFunc invoker;
{
    FILE *stream;
    char cmdstr[256], menustr[128];
    char *cmdlin;

    stream = Open_Read( ".rtl.tools" );
    if ( stream != NULL )
    {
        while ( fgets( menustr, 128, stream ) != NULL )
        {
            cmdlin = cmdstr;
            if ( fgets( cmdlin, 256, stream ) != NULL )
            {
                menustr[ strlen(menustr) - 1 ] = '\0';
                str_copy( tool[numtools].menu_name, menustr );

                TileMenu_Append_Call( manager_tool_menu,
                    tool[numtools].menu_name, invoker,
                    (pointer)numtools );

                while ( (*cmdlin != '\0') &&
                        ( (*cmdlin == ' ') || (*cmdlin == '\t') ) )
                    cmdlin++;                        
                cmdlin[ strlen(cmdlin) - 1 ] = '\0';
                str_copy( tool[numtools].cmd_line, cmdlin );

                numtools++;                    
            }
        }
        fclose ( stream );
    }
    return (numtools > 0);
}

/* ------------------------------------------------------------ */

void Tool_Invoke( num )
    int num;
{
    if ( num < numtools )
        Client_Window_Create( tool[num].cmd_line );
}

/* ------------------------------------------------------------ */

void Tool_Initiate()
{
    Client_Startup( ".rtl.startup" );
}

