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

#include "layout.h"
#include "region.h"
#include "twinD.h"
#include "uwinD.h"
#include "uwin.h"
#include "tilemenu.h"

#include "tileoptsS.h"
#include "twinoptsS.h"
#include "useroptsS.h"
#include "uwinoptS.h"

#include "uwinstrP.h"
#include "uwinstrS.h"

#include "uservalsS.h"
#include "uwinvalP.h"
#include "uwinvalS.h"

#include "synonymsS.h"

extern Size Icons_Set();

Size abs_min_siz, abs_max_siz;

extern FILE *Open_Read();

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                       PROFILE_MENU                           */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static TileMenu profiles;
static VoidFunc callproc;

/* ------------------------------------------------------------ */

static void Profile_Menu_Init( menu, proc )
    TileMenu menu;
    VoidFunc proc;
{
    callproc = proc;
    profiles = TileMenu_Create();
    TileMenu_Append_Call( profiles, "Preferences", callproc, NULL );
    TileMenu_Append_Submenu( menu, "Read Profile", profiles );
}

/* ------------------------------------------------------------ */

static void Profile_Menu_Read()
{
    FILE *stream;
    char filnams[256], menustr[128];
    char *filnamx, *menustrx;

    TileMenu_Delete_Entries( profiles );
    TileMenu_Append_Call( profiles, "Preferences", callproc, NULL );

    stream = Open_Read( ".rtl.profiles" );
    if ( stream != NULL )
    {
        while ( fgets( menustr, 128, stream ) != NULL )
        {
            if ( fgets( filnams, 256, stream ) != NULL )
            {
                menustr[ strlen(menustr) - 1 ] = '\0';
                str_copy( menustrx, menustr );

                filnams[ strlen(filnams) - 1 ] = '\0';
                str_copy( filnamx, filnams );

                TileMenu_Append_Call( profiles, menustrx, callproc, filnamx );
            }
        }
        fclose ( stream );
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                      CLASSES                                 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

typedef struct class Class;

struct class
{
    Class *next;
    char *name;
    Class *super;
    char *super_name;
    int prefnum;
    bool options[(int)LENGTH_WINDOW_OPTIONS];
    bool user_options[(int)LENGTH_USER_WINDOW_OPTIONS];
    int user_values[(int)LENGTH_USER_WINDOW_VALUES];
    char *user_strings[(int)LENGTH_USER_WINDOW_STRINGS];
    bool has_options[(int)LENGTH_WINDOW_OPTIONS];
    bool has_user_options[(int)LENGTH_USER_WINDOW_OPTIONS];
    bool has_user_values[(int)LENGTH_USER_WINDOW_VALUES];
    bool has_user_strings[(int)LENGTH_USER_WINDOW_STRINGS];
};

#define CLASS_NULL ((Class *)NULL)

static Class default_class;
static Class *default_classp = &default_class;
static Class *class_head = CLASS_NULL;

static int prefnum;

/* ------------------------------------------------------------ */

#define Tilwin_Set_Class_Option(classp,opt,val) \
{  \
    (classp)->options[(int)(opt)] = (val);  \
    (classp)->has_options[(int)(opt)] = TRUE;  \
}

#define Tilwin_Set_Default_Option(opt,val) \
    Tilwin_Set_Class_Option(default_classp,opt,val)

/* ------------------------------------------------------------ */

#define Userwin_Set_Class_Option(classp,opt,val) \
{  \
    (classp)->user_options[(int)(opt)] = (val);  \
    (classp)->has_user_options[(int)(opt)] = TRUE;  \
}

#define Userwin_Set_Default_Option(opt,val) \
    Userwin_Set_Class_Option(default_classp,opt,val)

/* ------------------------------------------------------------ */

#define Userwin_Set_Class_Value(classp,opt,val) \
{  \
    (classp)->user_values[(int)(opt)] = (val);  \
    (classp)->has_user_values[(int)(opt)] = TRUE;  \
}

#define Userwin_Set_Default_Value(opt,val) \
    Userwin_Set_Class_Value(default_classp,opt,val)

#define Userwin_Cond_Set_Default_Value(opt,val)  \
{  \
    if (! default_classp->has_user_values[(int)(opt)] )  \
        Userwin_Set_Default_Value(opt,val)  \
}

/* ------------------------------------------------------------ */

#define Userwin_Set_Class_String(classp,opt,val) \
{  \
    str_copy( (classp)->user_strings[(int)(opt)], val );  \
    (classp)->has_user_strings[(int)(opt)] = TRUE;  \
}

#define Userwin_Set_Default_String(opt,val) \
    Userwin_Set_Class_String(default_classp,opt,val)

/* ------------------------------------------------------------ */

static void Profile_Class_Reset( classp )
    Class *classp;
{
    int i;
    
    for ( i = 0; i < (int)LENGTH_WINDOW_OPTIONS; i++ )
        classp->has_options[i] = FALSE;

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_OPTIONS; i++ )
        classp->has_user_options[i] = FALSE;
    
    for ( i = 0; i < (int)LENGTH_USER_WINDOW_VALUES; i++ )
        classp->has_user_values[i] = FALSE;
    
    for ( i = 0; i < (int)LENGTH_USER_WINDOW_STRINGS; i++ )
    {
        classp->has_user_strings[i] = FALSE;
        classp->user_strings[i] = NULL;
    }

    classp->super = CLASS_NULL;
    classp->super_name = NULL;
    classp->prefnum = 0;
}

/* ------------------------------------------------------------ */

#define Profile_Default_Class_Reset()  \
    Profile_Class_Reset( default_classp );

/* ------------------------------------------------------------ */

bool Profile_Get_Class_Option( classp, namep, opt )
    Class *classp;
    Class *namep;
    Window_Options opt;
{
    while ( namep != CLASS_NULL )
    {
        if ( namep->has_options[(int)opt] )
            return namep->options[(int)opt];
        namep = namep->super;
    }

    while ( classp != CLASS_NULL )
    {
        if ( classp->has_options[(int)opt] )
            return classp->options[(int)opt];
        classp = classp->super;
    }

    return default_classp->options[(int)opt];
}

/* ------------------------------------------------------------ */

bool Profile_Get_User_Class_Option( classp, namep, opt )
    Class *classp;
    Class *namep;
    User_Window_Options opt;
{
    while ( namep != CLASS_NULL )
    {
        if ( namep->has_user_options[(int)opt] )
            return namep->user_options[(int)opt];
        namep = namep->super;
    }

    while ( classp != CLASS_NULL )
    {
        if ( classp->has_user_options[(int)opt] )
            return classp->user_options[(int)opt];
        classp = classp->super;
    }

    return default_classp->user_options[(int)opt];
}

/* ------------------------------------------------------------ */

bool Profile_Has_User_Class_Value( classp, namep, opt )
    Class *classp;
    Class *namep;
    User_Window_Values opt;
{
    while ( namep != CLASS_NULL )
    {
        if ( namep->has_user_values[(int)opt] )
            return TRUE;
        namep = namep->super;
    }

    while ( classp != CLASS_NULL )
    {
        if ( classp->has_user_values[(int)opt] )
            return TRUE;
        classp = classp->super;
    }

    return FALSE;
}

/* ------------------------------------------------------------ */

int Profile_Get_User_Class_Value( classp, namep, opt )
    Class *classp;
    Class *namep;
    User_Window_Values opt;
{
    while ( namep != CLASS_NULL )
    {
        if ( namep->has_user_values[(int)opt] )
            return namep->user_values[(int)opt];
        namep = namep->super;
    }

    while ( classp != CLASS_NULL )
    {
        if ( classp->has_user_values[(int)opt] )
            return classp->user_values[(int)opt];
        classp = classp->super;
    }

    return default_classp->user_values[(int)opt];
}

/* ------------------------------------------------------------ */

bool Profile_Has_User_Class_String( classp, namep, opt )
    Class *classp;
    Class *namep;
    User_Window_Strings opt;
{
    while ( namep != CLASS_NULL )
    {
        if ( namep->has_user_strings[(int)opt] )
            return TRUE;
        namep = namep->super;
    }

    while ( classp != CLASS_NULL )
    {
        if ( classp->has_user_strings[(int)opt] )
            return TRUE;
        classp = classp->super;
    }

    return FALSE;
}

/* ------------------------------------------------------------ */

char *Profile_Get_User_Class_String( classp, namep, opt )
    Class *classp;
    Class *namep;
    User_Window_Strings opt;
{
    while ( namep != CLASS_NULL )
    {
        if ( namep->has_user_strings[(int)opt] )
            return namep->user_strings[(int)opt];
        namep = namep->super;
    }

    while ( classp != CLASS_NULL )
    {
        if ( classp->has_user_strings[(int)opt] )
            return classp->user_strings[(int)opt];
        classp = classp->super;
    }

    return default_classp->user_strings[(int)opt];
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                    SETTING UP A WINDOW                       */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Profile_Set_Info( classp, namep, uwinp )
    Class *classp;
    Class *namep;
    Userwin *uwinp;
{
    uwinp->header_height =
        Profile_Get_User_Class_Value( classp, namep, HEADER_HEIGHT );

    uwinp->icon_body_rect.left_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_BODY_LEFT );
    uwinp->icon_body_rect.right_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_BODY_RIGHT );
    uwinp->icon_body_rect.top_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_BODY_TOP );
    uwinp->icon_body_rect.bottom_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_BODY_BOTTOM );

    uwinp->icon_res_rect.left_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_RES_LEFT );
    uwinp->icon_res_rect.right_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_RES_RIGHT );
    uwinp->icon_res_rect.top_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_RES_TOP );
    uwinp->icon_res_rect.bottom_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_RES_BOTTOM );

    uwinp->icon_host_rect.left_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_HOST_LEFT );
    uwinp->icon_host_rect.right_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_HOST_RIGHT );
    uwinp->icon_host_rect.top_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_HOST_TOP );
    uwinp->icon_host_rect.bottom_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_HOST_BOTTOM );

    uwinp->icon_name_rect.left_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_NAME_LEFT );
    uwinp->icon_name_rect.right_x =
        Profile_Get_User_Class_Value( classp, namep, ICON_NAME_RIGHT );
    uwinp->icon_name_rect.top_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_NAME_TOP );
    uwinp->icon_name_rect.bottom_y =
        Profile_Get_User_Class_Value( classp, namep, ICON_NAME_BOTTOM );

}

