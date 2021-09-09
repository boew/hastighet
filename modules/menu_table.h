/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2003
 *
 *    File name   : menu_table.h
 *    Description : Menu tables include file
 *
 *    History :
 *    1. Date        : Feb 10, 2005
 *       Author      : Stanimir Bonev
 *       Description : Create  
 *
 *    $Revision: 28 $
 **************************************************************************/

#ifndef  __MENU
#define  __MENU

#include "menu_table.h"

LPC_BOOL MenuInit (LANG_TYPE_DEF Language, MEMU_IND_DEF MainMenuInd);
LPC_BOOL MenuEvent (MENU_EVENT_TYPE_DEF MenuEvent);
void Menu (void);
MENU_EVENT_TYPE_DEF MenuGetInd(void);
MENU_EVENT_TYPE_DEF MenuGetActionChain(MEMU_IND_DEF MainMenuInd);
MENU_EVENT_TYPE_DEF MenuGetVisualChain(LANG_TYPE_DEF Language,MEMU_IND_DEF MainMenuInd);

#endif  /* __MENU */
