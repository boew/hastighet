/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2005
 *
 *    File name   : menu.h
 *    Description : Menu include file
 *
 *    History :
 *    1. Date        : Feb 10, 2005
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 28 $
 **************************************************************************/
#include "includes.h"

#ifndef  __MENU_H
#define  __MENU_H

#define END_OF_STR      '\0'
#define VARIABLE_DATA   1
#define END_OF_VAR_DATA 2

typedef char MEMU_STING_DEF ;

/* Menu XY coordinate type def */
typedef LPC_INT8U MENU_COORDINATE_XY_DEF;
typedef void (*MENU_USER_FUNC_DEF)(MEMU_STING_DEF * pVarArg, MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO);

typedef struct
{
  MENU_EVENT_TYPE_DEF EventType;
  MEMU_IND_DEF        MenuIndex;
  MEMU_TIME_OUT_DEF   MenuTO;
  MEMU_STING_DEF  *   pVarArg;
  MENU_USER_FUNC_DEF  UserFunc;
  MENU_USER_FUNC_DEF  UserFunc1;
} MENU_ACTION_SHAIN_DEF;

typedef struct
{
  const MEMU_STING_DEF * MenuText;
  MEMU_XY_DEF X;
  MEMU_XY_DEF Y;
} MENU_VISUAL_DEF;

typedef enum
{
  MENU_OK = 0,              /* command pass */
  MENU_LANG_ERROR,          /* not valid language */
  MENU_IND_ERROR,           /* not valid menu index */
  MENU_EVET_STACK_OVERFLOW, /* Event stack overflow */
  MENU_SHOW_OUT_OF_VISUAL,  /* String out of visual space */
  MENU_SHOW_ERROR,          /* Error into LCD driver module */
  MENU_TO_ERROR,            /* Menu tome out is to long */
}MENU_ERROR_CODE_DEF;

MENU_ERROR_CODE_DEF MenuInit (MENU_LANG_TYPE_DEF Language,
MEMU_IND_DEF MainMenuInd, MEMU_STING_DEF *pVarData, MEMU_TIME_OUT_DEF MenuTO);

MENU_ERROR_CODE_DEF MenuSetEvent (MENU_EVENT_TYPE_DEF MenuEvent);
MENU_ERROR_CODE_DEF Menu (void);
MENU_EVENT_TYPE_DEF MenuGetInd(void);
MENU_ACTION_SHAIN_DEF * MenuGetActionChain(MEMU_IND_DEF MenuInd);
MENU_VISUAL_DEF * MenuGetVisualChain(MENU_LANG_TYPE_DEF Language,MEMU_IND_DEF MenuInd);

#endif  /* __MENU_H */