/* ------------------------------------------------------------ */

static void Profile_Set_Sizes( classp, namep, uwinp )
    Class *classp;
    Class *namep;
    Userwin *uwinp;
{
    Size size;

    size.width =
        Profile_Get_User_Class_Value( classp, namep,
                                      CLIENT_MIN_WIDTH );
    size.height =
        Profile_Get_User_Class_Value( classp, namep,
                                      CLIENT_MIN_HEIGHT );

    uwinp->body_min = Region_Unadjust_Size( uwinp, size );

    size.width =
        Profile_Get_User_Class_Value( classp, namep,
                                      CLIENT_MAX_WIDTH );
    size.height =
        Profile_Get_User_Class_Value( classp, namep,
                                      CLIENT_MAX_HEIGHT );
    uwinp->body_max = Region_Unadjust_Size( uwinp, size );

    uwinp->regular_min.width =
        Profile_Get_User_Class_Value( classp, namep,
                                      USER_NORMAL_MIN_WIDTH );
    uwinp->regular_min.height =
        Profile_Get_User_Class_Value( classp, namep,
                                      USER_NORMAL_MIN_HEIGHT );

    uwinp->zoom_min.width =
        Profile_Get_User_Class_Value( classp, namep,
                                      USER_ZOOM_MIN_WIDTH );
    uwinp->zoom_min.height =
        Profile_Get_User_Class_Value( classp, namep,
                                      USER_ZOOM_MIN_HEIGHT );

    size.width =
        Profile_Get_User_Class_Value( classp, namep,
                                      USER_MAX_WIDTH );
    size.height =
        Profile_Get_User_Class_Value( classp, namep,
                                      USER_MAX_HEIGHT );

    Tilwin_Set_Max( uwinp->winp, size );
}

