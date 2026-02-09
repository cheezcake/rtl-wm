/*
static char sccs_id[] = "@(#)twin.h	5.6  9/1/88";
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


#ifndef TILWIN
#include "twinP.h"
#endif

#include "state.h"

/* ------------------------------------------------------------ */

extern Size desktop_size;
extern TWRectangle desktop_rect;
extern TWPoint desktop_center;

extern Size absolute_mins;
extern int gravity;

/* ------------------------------------------------------------ */

#define  Tilwin_Get_Desktop_Size() \
    ( desktop_size )
#define  Tilwin_Get_Desktop_Rectangle() \
    ( desktop_rect )
#define  Tilwin_Get_Desktop_Center() \
    ( desktop_center )

extern void Tilwin_Set_Desktop_Size();
/* siz */


/* ------------------------------------------------------------ */

extern Tilwinp Tilwin_Create_Window();

extern void Tilwin_Destroy_Window();
/*    Tilwinp winp; */

extern Tilwinp Tilwin_Locate();
/*    TWPoint pt;         */

/* ------------------------------------------------------------ */

extern bool Tilwin_Check_Center_Open();
/*    Tilwinp winp;       */
/*    TWPoint *adr_pt;      */
/*    Size *adr_siz;      */

extern bool Tilwin_Check_Corner_Open();
/*    Tilwinp winp;       */
/*    TWPoint *start_pt;  */
/*    TWPoint *adr_pt;    */
/*    Side side;  */
/*    Size min_size;  */
/*    Size max_size;  */

extern bool Tilwin_Check_Resize();
/*    Tilwinp winp;       */
/*    TWPoint *adr_pt;    */
/*    Side side;       */
/*    Size min_size;  */
/*    Size max_size;  */

/* ------------------------------------------------------------ */

extern bool Tilwin_Open();
/*    Tilwinp winp;       */
/*    TWPoint center;       */
/*    Size siz;           */

extern void Tilwin_Close();
/*    Tilwinp winp;       */

extern void Tilwin_Auto_Close();
/*    Tilwinp winp;       */

/* ------------------------------------------------------------ */

extern bool Tilwin_Set();
/*    Tilwinp winp;       */
/*    TWPoint center; 	*/    
/*    Size siz;   	*/    

extern bool Tilwin_Set_Size();
/*    Tilwinp winp;       */
/*    Size siz;         */

/* ------------------------------------------------------------ */

extern bool Tilwin_Is_Satisfied();
/*    Tilwinp winp;       */

/* ------------------------------------------------------------ */

extern bool Tilwin_Resize();
/*    Tilwinp winp;       */
/*    TWPoint pt;    */
/*    Side side;    */

extern bool Tilwin_Enlarge_Nearest();
/*    Tilwinp winp;       */
/*    TWPoint pt; 	*/    
/*    Size siz;   	*/    

extern bool Tilwin_Enlarge_Farthest();
/*    Tilwinp winp;       */
/*    TWPoint pt; 	*/    
/*    Size siz;   	*/    

/* ------------------------------------------------------------ */

extern void Tilwin_Enlarge_Nearest_In_Area();
/*    Tilwinp winp;       */
/*    TWRectangle rect;   */
/*    TWPoint pt; 	*/    
/*    Size siz;   	*/    

extern void Tilwin_Enlarge_Farthest_In_Area();
/*    Tilwinp winp;       */
/*    TWRectangle rect;   */
/*    TWPoint pt; 	*/    
/*    Size siz;   	*/    

/* ------------------------------------------------------------ */

extern bool Tilwin_Open_Nearest_In_Area();
/*    Tilwinp winp;       */
/*    TWRectangle rect;   */
/*    TWPoint pt; 	*/    
/*    Size siz;   	*/    

extern bool Tilwin_Open_Farthest_In_Area();
/*    Tilwinp winp;       */
/*    TWRectangle rect;   */
/*    TWPoint pt; 	*/    
/*    Size siz;   	*/    

