#include "init.h"
#include "alarm.h"
#include "record.h"
#include "capture.h"
#include "public.h"
#include "param.h"
#include "cmdhead.h"
#include "dns.h"
#include "ipc.h"
#include "nvram.h"
#include <string.h>
#include "debug.h"

void IPCStart( void ) 			//date init
{
    IPCInit();
    IPCThread();
}

void SysParamInit( void ) 		//system param init
{
    char* pdst = NULL;
    int iRet;
    /* BEGIN: Added by wupm, 2013/3/12 */
#ifdef	HONESTECH
    ReadHTClassParams();
#endif
    InitSystemParam();
	Textout("Read Config File , UUID = [%s], MAC = [%s]",
		bparam.stIEBaseParam.dwDeviceID,
		bparam.stIEBaseParam.szMac		);
	Textout("ApiLisense = [%s]",bparam.stIEBaseParam.dwApiLisense);
    nvram_init( RT2860_NVRAM );
    IPCStart();             //ipc init
    #ifndef NOT_READ_MAC
    ReadFactoryMac();		//read mac
	Textout("ReadFactoryMac, UUID = [%s], MAC = [%s]",
		bparam.stIEBaseParam.dwDeviceID,
		bparam.stIEBaseParam.szMac		);
	Textout("ApiLisense = [%s]",bparam.stIEBaseParam.dwApiLisense);
    #endif
    ReadRactoryID();		//read deviceid
	Textout("ReadRactoryID, UUID = [%s], MAC = [%s]",
		bparam.stIEBaseParam.dwDeviceID,
		bparam.stIEBaseParam.szMac		);
	Textout("ApiLisense = [%s]",bparam.stIEBaseParam.dwApiLisense);
    //ReadDnsFactory();		//read dns factory
    ConfigVersion();		//config system version
    DateInit();

    FactoryUpdateInit();
}

void JpegInit( void )
{
    char temp[64];
    memset( temp, 0x00, 64 );
    sprintf( temp, "chmod a+x /system/system/bin/jpeg" );
    DoSystem( temp );
    memset( temp, 0x00, 64 );
    sprintf( temp, "/system/system/bin/jpeg &" );
    DoSystem( temp );
}

void JpegThreadStart( void )
{
    JpegInit();
}

void InsmodUvcDriver()
{
    Textout("=================Insmod uvc driver==================");
    DoSystem("insmod /lib/modules/2.6.21/kernel/drivers/media/video/v4l2-common.ko");
    DoSystem("insmod /lib/modules/2.6.21/kernel/drivers/media/video/compat_ioctl32.ko");
    DoSystem("insmod /lib/modules/2.6.21/kernel/drivers/media/video/v4l1-compat.ko");
    DoSystem("insmod /lib/modules/2.6.21/kernel/drivers/media/video/videodev.ko");
    #if defined (SENSOR_3861) || defined (SENSOR_3894)
    DoSystem("insmod /lib/modules/2.6.21/kernel/drivers/media/video/uvc/uvcvideo.ko");
	Textout("=================Insmod uvc driver SENSOR_3861 | SENSOR_3894 end==================");
    #else
    DoSystem("insmod /system/system/lib/uvcvideo.ko");
	Textout("=================Insmod uvc driver 8433 end==================");
    #endif
    
}

void RmmodUvcDriver()
{
    Textout("=================Rmmod uvc driver==================");
    DoSystem("rmmod uvcvideo");
    DoSystem("rmmod videodev");
    DoSystem("rmmod v4l1-compat");
    DoSystem("rmmod compat_ioctl32");
    DoSystem("rmmod v4l2-common");
}

void SensorInit( void ) 			//sensor init
{
#ifdef INSMOD_UVC_DRIVER
    InsmodUvcDriver();
#endif
    //sleep(2);

#if defined (SENSOR_8433)
	bparam.stVencParam.bysize = 0;	
	bparam.stVencParam.byframerate = 10;
#elif defined (SENSOR_3894)
	bparam.stVencParam.bysize = 0;	
	bparam.stVencParam.byframerate = 10;
#else
	bparam.stVencParam.bysize = 1;	//QVGA
	bparam.stVencParam.byframerate = 15;
	//bparam.stVencParam.bysize = 0;	//VGA
	//bparam.stVencParam.byframerate = 30;
#endif

#ifdef SENSOR_3894
	Textout("SENSOR_3894 init");
	H264_VideoInit(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
	MJPG_VideoInit(1,bparam.stVencParam.byframerate);
#else
	InitSensorLib(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
#endif	

    VideoInInit();
}

void VencStart( void ) 			//video codec is start
{
    VCodecStart();
#ifndef SENSOR_3894
    H264EncThread();
#endif
}

void NetCmdStart( void ) 			//network command init and thread is start
{
    NetCmdInit();
    NetCmdThread();
}

void LogStart( void ) 			//log init
{
    LogInit();
}

void DnsStart( void ) 			//dns init
{
    DnsInit();
    DnsThread();
}

void UpnpStart( void ) 			//Upnp init
{
    UpnpInit();
    UpnpThread();
}

void RegisterStart( void ) 		//Register init
{
    RegisterInit();
    RegisterThread();
}