/* ------------------------------------------------------------ */

static void Profile_Update_Sizes( classp, namep, uwinp )
    Class *classp;
    Class *namep;
    Userwin *uwinp;
{
    bool sized = TRUE;

    if ( Profile_Has_User_Class_Value( classp, namep,
                                  NORMAL_DESIRED_WIDTH ) )
        uwinp->regular_size.width =
            Profile_Get_User_Class_Value( classp, namep,
                                          NORMAL_DESIRED_WIDTH );
    else
        sized = FALSE;

    if ( Profile_Has_User_Class_Value( classp, namep,
                                  NORMAL_DESIRED_HEIGHT ) )
        uwinp->regular_size.height =
            Profile_Get_User_Class_Value( classp, namep,
                                          NORMAL_DESIRED_HEIGHT );
    else
        sized = FALSE;

    if ( sized )
        uwinp->sized = TRUE;

    if ( Profile_Has_User_Class_Value( classp, namep,
                                  ZOOM_DESIRED_WIDTH ) )
        uwinp->zoom_size.width =
            Profile_Get_User_Class_Value( classp, namep,
                                          ZOOM_DESIRED_WIDTH );

    if ( Profile_Has_User_Class_Value( classp, namep,
                                  ZOOM_DESIRED_HEIGHT ) )
        uwinp->zoom_size.height =
            Profile_Get_User_Class_Value( classp, namep,
                                          ZOOM_DESIRED_HEIGHT );
}

/* ------------------------------------------------------------ */

static void Profile_Update_Icon_Sizes( classp, namep, uwinp )
    Class *classp;
    Class *namep;
    Userwin *uwinp;
{
    Size size;

    size = Tilwin_Get_Size( uwinp->iconp );

    if ( Profile_Has_User_Class_Value( classp, namep,
                                  ICON_WIDTH ) )
        size.width = MAX( 1,
            Profile_Get_User_Class_Value( classp, namep,
                                          ICON_WIDTH ) );

    if ( Profile_Has_User_Class_Value( classp, namep,
                                  ICON_HEIGHT ) )
        size.height = MAX( 1, 
            Profile_Get_User_Class_Value( classp, namep,
                                          ICON_HEIGHT ) );

    size = Icons_Set( uwinp, size,
               Profile_Get_User_Class_String(
                   classp, namep, ICON_PIXMAP_FILE ) );

    Tilwin_Set_Min( uwinp->iconp, size );
    Tilwin_Set_Max( uwinp->iconp, size );
    Tilwin_Set_Size( uwinp->iconp, size );
    Tilwin_Set_Desired( uwinp->iconp, size );
}

/* ------------------------------------------------------------ */