extern bool Tilwin_Open_Best_In_Area();
/*    Tilwinp winp;       */
/*    TWRectangle rect;   */
/*    Size siz;   	*/    

/* ------------------------------------------------------------ */

extern void Tilwin_Prorate();

/* ------------------------------------------------------------ */

extern void Tilwin_Gen_Open_Windows();

extern void Tilwin_Gen_Closed_Windows();

extern void Tilwin_Gen_Just_Opened_Windows();

extern void Tilwin_Gen_Just_Modified_Windows();

extern void Tilwin_Gen_Just_Closed_Windows();

extern Tilwinp Tilwin_Next_Window();

extern void Tilwin_Modify_Covered_Windows();

extern bool Tilwin_Is_Covered();

/* ------------------------------------------------------------ */

extern void Tilwin_Undo();
extern void Tilwin_Abort_Transaction();

#define Tilwin_Start_Transaction() \
    State_Start_Transaction()

#define Tilwin_Commit_Transaction() \
    State_Commit_Transaction()

#define Tilwin_Continue_Transaction() \
    State_Continue_Transaction()

#define Tilwin_Transaction_Depth() \
    State_Transaction_Depth()

/* ------------------------------------------------------------ */

#define Tilwin_Get_Timestamp() \
    State_Get_Timestamp()

#define Tilwin_Set_Window_Timestamp(winp,stamp) \
    State_Set_Window_Timestamp(winp,stamp)

#define Tilwin_Note_Use(winp) \
    State_Note_Use(winp)

#define Tilwin_Act_Modified(winp) \
    State_Act_Modified(winp)

/* ------------------------------------------------------------ */

#define Tilwin_Was_Just_Modified(winp) \
    State_Was_Just_Modified(winp)

#define Tilwin_Was_Just_Changed(winp) \
    State_Was_Just_Changed(winp)

/* ------------------------------------------------------------ */

#define Tilwin_Get_Absolute_Minimums() \
    ( absolute_mins )
#define Tilwin_Set_Absolute_Minimums(siz) \
    absolute_mins = (siz)

#define Tilwin_Get_Gravity() \
    ( gravity )
#define Tilwin_Set_Gravity(grav) \
    ( gravity = (grav) )

extern bool Tilwin_Slide_Nearest();
extern bool Tilwin_Slide_Farthest();
extern bool Tilwin_Slide_Nearest_In_Area();
extern bool Tilwin_Slide_Farthest_In_Area();

extern void Tilwin_Slide_Horizly_Farthest();
extern void Tilwin_Slide_Vertly_Farthest();
extern void Tilwin_Slide_Horizly_Nearest();
extern void Tilwin_Slide_Vertly_Nearest();

extern Tilwinp Tilwin_Thread_Nearest();
extern Tilwinp Tilwin_Thread_Farthest();
extern Tilwinp Tilwin_Reverse_Thread();

extern Tilwinp Tilwin_Thread_Nearest_Position();

extern Tilwinp Tilwin_Thread_Vertly_Nearest();
extern Tilwinp Tilwin_Thread_Horizly_Nearest();
extern Tilwinp Tilwin_Thread_Vertly_Farthest();
extern Tilwinp Tilwin_Thread_Horizly_Farthest();

/* ------------------------------------------------------------ */

extern TWPoint Tilwin_Center_Of_Gravity();
extern TWPoint Tilwin_Position_Ctr_Of_Gravity();

extern Size Tilwin_Good_Size();
extern Size Tilwin_Checked_Size();
extern Size Tilwin_Checked_Previous_Size();
extern Size Tilwin_Checked_Min_Size();
extern Size Tilwin_Checked_Desired_Size();
extern Size Tilwin_Checked_Good_Desired_Size();
extern Size Tilwin_Checked_Max_Size();
extern Size Tilwin_Checked_Good_Max_Size();

/* ------------------------------------------------------------ */

extern Tilwinp Tilwin_Get_Latest_Height();
extern Tilwinp Tilwin_Get_Latest_Width();

