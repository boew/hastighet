/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2003
 *
 *    File name   : user_func.c
 *    Description : User functions module
 *
 *    History :
 *    1. Date        : Feb 12, 2005
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 28 $
**************************************************************************/
#include "user_func.h"

#define SCREEN_SAVER_INC  TRUE    /* Index increment */
#define SCREEN_SAVER_DEC  FALSE   /* Index decrement */

#define MAX_ADC_FREQ      4500000 /* Max ADC frequence */

LPC_INT8U ButtCount1,ButtCount2,ButtFlags;

LPC_BOOL LightState;

LPC_INT8U Index;
LPC_BOOL Direction;

const char IllumAlwaysOff[] = " Off";
const char IllumAuto[] = " Auto";
const char IllumAlwaysOn[] = " On";

const char * const IlluminationModeStr[] =
{
  IllumAlwaysOff,
  IllumAuto,
  IllumAlwaysOn,
};

const LPC_INT8U ScreenSaverTO [] =
{
  2*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  0.15*TICK_PER_SECOND,
  2*TICK_PER_SECOND,
};

const MEMU_STING_DEF ScreenSaver0 [] = "  IAR Embedded  \2 Workbench-ARM  \2";
const MEMU_STING_DEF ScreenSaver1 [] = "   IAR Eedded   \2  Worknch-ARM   \2";
const MEMU_STING_DEF ScreenSaver2 [] = "    IAR dded    \2   Worch-ARM    \2";
const MEMU_STING_DEF ScreenSaver3 [] = "     IARded     \2    Woh-ARM     \2";
const MEMU_STING_DEF ScreenSaver4 [] = "      IAed      \2     W-ARM      \2";
const MEMU_STING_DEF ScreenSaver5 [] = "       Id       \2      WRM       \2";
const MEMU_STING_DEF ScreenSaver6 [] = "                \2       M        \2";
const MEMU_STING_DEF ScreenSaver7 [] = "                \2                \2";
const MEMU_STING_DEF ScreenSaver8 [] = "       PM       \2                \2";
const MEMU_STING_DEF ScreenSaver9 [] = "      PARM      \2                \2";
const MEMU_STING_DEF ScreenSaver10[] = "     Ph ARM     \2                \2";
const MEMU_STING_DEF ScreenSaver11[] = "    Phii ARM    \2                \2";
const MEMU_STING_DEF ScreenSaver12[] = "   Phiemi ARM   \2       L        \2";
const MEMU_STING_DEF ScreenSaver13[] = "  Philiemi ARM  \2      L38       \2";
const MEMU_STING_DEF ScreenSaver14[] = " Philipsemi ARM \2     LP138      \2";
const MEMU_STING_DEF ScreenSaver15[] = "Philips Semi ARM\2    LPC2138     \2";

const MEMU_STING_DEF * const ScreenSaverTable [] =
{
  ScreenSaver0,ScreenSaver1,ScreenSaver2,ScreenSaver3,
  ScreenSaver4,ScreenSaver5,ScreenSaver6,ScreenSaver7,
  ScreenSaver8,ScreenSaver9,ScreenSaver10,ScreenSaver11,
  ScreenSaver12,ScreenSaver13,ScreenSaver14,ScreenSaver15,
};

/*************************************************************************
 * Function Name: ScreenSaverInit
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Initialize menu screensaver
 *
 *************************************************************************/
void ScreenSaverInit (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
  Index = 0;
  Direction = SCREEN_SAVER_INC;
  ScreenSaver(pVarArg,MenuIndex,MenuTO);
}

/*************************************************************************
 * Function Name: ScreenSaver
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Initialize menu screensaver
 *
 *************************************************************************/