static void Profile_Create_Sizes( uwinp )
    Userwin *uwinp;
{
    TWRectangle rect;
    TWPoint center;
    Size siz;

    uwinp->regular_size.width =
        Profile_Get_User_Class_Value( CLASS_NULL, CLASS_NULL,
                                      NORMAL_DESIRED_WIDTH );
    uwinp->regular_size.height =
        Profile_Get_User_Class_Value( CLASS_NULL, CLASS_NULL,
                                      NORMAL_DESIRED_HEIGHT );
    uwinp->zoom_size.width =
        Profile_Get_User_Class_Value( CLASS_NULL, CLASS_NULL,
                                      ZOOM_DESIRED_WIDTH );
    uwinp->zoom_size.height =
        Profile_Get_User_Class_Value( CLASS_NULL, CLASS_NULL,
                                      ZOOM_DESIRED_HEIGHT );

    rect.left_x = 0;
    rect.top_y = 0;

    Tilwin_Set_Min( uwinp->winp, uwinp->regular_min );
    rect.right_x = uwinp->regular_min.width - 1;
    rect.bottom_y = uwinp->regular_min.height - 1;
    COMPUTE_SIZE( rect, siz );
    COMPUTE_CENTER( rect, center );
    Tilwin_Set( uwinp->winp, center, siz );
    Tilwin_Set_Size( uwinp->winp, uwinp->regular_size );

    siz.width =
        Profile_Get_User_Class_Value( CLASS_NULL, CLASS_NULL,
                                      ICON_WIDTH );
    siz.height =
        Profile_Get_User_Class_Value( CLASS_NULL, CLASS_NULL,
                                      ICON_HEIGHT );

    rect.right_x = siz.width - 1;
    rect.bottom_y = siz.height - 1;
    COMPUTE_SIZE( rect, siz );
    COMPUTE_CENTER( rect, center );

    Tilwin_Set_Min( uwinp->iconp, siz );
    Tilwin_Set_Max( uwinp->iconp, siz );
    Tilwin_Set( uwinp->iconp, center, siz );

    uwinp->rezoom_rect = Tilwin_Get_Desktop_Rectangle();
}

/* ------------------------------------------------------------ */

static void Profile_Default_Sizes()
{
    Size siz;

    abs_max_siz.width = UserGlobals_Get_Value( FULL_WIDTH );
    abs_max_siz.height = UserGlobals_Get_Value( FULL_HEIGHT );

    siz = Region_Minimum_Size();
    abs_min_siz.width = UserGlobals_Get_Value( ABS_MIN_WIDTH );
    abs_min_siz.height = UserGlobals_Get_Value( ABS_MIN_HEIGHT );
    Set_Max_Size( abs_min_siz, abs_min_siz, siz );
    UserGlobals_Set_Value( ABS_MIN_WIDTH, abs_min_siz.width );
    UserGlobals_Set_Value( ABS_MIN_HEIGHT, abs_min_siz.height );

    Userwin_Cond_Set_Default_Value( CLIENT_MIN_WIDTH, 
                                    abs_min_siz.width );
    Userwin_Cond_Set_Default_Value( CLIENT_MIN_HEIGHT, 
                                    abs_min_siz.height );

    Userwin_Cond_Set_Default_Value( CLIENT_MAX_WIDTH, 
                                    abs_max_siz.width );
    Userwin_Cond_Set_Default_Value( CLIENT_MAX_HEIGHT, 
                                    abs_max_siz.height );

    Userwin_Cond_Set_Default_Value( NORMAL_DESIRED_WIDTH,
                                    abs_min_siz.width );
    Userwin_Cond_Set_Default_Value( NORMAL_DESIRED_HEIGHT,
                                    abs_min_siz.height );

    Userwin_Cond_Set_Default_Value( USER_NORMAL_MIN_WIDTH, 
                                    abs_min_siz.width );
    Userwin_Cond_Set_Default_Value( USER_NORMAL_MIN_HEIGHT, 
                                    abs_min_siz.height );

    Userwin_Cond_Set_Default_Value( ZOOM_DESIRED_WIDTH,
                                    abs_min_siz.width );
    Userwin_Cond_Set_Default_Value( ZOOM_DESIRED_HEIGHT,
                                    abs_min_siz.height );

    Userwin_Cond_Set_Default_Value( USER_ZOOM_MIN_WIDTH, 
                                    abs_min_siz.width );
    Userwin_Cond_Set_Default_Value( USER_ZOOM_MIN_HEIGHT, 
                                    abs_min_siz.height );

    Userwin_Cond_Set_Default_Value( USER_MAX_WIDTH, 
                                    abs_max_siz.width );
    Userwin_Cond_Set_Default_Value( USER_MAX_HEIGHT, 
                                    abs_max_siz.height );

}

/* ------------------------------------------------------------ */

