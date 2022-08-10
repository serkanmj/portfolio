/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2013  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.22 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  NXP Semiconductors USA, Inc.  whose
registered  office  is  situated  at 411 E. Plumeria Drive, San  Jose,
CA 95134, USA  solely for  the  purposes  of  creating  libraries  for
NXPs M0, M3/M4 and  ARM7/9 processor-based  devices,  sublicensed  and
distributed under the terms and conditions of the NXP End User License
Agreement.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : MULTIPAGE.h
Purpose     : MULTIPAGE include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef MULTIPAGE_H
#define MULTIPAGE_H

#include "WM.h"
#include "DIALOG.h"   // Required for Create indirect data structure

#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {        // Make sure we have C-declarations in C++ programs
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Create / Status flags
*/
#define MULTIPAGE_ALIGN_LEFT           (0 << 0)
#define MULTIPAGE_ALIGN_RIGHT          (1 << 0)
#define MULTIPAGE_ALIGN_TOP            (0 << 2)
#define MULTIPAGE_ALIGN_BOTTOM         (1 << 2)

#define MULTIPAGE_CF_ROTATE_CW          WIDGET_CF_VERTICAL

#define MULTIPAGE_CI_DISABLED           0
#define MULTIPAGE_CI_ENABLED            1

#define MULTIPAGE_SKIN_FRAME_LEFT      (1 << 0)
#define MULTIPAGE_SKIN_FRAME_RIGHT     (1 << 1)
#define MULTIPAGE_SKIN_FRAME_TOP       (1 << 2)
#define MULTIPAGE_SKIN_FRAME_BOTTOM    (1 << 3)
#define MULTIPAGE_SKIN_FRAME_ALL       (MULTIPAGE_SKIN_FRAME_LEFT | MULTIPAGE_SKIN_FRAME_RIGHT | MULTIPAGE_SKIN_FRAME_TOP | MULTIPAGE_SKIN_FRAME_BOTTOM)

#define MULTIPAGE_SKINFLEX_PI_ENABLED   0
#define MULTIPAGE_SKINFLEX_PI_SELECTED  1
#define MULTIPAGE_SKINFLEX_PI_DISABLED  2

/*********************************************************************
*
*       Public Types
*
**********************************************************************
*/
typedef WM_HMEM MULTIPAGE_Handle;

typedef struct {
  GUI_COLOR BkColor;
  GUI_COLOR aBkUpper[2];
  GUI_COLOR aBkLower[2];
  GUI_COLOR FrameColor;
  GUI_COLOR TextColor;
} MULTIPAGE_SKINFLEX_PROPS;

typedef struct {
  U16 StartOff;                 // Offset to use when drawing the unselected item 0.
  U8  SelSideBorderInc;         // Number of pixels to add on both sides when drawing the selected item.
  U8  UnselTopBorderDec;        // Number of pixels to decrease the height of unselected items.
} MULTIPAGE_SKIN_PROPS;

