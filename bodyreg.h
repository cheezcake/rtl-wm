/*
static char sccs_id[] = "@(#)bodyreg.h	5.3  9/1/88";
*/

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


#ifndef BODYREGION
#include "bodyreg.h"
#endif

#ifndef BASETYPE
#include "basetype.h"
#endif 

#ifndef TILEMENU
#include "tilemenu.h"
#endif

#ifndef TILECURSOR
#include "tilecrsr.h"
#endif

extern BodyRegion Bodyreg_Locate();
  /*  Userwin *uwinp */
  /*  TWPoint pt */
    
extern TileCursor Bodyreg_Get_Cursor();
  /*  Userwin *uwinp */
  /*  Bodyregion region */

extern void Bodyreg_Set_Cursor();
/*    Userwin	*uw;
      int	font_index, c;
 */

extern TileMenu Bodyreg_Get_Menu();
  /*  Userwin *uwinp */
  /*  Bodyregion region */

extern void	Bodyreg_Name_Region();
/*
    Userwin        *uwinp;
    int             regionid;
    char           *name;
*/

extern void	Bodyreg_Create_If_Not_Pres();
/*
    Userwin        *uwinp;
    int             regionid;
*/

extern void	Bodyreg_Def_Rect_For_Region();
/*
    Userwin        *uwinp;
    int             regionid;
    int             left, top, width, height;
*/

extern void	Bodyreg_Destroy_Regions();
/*
    Userwin        *uwinp;
*/

extern void	Bodyreg_Link_Region();
/*
    Userwin        *uwinp;
    int             regionid1, regionid2;
*/

extern void	Bodyreg_Menu_Item();
/*
    Userwin        *uwinp;
    char           *string;
*/