static void Profile_Set_Global_Values()
{
    Size siz;

    siz.width = siz.height = 2;
    Tilwin_Set_Absolute_Minimums( siz );
    Tilwin_Set_Gravity( UserGlobals_Get_Value( GRAVITY ) );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                   SETTING OPTIONS BY NAME                    */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Profile_Set_Global_Option( opt, val )
    char *opt, *val;
{
    int i;
    int num;

    for ( i = 0; i < (int)LENGTH_GLOBAL_OPTIONS; i++ )
        if ( streql( opt, global_strs[i] ) )
        {
            if ( streql( val, "on" ) )
                Tilwin_Set_Global_Option( (Global_Options)i, TRUE );
            else
                Tilwin_Set_Global_Option( (Global_Options)i, FALSE );
            return;
        }

    for ( i = 0; i < (int)LENGTH_WINDOW_OPTIONS; i++ )
        if ( streql( opt, window_strs[i] ) )
        {
            if ( streql( val, "on" ) )
                Tilwin_Set_Default_Option( (Window_Options)i, TRUE )
            else
                Tilwin_Set_Default_Option( (Window_Options)i, FALSE )
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_GLOBAL_OPTIONS; i++ )
        if ( streql( opt, user_global_strs[i] ) )
        {
            if ( streql( val, "on" ) )
                UserGlobals_Set_Option( (User_Global_Options)i, TRUE );
            else
                UserGlobals_Set_Option( (User_Global_Options)i, FALSE );
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_OPTIONS; i++ )
        if ( streql( opt, user_window_strs[i] ) )
        {
            if ( streql( val, "on" ) )
                Userwin_Set_Default_Option( (User_Window_Options)i, TRUE )
            else
                Userwin_Set_Default_Option( (User_Window_Options)i, FALSE )
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_GLOBAL_VALUES; i++ )
        if ( streql( opt, user_global_value_strs[i] ) )
        {
            if ( sscanf( val, "%d", &num ) == 1 )
                UserGlobals_Set_Value( (User_Global_Values)i, num );
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_VALUES; i++ )
        if ( streql( opt, user_window_value_strs[i] ) )
        {
            if ( sscanf( val, "%d", &num ) == 1 )
                Userwin_Set_Default_Value( (User_Window_Values)i, num );
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_STRINGS; i++ )
        if ( streql( opt, user_window_string_strs[i] ) )
        {
            Userwin_Set_Default_String( (User_Window_Values)i, val );
            return;
        }

    for ( i = 0; i < (int)LENGTH_SYNONYMS; i += 2 )
        if ( streql( opt, synonym_strs[i] ) )
            Profile_Set_Global_Option( synonym_strs[i+1], val );

}

/* ------------------------------------------------------------ */

static void Profile_Class_Set_Option( classp, opt, val )
    Class *classp;
    char *opt, *val;
{
    int i;
    int num;

    for ( i = 0; i < (int)LENGTH_WINDOW_OPTIONS; i++ )
        if ( streql( opt, window_strs[i] ) )
        {
            if ( streql( val, "on" ) )
                Tilwin_Set_Class_Option( classp, (Window_Options)i, TRUE )
            else
                Tilwin_Set_Class_Option( classp, (Window_Options)i, FALSE )
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_OPTIONS; i++ )
        if ( streql( opt, user_window_strs[i] ) )
        {
            if ( streql( val, "on" ) )
                Userwin_Set_Class_Option( classp, 
                    (User_Window_Options)i, TRUE )
            else
                Userwin_Set_Class_Option( classp,
                    (User_Window_Options)i, FALSE )
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_VALUES; i++ )
        if ( streql( opt, user_window_value_strs[i] ) )
        {
            if ( sscanf( val, "%d", &num ) == 1 )
                Userwin_Set_Class_Value(
                    classp, (User_Window_Values)i, num );
            return;
        }

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_STRINGS; i++ )
        if ( streql( opt, user_window_string_strs[i] ) )
        {
            Userwin_Set_Class_String(
                    classp, (User_Window_Values)i, val );
            return;
        }

    if ( streql( opt, "superClass" ) )
        str_copy( classp->super_name, val );

    for ( i = 0; i < (int)LENGTH_SYNONYMS; i += 2 )
        if ( streql( opt, synonym_strs[i] ) )
            Profile_Class_Set_Option( classp, synonym_strs[i+1], val );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*               ALL CLASSES                                    */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static Class *Profile_Classes_Find_Name( nam )
    char *nam;
{
    Class *classp;
    
    if ( nam == NULL )
        return CLASS_NULL;

    for ( classp = class_head; classp != CLASS_NULL; 
          classp = classp->next )
    {
        if ( streql( nam, classp->name ) )
            return classp;
    }
    return CLASS_NULL;
}

/* ------------------------------------------------------------ */

static Class *Profile_Classes_Add( nam )
    char *nam;
{
    Class *classp;
    classp = allocate( Class, 1 );
    
    classp->next = class_head;
    class_head = classp;

    str_copy( classp->name, nam );

    Profile_Class_Reset( classp );

    return classp;
}

/* ------------------------------------------------------------ */

static Class *Profile_Classes_Get_Name( nam )
    char *nam;
{
    Class *classp;

    classp = Profile_Classes_Find_Name( nam );
    if ( (classp == CLASS_NULL) && (nam != NULL) )
        classp = Profile_Classes_Add( nam );
    return classp;
}

/* ------------------------------------------------------------ */

static void Profile_Classes_Reset()
{
    Class *classp;

    for ( classp = class_head; classp != CLASS_NULL; 
          classp = classp->next )
        Profile_Class_Reset( classp );

    Profile_Default_Class_Reset();

    UserGlobals_Set_Value( ABS_MIN_WIDTH, 2 );
    UserGlobals_Set_Value( ABS_MIN_HEIGHT, 2 );

    prefnum = 0;
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                      READING THE PROFILE                     */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Profile_Read_File( filnam )
    char *filnam;
{    
    char str[256];
    char wmnam[128], nam[128], opt[128], val[128];
    FILE *stream;
    Class *classp;
    
    stream = Open_Read( filnam );
    if ( stream == NULL ) return;
    while ( fgets( str, 256, stream ) != NULL )
    {
            /*  rtl.nam.opt:  */

        if ( sscanf( str, "%[^.]%*c%[^.]%*c%[^:]%*c%s",
                          wmnam, nam, opt, val ) == 4 )
        {
            if ( streql( wmnam, "rtl" ) || 
                 streql( wmnam, "Wm" ) ||
                 streql( wmnam, "*" ) )
            {
                classp = Profile_Classes_Get_Name( nam );
                Profile_Class_Set_Option( classp, opt, val );
            }
        }

            /*  *nam.opt:  */

        else if ( sscanf( str, "*%[^.]%*c%[^:]%*c%s",
                          nam, opt, val ) == 3 )
        {
                classp = Profile_Classes_Get_Name( nam );
                Profile_Class_Set_Option( classp, opt, val );
        }

            /*  rtl.opt:  or  nam.opt:  */

        else if ( sscanf( str, "%[^.]%*c%[^:]%*c%s",
                        nam, opt, val ) == 3 )
        {
            if ( streql( nam, "rtl" ) || 
                 streql( nam, "Wm" ) || 
                 streql( nam, "*" ) )
                Profile_Set_Global_Option( opt, val );
            else
            {
                classp = Profile_Classes_Get_Name( nam );
                Profile_Class_Set_Option( classp, opt, val );
            }
        }
        
            /*  *opt:  */

        else if ( sscanf( str, "*%[^:]%*c%s",
                          opt, val ) == 2 )
        {
                Profile_Set_Global_Option( opt, val );
        }

            /*  rtl*opt:  */

        else if ( sscanf( str, "%[^*]%*c%[^:]%*c%s",
                               wmnam, opt, val ) == 3 )
        {
            if ( streql( wmnam, "rtl" ) || streql( wmnam, "Wm" ) )
                Profile_Set_Global_Option( opt, val );
        }
        
            /*  opt:  */

        else if ( sscanf( str, "%[^:]%*c%s",
                          opt, val ) == 2 )
        {
                Profile_Set_Global_Option( opt, val );
        }
    }
    fclose( stream );
}

/* ------------------------------------------------------------ */

static void Profile_Read_Files( filnams )
    char *filnams;
{
    char *startp, *curp;
    char lastchar;

    startp = filnams;

    while ( *startp != '\0' )
    {
        while ( ( *startp != '\0' ) &&
            ( ( *startp == ' ' ) || ( *startp == '\t' ) ) )
            startp++;
            
        curp = startp;
        
        while ( ( *curp != 0 ) && ( *curp != ' ' ) && ( *curp != '\t' ) )
            curp++;
            
        if ( startp != curp )
        {
            lastchar = *curp;
            *curp = '\0';
            Profile_Read_File( startp );
            *curp = lastchar;
        }
        
        startp = curp;
    }
}

/* ------------------------------------------------------------ */

#include "defaults.i"

void Profile_Read( filnams )
    char *filnams;
{
    Profile_Classes_Reset();

    Profile_Defaults();

    Profile_Read_File( ".Xdefaults" );
    Profile_Read_File( ".rtl.preferences" );
    if ( filnams != NULL )
        Profile_Read_Files( filnams );

    Profile_Default_Sizes();
    Profile_Set_Global_Values();
}

/* ------------------------------------------------------------ */

static void Profile_Super_Preference( classp )
    Class *classp;
{
    char filnam[128];
    
    prefnum++;

    while ( (classp != CLASS_NULL) && (classp->prefnum == 0) )
    {
        classp->prefnum = prefnum;
    
        strcpy( filnam, "." );
        strcat( filnam, classp->name );
        strcat( filnam, ".preferences" );
    
        Profile_Read_File( filnam );
    
        if (! classp->super_name == NULL )
        {
            classp->super =
                Profile_Classes_Get_Name( classp->super_name );
    
            if ( classp->super->prefnum == prefnum )
                classp->super = CLASS_NULL;
        }
        classp = classp->super;
    }
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                EXPLICITLY SET WINDOW OPTIONS                 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static bool explopts[(int)LENGTH_EXPLICIT_WINDOW_OPTIONS];

/* ------------------------------------------------------------ */

static void Profile_Explicit_Clear( uwinp )
    Userwin *uwinp;
{
    int i;

    for ( i = 0; i < (int)LENGTH_EXPLICIT_WINDOW_OPTIONS; i++ )
        Explicit_Window_Clear( uwinp, 
            ((Explicit_Window_Options)(i)) );
}

/* ------------------------------------------------------------ */

static void Profile_Explicit_Save( uwinp )
    Userwin *uwinp;
{
    if ( Explicit_Window_Get( uwinp, EXPLICIT_REQUIRE_MANUAL_CLOSE ) )
        explopts[(int)EXPLICIT_REQUIRE_MANUAL_CLOSE] =
            Tilwin_Get_Window_Option( uwinp->winp, REQUIRE_MANUAL_CLOSE );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_FIXED_WIDTH ) )
        explopts[(int)EXPLICIT_FIXED_WIDTH] =
            Tilwin_Get_Window_Option( uwinp->winp, FIXED_WIDTH );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_FIXED_HEIGHT ) )
        explopts[(int)EXPLICIT_FIXED_HEIGHT] =
            Tilwin_Get_Window_Option( uwinp->winp, FIXED_HEIGHT );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_FIXED_COMPLETELY ) )
        explopts[(int)EXPLICIT_FIXED_COMPLETELY] =
            Tilwin_Get_Window_Option( uwinp->winp, FIXED_COMPLETELY );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_LISTENER_TIED_TO_ZOOM ) )
        explopts[(int)EXPLICIT_LISTENER_TIED_TO_ZOOM] =
            Userwin_Get_Window_Option( uwinp, LISTENER_TIED_TO_ZOOM );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_ZOOM_TIED_TO_DESIRE ) )
        explopts[(int)EXPLICIT_ZOOM_TIED_TO_DESIRE] =
            Userwin_Get_Window_Option( uwinp, ZOOM_TIED_TO_DESIRE );
}