void ScreenSaver (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
  Index &= 0xF;
  *MenuTO = ScreenSaverTO[Index];
  strcpy(pVarArg,ScreenSaverTable[Index]);
  if (Direction == SCREEN_SAVER_INC)
  {
    ++Index;
  }
  else
  {
    --Index;
  }
  if (Index == 15)
  {
    Direction = SCREEN_SAVER_DEC;
  }
  else if (Index == 0)
  {
    Direction = SCREEN_SAVER_INC;
  }
}


/*************************************************************************
 * Function Name: SysTimeUpdate
 * Parameters: none
 * Return: none
 * Description: Set flag sys_time_update
 *
 *************************************************************************/
void SysTimeUpdate (void)
{
  SysTimeUpdateFlag = 1;
}

/*************************************************************************
 * Function Name: Alarm
 * Parameters: none
 * Return: none
 * Description: Set flag alarm
 *
 *************************************************************************/
void Alarm (void)
{
  SysAlarmFlag = 1;
}

/*************************************************************************
 * Function Name: FindOffSet
 * Parameters: const char* Str,
 *             LPC_INT8U  Size
 * Return: LPC_INT8U
 * Description: Return needed offset to show string in the middle of the LCD
 *
 *************************************************************************/
LPC_INT8U FindOffSet(const char* Str,LPC_INT8U  Size)
{
  if(strlen(Str) < Size-1)
  {
    Size -= strlen(Str);
    return (Size>>1);
  }
  return 0;
}
/*************************************************************************
 * Function Name: FindOffSet
 * Parameters: const char* Str,
 *             LPC_INT8U  Size
 * Return: LPC_INT8U
 * Description: Return needed offset to show string in the middle of the LCD
 *
 *************************************************************************/
void ReplaceStr(char* DestStr,const char* SourStr,LPC_INT8U  Offset,LPC_INT8U  Size)
{
  if((SourStr == NULL) || (DestStr == NULL)
    || (Size == 0))
  {
    return;
  }
  DestStr += Offset;
  while(*SourStr)
  {
    *DestStr = *SourStr;
    ++SourStr;++DestStr;
    if(--Size == 0)
    {
      break;
    }
  }
}
/*************************************************************************
 * Function Name: GetTimeAndData
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Set flag alarm
 *
 *************************************************************************/
void GetTimeAndData (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex,MEMU_TIME_OUT_DEF * MenuTO)
{
char Temp[20];
LPC_Rtc_Time_t CurrTime;
LPC_Rtc_Date_t CurrData;
  RTC_GetTime(&CurrTime);
  FormatTime(TimeFormat,&CurrTime,Temp);
  ReplaceStr(pVarArg,Temp,FindOffSet(Temp,16),16);
  *(pVarArg+16) = 0;
  RTC_GetDate(&CurrData);
  FormatDate(DataFormat,&CurrData,Temp);
  ReplaceStr(pVarArg+17,Temp,FindOffSet(Temp,16),16);
  *(pVarArg+33) = 0;
  HD44780_CursorPosSet(HD44780_CURSOR_OFF, HD44780_CURSOR_BLINK,1, 1);
}

void FormatSpeed(int v_fixpoint, char *s)
{
  sprintf(s, "%3d km/h", v_fixpoint/100);
}
void FormatDist(int dkm, int tkm, char *s)
{
  sprintf(s, "%03d %03d [km] ", dkm, tkm);
}
void renamed_GetTimeAndSpeed (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex,MEMU_TIME_OUT_DEF * MenuTO)
{
char Temp[20];
LPC_Rtc_Time_t CurrTime;
//LPC_Rtc_Date_t CurrData;
  RTC_GetTime(&CurrTime);
  FormatTime(TimeFormat,&CurrTime,Temp);
  ReplaceStr(pVarArg,Temp,FindOffSet(Temp,16),16);
  *(pVarArg+16) = 0;
  FormatSpeed(getScaledV(),Temp);
  ReplaceStr(pVarArg+17,Temp,FindOffSet(Temp,16),16);
  *(pVarArg+33) = 0;
  HD44780_CursorPosSet(HD44780_CURSOR_OFF, HD44780_CURSOR_BLINK,1, 1);
}

