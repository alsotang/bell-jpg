#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "init.h"
#include "alarm.h"
#include "mywatchdog.h"
#include "boa.h"
#include "param.h"
#include "debug.h"
#include "ipcparam.h"

static int bDoorOpening = FALSE;
static int bDoor2Opening = FALSE;

static int bOpenTimes = 0;
static int bOpen2Times = 0;


void StartOpenLock()
{
	bDoorOpening = TRUE;
	bOpenTimes = 0;
	SetBellLock(TRUE);
	Textout("Open Lock ---------- Start ");
#ifdef  RUIYITONG
	ControlIO(BELL_OPENDOOR_2, 1);
#endif

	/* add begin by yiqing, 2017-02-15*/
	setPlayAudioFlag(1);//播放开锁音频内，咪头不采集声音，以免产生哒哒哒的声音

	#ifndef UK_CUSTOMERS_NEW_KERNEL
	StartAudioPlay(WF_OPENLOCK, 1, NULL);
	#endif
}

void StartOpenLock2()
{
	bDoor2Opening = TRUE;
	bOpen2Times = 0;
	SetBell2Lock(TRUE);
	Textout("Open Lock ---------- Start ");
	#ifndef UK_CUSTOMERS_NEW_KERNEL
	StartAudioPlay(WF_OPENLOCK, 1, NULL);
	#endif
}

void* ThreadOpenDelayProc( void* p )
{
	//int time = 0;
	static int bTimeing = FALSE;
	while(1)
	{
		
		if ( !bDoorOpening )
		{
			usleep(100);
			continue;
		}
		sleep(1);

		bOpenTimes ++;

#ifdef  RUIYITONG
		if ( bOpenTimes >= 1 )
		{
			ControlIO(BELL_OPENDOOR_2, 0);
		}
#endif
		if ( bOpenTimes >= bparam.stBell.lock_delay )
		{
			bDoorOpening = FALSE;
			bOpenTimes = 0;
			SetBellLock(FALSE);
			Textout("Open Lock ---------- Over ");
		}

		
	}
}


void* ThreadOpen2DelayProc( void* p )
{
	static int bTimeing = FALSE;
	while(1)
	{
		sleep(1);
		if ( !bDoor2Opening )
		{
			sleep(1);
			continue;
		}

		bOpen2Times ++;

		if ( bOpen2Times >= bparam.stBell.lock_delay )
		{
			bDoor2Opening = FALSE;
			bOpen2Times = 0;
			SetBell2Lock(FALSE);
			Textout("Open Lock 2---------- Over ");
		}

		
	}
}

void OnDoorOpenEx()
{
	static pthread_t	threadopendelay = 0;
	if ( threadopendelay == 0 )
	{
		if ( pthread_create( &threadopendelay, NULL, &ThreadOpenDelayProc, NULL ) )
		{
			Textout("[Thread Open Delay Proc] Create Fail...");
		}
		else
		{
			//Textout("[Thread Open Delay Proc] Create Succ");
			pthread_detach(threadopendelay);
		}
	}

	Textout("Open Lock");
	//bDoorOpening = TRUE;	
	StartOpenLock();
}

void OnDoor2OpenEx()
{
	static pthread_t	threadopen2delay = 0;
	if ( threadopen2delay == 0 )
	{
		if ( pthread_create( &threadopen2delay, NULL, &ThreadOpen2DelayProc, NULL ) )
		{
			Textout("[Thread Open 2 Delay Proc] Create Fail...");
		}
		else
		{
			//Textout("[Thread Open 2 Delay Proc] Create Succ");
			pthread_detach(threadopen2delay);
		}
	}

	Textout("Open Lock 2");
	StartOpenLock2();
}

void OnDoorOpen()
{
#if 1
    #ifdef BAGGIO_API
    NvrAlarmSend(eDoorBell_Button);
    #endif
    
    OnDoorOpenEx();
#endif

#ifdef DINGDONG
    SetMcuNotyceFlag(1);
#endif

}

void OnDoor2Open()
{
    #ifdef BAGGIO_API
    NvrAlarmSend(eDoorBell_Button);
    #endif
    
    OnDoor2OpenEx();
}

/* add begin by yiqing, 2016-03-26,马上开锁关锁函数*/
//door: 1=锁1 2=锁2
//value:  1=开锁  0=关锁
void OnDoorUnlock(char door,char value)
{
	Textout("OnDoorUnlock  door:%d  value:%d",door,value);
#ifdef ZHENGSHOW
    if ( bparam.stBell.lock_type == 1)//nc
    {
        if(1 == value )
        {
        	if(1 == door)
        	{
				ControlIO(BELL_OPENDOOR, 0);
			}
			else if(2 == door)
			{
				ControlIO(BELL_OPENDOOR2, 0);
			}  
        }
        else
        {
			if(1 == door)
        	{
				ControlIO(BELL_OPENDOOR, 1);
			}
			else if(2 == door)
			{
				ControlIO(BELL_OPENDOOR2, 1);
			}
        }
    }
    else                               //no
    {
		if(1 == door)
    	{
			ControlIO(BELL_OPENDOOR, value);
		}
		else if(2 == door)
		{
			ControlIO(BELL_OPENDOOR2, value);
		}
    }
#endif
}