/* ------------------------------------------------------------ */

static void Profile_Explicit_Restore( uwinp )
    Userwin *uwinp;
{
    if ( Explicit_Window_Get( uwinp, EXPLICIT_REQUIRE_MANUAL_CLOSE ) )
        Tilwin_Set_Window_Option( uwinp->winp, REQUIRE_MANUAL_CLOSE,
            explopts[(int) EXPLICIT_REQUIRE_MANUAL_CLOSE ] );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_FIXED_WIDTH ) )
        Tilwin_Set_Window_Option( uwinp->winp, FIXED_WIDTH,
            explopts[(int) EXPLICIT_FIXED_WIDTH ] );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_FIXED_HEIGHT ) )
        Tilwin_Set_Window_Option( uwinp->winp, FIXED_HEIGHT,
            explopts[(int) EXPLICIT_FIXED_HEIGHT ] );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_FIXED_COMPLETELY ) )
        Tilwin_Set_Window_Option( uwinp->winp, FIXED_COMPLETELY,
            explopts[(int) EXPLICIT_FIXED_COMPLETELY ] );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_LISTENER_TIED_TO_ZOOM ) )
        Userwin_Set_Window_Option( uwinp, LISTENER_TIED_TO_ZOOM,
            explopts[(int) EXPLICIT_LISTENER_TIED_TO_ZOOM ] );
    if ( Explicit_Window_Get( uwinp, EXPLICIT_ZOOM_TIED_TO_DESIRE ) )
        Userwin_Set_Window_Option( uwinp, ZOOM_TIED_TO_DESIRE,
            explopts[(int) EXPLICIT_ZOOM_TIED_TO_DESIRE ] );
}