void GetDistAndSpeed (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex,MEMU_TIME_OUT_DEF * MenuTO)
{
  char Temp[20];
  int dist;
  int trip;
  dist = getScaledDistance();
  trip = getScaledTrip();
  FormatDist(dist, trip, Temp);
  ReplaceStr(pVarArg,Temp,FindOffSet(Temp,16),16);
  *(pVarArg+16) = 0;
  FormatSpeed(getScaledV(),Temp);
  ReplaceStr(pVarArg+17,Temp,FindOffSet(Temp,16),16);
  *(pVarArg+33) = 0;
  HD44780_CursorPosSet(HD44780_CURSOR_OFF, HD44780_CURSOR_BLINK,1, 1);
}


/*************************************************************************
 * Function Name: ButtonsInit
 * Parameters: none
 * Return: none
 * Description: Init buttons
 *
 *************************************************************************/
void ButtonsInit (void)
{
  /* Init buttons Inputs */
  IO0DIR_bit.P0_15 = IO0DIR_bit.P0_16 = 0;
  /* Init buttons' variables */
  ButtFlags = ButtCount1 = ButtCount2 = 0;
}

/*************************************************************************
 * Function Name: Buttons
 * Parameters: none
 * Return: none
 * Description: Imlement buttons
 *
 *************************************************************************/
void Buttons (void)
{
  if (!IO0PIN_bit.P0_15)
  {
    if(ButtCount1 > BUTT_DEB)
    {
      if((ButtFlags & BUTT_FLAG_1) == 0)
      {
        ButtFlags |= BUTT_FLAG_1+BUTT_EVENT_1;
      }
    }
    else
    {
      ++ButtCount1;
    }
  }
  else
  {
    if(ButtCount1 == 0)
    {
      if(ButtFlags & BUTT_FLAG_1)
      {
        ButtFlags &= ~BUTT_FLAG_1;
      }
    }
    else
    {
      --ButtCount1;
    }
  }
  if (!IO0PIN_bit.P0_16)
  {
    if(ButtCount2 > BUTT_DEB)
    {
      if((ButtFlags & BUTT_FLAG_2) == 0)
      {
        ButtFlags |= BUTT_FLAG_2+BUTT_EVENT_2;
      }
    }
    else
    {
      ++ButtCount2;
    }
  }
  else
  {
    if(ButtCount2 == 0)
    {
      if(ButtFlags & BUTT_FLAG_2)
      {
        ButtFlags &= ~BUTT_FLAG_2;
      }
    }
    else
    {
      --ButtCount2;
    }
  }
}

/*************************************************************************
 * Function Name: GetButtonsEvent
 * Parameters: none
 * Return: LPC_INT8U
 * Description: Return buttons event and clear event flags
 *
 *************************************************************************/
LPC_INT8U GetButtonsEvent (void)
{
LPC_INT8U Events = ButtFlags & (BUTT_EVENT_1|BUTT_EVENT_2);
  ButtFlags &= ~(BUTT_EVENT_1|BUTT_EVENT_2);
  return Events;
}

/*************************************************************************
 * Function Name: SetSysTickFlag
 * Parameters: void
 * Return: void
 *
 * Description: clear arg
 *		
 *************************************************************************/
void SetSysTickFlag (void* arg)
{
int* pFlag = arg;
  *pFlag = 1;
  Buttons();
}

/*************************************************************************
 * Function Name: LightInit
 * Parameters: none
 * Return: none
 * Description: Init light control
 *
 *************************************************************************/
void LightInit(void)
{
  /* Connect DAC output to pin P0_25 */
  PINSEL1_bit.P0_25 = 2;
  /* DAC Init */
  DACR_bit.BIAS = 0x1;
  /* Light Off */
  DACR_bit.VALUE = LIGHT_OFF_VALUE;
  /* Init Current state of light */
  LightState = LIGHT_OFF;

}