typedef struct {
  GUI_ROTATION * pRotation;
  unsigned       Align;
  int            Sel;
  U16            State;
  U8             FrameFlags;    // Flags to let the drawing function know which parts of the frame to display.
  U8             PageStatus;
} MULTIPAGE_SKIN_INFO;

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/
MULTIPAGE_Handle MULTIPAGE_Create        (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int Id, int Flags, int SpecialFlags);
MULTIPAGE_Handle MULTIPAGE_CreateEx      (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id);
MULTIPAGE_Handle MULTIPAGE_CreateUser    (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, int NumExtraBytes);
MULTIPAGE_Handle MULTIPAGE_CreateIndirect(const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void MULTIPAGE_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/
void             MULTIPAGE_AddPage       (MULTIPAGE_Handle hObj, WM_HWIN hWin ,const char * pText);
void             MULTIPAGE_AddEmptyPage  (MULTIPAGE_Handle hObj, WM_HWIN hWin ,const char * pText);
WM_HWIN          MULTIPAGE_AttachWindow  (MULTIPAGE_Handle hObj, unsigned Index, WM_HWIN hWin);
void             MULTIPAGE_DeletePage    (MULTIPAGE_Handle hObj, unsigned Index, int Delete);
void             MULTIPAGE_DisablePage   (MULTIPAGE_Handle hObj, unsigned Index);
void             MULTIPAGE_EnablePage    (MULTIPAGE_Handle hObj, unsigned Index);
const GUI_FONT * MULTIPAGE_GetFont       (MULTIPAGE_Handle hObj);
int              MULTIPAGE_GetSelection  (MULTIPAGE_Handle hObj);
int              MULTIPAGE_GetPageText   (MULTIPAGE_Handle hObj, unsigned Index, char * pBuffer, int MaxLen);
int              MULTIPAGE_GetUserData   (MULTIPAGE_Handle hObj, void * pDest, int NumBytes);
WM_HWIN          MULTIPAGE_GetWindow     (MULTIPAGE_Handle hObj, unsigned Index);
int              MULTIPAGE_IsPageEnabled (MULTIPAGE_Handle hObj, unsigned Index);
void             MULTIPAGE_SelectPage    (MULTIPAGE_Handle hObj, unsigned Index);
void             MULTIPAGE_SetAlign      (MULTIPAGE_Handle hObj, unsigned Align);
void             MULTIPAGE_SetBkColor    (MULTIPAGE_Handle hObj, GUI_COLOR Color, unsigned Index);
void             MULTIPAGE_SetFont       (MULTIPAGE_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont);
void             MULTIPAGE_SetRotation   (MULTIPAGE_Handle hObj, unsigned Rotation);
void             MULTIPAGE_SetText       (MULTIPAGE_Handle hObj, const char * pText, unsigned Index);
void             MULTIPAGE_SetTextColor  (MULTIPAGE_Handle hObj, GUI_COLOR Color, unsigned Index);
int              MULTIPAGE_SetUserData   (MULTIPAGE_Handle hObj, const void * pSrc, int NumBytes);

/*********************************************************************
*
*       Get/Set defaults
*
**********************************************************************
*/
unsigned                     MULTIPAGE_GetDefaultAlign    (void);
GUI_COLOR                    MULTIPAGE_GetDefaultBkColor  (unsigned Index);
const GUI_FONT GUI_UNI_PTR * MULTIPAGE_GetDefaultFont     (void);
GUI_COLOR                    MULTIPAGE_GetDefaultTextColor(unsigned Index);

void                         MULTIPAGE_SetDefaultAlign    (unsigned Align);
void                         MULTIPAGE_SetDefaultBkColor  (GUI_COLOR Color, unsigned Index);
void                         MULTIPAGE_SetDefaultFont     (const GUI_FONT GUI_UNI_PTR * pFont);
void                         MULTIPAGE_SetDefaultTextColor(GUI_COLOR Color, unsigned Index);

void                         MULTIPAGE_SetEffectColor     (unsigned Index, GUI_COLOR Color);
GUI_COLOR                    MULTIPAGE_GetEffectColor     (unsigned Index);
int                          MULTIPAGE_GetNumEffectColors (void);

/*********************************************************************
*
*       Member functions: Skinning
*
**********************************************************************
*/
int                     MULTIPAGE_DrawSkinFlex         (const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void                    MULTIPAGE_GetSkinFlexProps     (MULTIPAGE_SKINFLEX_PROPS * pProps, int Index);
WIDGET_DRAW_ITEM_FUNC * MULTIPAGE_SetDefaultSkin       (WIDGET_DRAW_ITEM_FUNC * pfDrawSkin);
void                    MULTIPAGE_SetDefaultSkinClassic(void);
void                    MULTIPAGE_SetSkinClassic       (MULTIPAGE_Handle hObj);
void                    MULTIPAGE_SetSkin              (MULTIPAGE_Handle hObj, WIDGET_DRAW_ITEM_FUNC * pfDrawSkin);
void                    MULTIPAGE_SetSkinFlexProps     (const MULTIPAGE_SKINFLEX_PROPS * pProps, int Index);

#define MULTIPAGE_SKIN_FLEX MULTIPAGE_DrawSkinFlex

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // MULTIPAGE_H

/*************************** End of file ****************************/