/* ------------------------------------------------------------ */

static void Profile_Set_Options( classp, namep, uwinp )
    Class *classp;
    Class *namep;
    Userwin *uwinp;
{
    int i;

    Profile_Explicit_Save( uwinp );

    for ( i = 0; i < (int)LENGTH_WINDOW_OPTIONS; i++ )
        Tilwin_Set_Window_Option( uwinp->winp, ((Window_Options)(i)),
            Profile_Get_Class_Option(
                classp, namep, (Window_Options)(i)) );

    for ( i = 0; i < (int)LENGTH_USER_WINDOW_OPTIONS; i++ )
        Userwin_Set_Window_Option( uwinp, ((User_Window_Options)(i)),
            Profile_Get_User_Class_Option(
                classp, namep, (User_Window_Options)(i)) );

    Profile_Explicit_Restore( uwinp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

bool Profile_Supplies_User_Value( uwinp, opt )
    Userwin *uwinp;
    User_Window_Values opt;
{
    Class *classp;
    Class *namep;

    classp = Profile_Classes_Get_Name( uwinp->res_class );
    namep = Profile_Classes_Get_Name( uwinp->identity );
    return Profile_Has_User_Class_Value( classp, namep, opt );
}

/* ------------------------------------------------------------ */

bool Profile_Supplies_User_String( uwinp, opt )
    Userwin *uwinp;
    User_Window_Strings opt;
{
    Class *classp;
    Class *namep;

    classp = Profile_Classes_Get_Name( uwinp->res_class );
    namep = Profile_Classes_Get_Name( uwinp->res_name );
    return Profile_Has_User_Class_String( classp, namep, opt );
}

/* ------------------------------------------------------------ */

bool Profile_Supplies_Pixmap( uwinp )
    Userwin *uwinp;
{
    return Profile_Supplies_User_String( uwinp, ICON_PIXMAP_FILE );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                    PREPARE & LAYOUT                          */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

static void Profile_Preferences( classp, namep, uwinp )
    Class *classp;
    Class *namep;
    Userwin *uwinp;
{
    Profile_Super_Preference( classp );
    Profile_Super_Preference( namep );

    Profile_Set_Options( classp, namep, uwinp );
    Profile_Set_Info( classp, namep, uwinp );
}

/* ------------------------------------------------------------ */

void Profile_Create( uwinp )
    Userwin *uwinp;
{
    Profile_Explicit_Clear( uwinp );

    Profile_Set_Options( CLASS_NULL, CLASS_NULL, uwinp );
    Profile_Set_Info( CLASS_NULL, CLASS_NULL, uwinp );

    Profile_Set_Sizes( CLASS_NULL, CLASS_NULL, uwinp );
    Profile_Create_Sizes( uwinp );

    Userwin_Body_Min_Max( uwinp );
    Userwin_Enforce_Client_Sizes( uwinp );
    Userwin_Check_Sizes( uwinp );
    Userwin_Followup_Sizes( uwinp );
}

/* ------------------------------------------------------------ */

void Profile_Prepare( uwinp )
    Userwin *uwinp;
{
    Class *classp;
    Class *namep;

    classp = Profile_Classes_Get_Name( uwinp->res_class );
    namep = Profile_Classes_Get_Name( uwinp->res_name );

    Profile_Preferences( classp, namep, uwinp );
    Profile_Update_Icon_Sizes( classp, namep, uwinp );

    Userwin_Setup_Sizes( uwinp );

    Profile_Set_Sizes( classp, namep, uwinp );
    Profile_Update_Sizes( classp, namep, uwinp );

    Userwin_Body_Min_Max( uwinp );
    Userwin_Enforce_Client_Sizes( uwinp );
    Userwin_Check_Sizes( uwinp );
    Userwin_Followup_Sizes( uwinp );

    if ( Same_Size( Tilwin_Get_Min( uwinp->winp ),
                    Tilwin_Get_Max( uwinp->winp ) ) )
        uwinp->sized = TRUE;
}

/* ------------------------------------------------------------ */

void Profile_Layout( uwinp )
    Userwin *uwinp;
{
    Layoutp layoutp = LAYOUT_NULL;

    if ( (uwinp->res_class != NULL) || (uwinp->res_name != NULL ) )
        layoutp = Layout_Find( uwinp );
    else
        Profile_Prepare( uwinp );

    if ( layoutp != LAYOUT_NULL )
        uwinp->layout_found = TRUE;

    Userwin_Setup_Sizes( uwinp );
    Layout_Set_Values( layoutp, uwinp );
    Userwin_Enforce_Client_Sizes( uwinp );
    Userwin_Check_Sizes( uwinp );
    Userwin_Followup_Sizes( uwinp );
    Userwin_Bound_Size( uwinp );

    Layout_Set_Options( layoutp, uwinp );
}

/* ------------------------------------------------------------ */

static void Profile_Update_Window( uwinp )
    Userwin *uwinp;
{
    Class *classp;
    Class *namep;

    classp = Profile_Classes_Get_Name( uwinp->res_class );
    namep = Profile_Classes_Get_Name( uwinp->res_name );

    Profile_Preferences( classp, namep, uwinp );
    Profile_Update_Icon_Sizes( classp, namep, uwinp );

    Userwin_Setup_Sizes( uwinp );
    Userwin_Body_Min_Max( uwinp );
    Userwin_Enforce_Client_Sizes( uwinp );
    Userwin_Followup_Sizes( uwinp );
}

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*                  INIT & REINIT                               */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

void Profile_Update( filnams )
    char *filnams;
{
    Tilwinp winp;
    Userwin *uwinp;

    Profile_Menu_Read();
    Profile_Read( filnams );
    Layout_Update( filnams );

    Tilwin_Gen_Open_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get( winp );
        if ( uwinp->winp == winp )
            Profile_Update_Window( uwinp );
    }

    Tilwin_Gen_Closed_Windows();
    while ( (winp = Tilwin_Next_Window()) != WIN_NULL )
    {
        uwinp = Userwin_Get( winp );
        if ( (uwinp->winp == winp) && (uwinp->current_type != rtl) )
            Profile_Update_Window( uwinp );
    }
}

/* ------------------------------------------------------------ */

void Profile_Init( menu, proc )
    TileMenu menu;
    VoidFunc proc;
{
    Profile_Menu_Init( menu, proc );
    Profile_Menu_Read();

    Profile_Read( Layout_Init() );
    Layout_Read();
}