/*************************************************************************
 * Function Name: LightCntr
 * Parameters: LPC_BOOL Slow,
               LPC_BOOL On
 * Return: none
 * Description: Light control
 *
 *************************************************************************/
void LightCntr (LPC_BOOL Slow,LPC_BOOL On)
{
  if(LightState != On)
  {
    if(Slow == LIGHT_SLOW)
    {
      if(On == LIGHT_ON)
      {
        if(DACR_bit.VALUE < LIGHT_ON_VALUE-0xF)
        {
          DACR_bit.VALUE += 0xF;
        }
        else
        {
          LightState = On;
        }
      }
      else
      {
        if(DACR_bit.VALUE > 0xF)
        {
          DACR_bit.VALUE -= 0xF;
        }
        else
        {
          LightState = On;
        }
      }
    }
    else
    {
      LightState = On;
      DACR_bit.VALUE = (On == LIGHT_ON)? LIGHT_ON_VALUE: LIGHT_OFF_VALUE;
    }
  }
}

/*************************************************************************
 * Function Name: ADC_Init
 * Parameters: none
 * Return: none
 * Description: ADC Init
 *
 *************************************************************************/
void ADC_Init (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
  /* ADC Channel0 is connected to pin P0_27 */
  PINSEL1_bit.P0_27 = 1;
  /* ADC Settings */
  AD0CR_bit.SEL = 1;
  AD0CR_bit.CLKDIV = SYS_GetFpclk()/MAX_ADC_FREQ;
  AD0CR_bit.BURST = 0;
  AD0CR_bit.PDN = 1;
  AD0CR_bit.START = 0;
  ADC_Measure(pVarArg,MenuIndex,MenuTO);
}
/*************************************************************************
 * Function Name: ADC_Measure
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Trim voltage measure
 *
 *************************************************************************/
void ADC_Measure (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
LPC_INT32U AdcResult;
LPC_INT8U Count;
int i;
  /* ADC Conversion start */
  AD0CR_bit.START = 1;

  /* Delay needed when executing from flash, unknown why */
  for (i = 0; i < 32; i++)
    __no_operation();

  /* Wait result */
  do
  {
    AdcResult = AD0DR;
  }while((AdcResult&0x80000000) == 0);
  AdcResult = (AdcResult >> 12) & 0xF;
  for (Count = 0;Count < 16; ++Count)
  {
    if(AdcResult)
    {
      *pVarArg = '*';
      --AdcResult;
    }
    else
    {
      *pVarArg = ' ';
    }
    ++pVarArg;
  }
  *pVarArg = 2;
  *++pVarArg = 0;
}

/*************************************************************************
 * Function Name: IlluminationShow
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Illumination show
 *
 *************************************************************************/
void IlluminationShow (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
const char * SourceData = IlluminationModeStr[LightMode];
  for (int i =0; i < 10;++i)
  {
    if(*SourceData)
    {
      *pVarArg = *SourceData;
      ++SourceData;
    }
    else
    {
      *pVarArg = ' ';
    }
    ++pVarArg;
  }
  *pVarArg=2;
  *++pVarArg=0;
}
/*************************************************************************
 * Function Name: IlluminationModeCursorOn
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Illumination cursor on
 *
 *************************************************************************/
void IlluminationModeCursorOn (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
  HD44780_CursorPosSet(HD44780_CURSOR_OFF, HD44780_CURSOR_BLINK,8, 2);
}

/*************************************************************************
 * Function Name: IlluminationNextMode
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Illumination next
 *
 *************************************************************************/
void IlluminationNextMode (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
  if(++LightMode > 2)
  {
    LightMode = 0;
  }
  IlluminationShow(pVarArg,MenuIndex,MenuTO);
}

/*************************************************************************
 * Function Name: CursorOff
 * Parameters: MEMU_STING_DEF * pVarArg,
 *             MEMU_IND_DEF * MenuIndex,
 *             MEMU_TIME_OUT_DEF * MenuTO
 * Return: none
 * Description: Cursor off
 *
 *************************************************************************/
void CursorOff (MEMU_STING_DEF * pVarArg,MEMU_IND_DEF * MenuIndex, MEMU_TIME_OUT_DEF * MenuTO)
{
  HD44780_CursorPosSet(HD44780_CURSOR_OFF, HD44780_CURSOR_NORM,1, 1);
}

//BoE
char boe_UART_Msg[40]=""; // LCD 2 x16 chars + crlf + null
unsigned int BoE_TC_tmp;
unsigned int BoE_TCP_tmp;
/*
	TIMER_GetTimerCapture(TIMER1, CPCH2, &BoE_TCP_tmp);
	sprintf(boe_UART_Msg,"\r\nTimes:\r\n");
	UART_PutString(UART1,(char*)boe_UART_Msg);
	for(BoE_TCP_tmp = 0; BoE_TCP_tmp < TimesN; BoE_TCP_tmp++)
	  {
	    sprintf(boe_UART_Msg,"\r\n\t%d:\t%d",BoE_TCP_tmp, times[BoE_TCP_tmp]);
	    UART_PutString(UART1,(char*)boe_UART_Msg);
	  }

sprintf(boe_UART_Msg,"\r\nnTimes, Speed:\t%d, %d\r\n",nTimes, getScaledV());
UART_PutString(UART1,(char*)boe_UART_Msg);
*/


#define TIME_BUF_SIZE (1 << 4) /*  must be power of two - circular buffer */
#define TIME_BUF_MASK (TIME_BUF_SIZE - 1) /* mask for index to circular buffer */
volatile unsigned int times[ TIME_BUF_SIZE ];
volatile unsigned long long nTimes = 0; 
unsigned long long CaptureCount = 0;
unsigned long long TripOffset = 0;
/* 0.6 m per revolution
   divided by 2 (triggering twice per revolution):   
   600/2 mm = 300 mm 
*/

unsigned int distancePerPulse_mm = 600; // mm 
unsigned int captureCountDiff_to_10mh = 14740 / 14 * 600 * 360; // units of (10m) / h = (0.01 km)/h
/* 14.74 MHz timer clock, divide by 14 prescaling, 600 mm / sensor pulse, (3.6 km/h per m/s) * 100 */
 
// BoE TBD: Make this __monitor ?
void DoTimes(void* arg)
{
  unsigned int tmp1;
  int tmp2;  
  TIMER_GetTimerCapture(TIMER1, CPCH2, &tmp1);
  times[nTimes & TIME_BUF_MASK] = tmp1;
  tmp2 = (nTimes + 1);
  nTimes = tmp2;
  (*((unsigned long long *) arg))++;
}

int getScaledV()
{
  unsigned int periodCount = 0;
  int currentIndex = -3; /* Never "== nTimes-1" */
  int indexPreviousPeriod = 0; 

  while (((nTimes-1) & TIME_BUF_MASK) != currentIndex ) 
    {
      currentIndex = (nTimes - 1) & TIME_BUF_MASK;
      if (0 > currentIndex) { currentIndex += TIME_BUF_SIZE; }
      
      indexPreviousPeriod = ( currentIndex - 2 ) & TIME_BUF_MASK;
      if (0 > indexPreviousPeriod) { indexPreviousPeriod += TIME_BUF_SIZE ;}      

      periodCount  = times[currentIndex];
      periodCount -= times[indexPreviousPeriod];      
    }
  if (0 == periodCount) {
    return 0;
  }
  return (captureCountDiff_to_10mh / periodCount);
}

int getScaledDistance()
{
  return (nTimes * distancePerPulse_mm / 1000000);
}

int getScaledTrip()
{
  return ((nTimes - TripOffset) * distancePerPulse_mm / 1000000) ;
}


