#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "init.h"
#include "alarm.h"
#include "record.h"
#include "capture.h"
#include "public.h"
#include "param.h"
#include "cmdhead.h"
#include "debug.h"

char  appfindstring[128];
char  sysfindstring[128];

void FactoryUpdateInit( void )
{
    memset( appfindstring, 0x00, 128 );
    memset( sysfindstring, 0x00, 128 );
    strcpy( appfindstring, "ifi-camera-app-qazwsxedcrfvtgba" );             //wifi-camera-app-qazwsxedcrfvtgbaw
    strcpy( sysfindstring, "ifi-camera-sys-qetyipadgjlzcbmn" );             //wifi-camera-sys-qetyipadgjlzcbmnw
}

unsigned char nVersion = 10;
unsigned char GetMinorVersion()
{
    return nVersion;
}

unsigned char GetMajorVersion()
{
    return MAJOR_VERSION;
}
void ConfigVersion( void )
{
    bparam.stIEBaseParam.factory  = 0;

#ifdef FOBJECTTEST
    nVersion = 14;
#endif

#ifdef FOBJECT
    //0.3.11.15 1)mail alarm
    //0.3.11.16 1)calling wave 2)433 control
    //0.3.11.17 1)WF_CALLING 2)AP Mode wifi scan
    //0.3.12.18 1)Baggio.wu
    //0.3.12.19 1)FM34
    //0.3.12.20 1)jPush
    //0.3.12.21 1)jPush add apns_production=1
    //0.3.12.22 1)phoneDateSync
    //0.3.11.23
    //0.3.11.24 1)define P2P_BIZ_LIB
    //0.3.11.25 1)define BAGGIO_API
    //0.3.12.26 1)use libBPPP_API_20150423.a
    //0.3.12.27 1)define XGPUSH 2)use libPPPP_API_20150529
    //0.3.12.28 1)define LDPUSH 2)use libPPPP_API_20150609
    //0.3.12.29 1)sync
    //0.3.12.30 1)not pop socket when password error
    //0.3.11.31 1)sync
    //0.3.12.31 1)sync
    nVersion = 31;
#endif

#ifdef FOBJECT_FM34
    //60.3.12.20 1)BASE OF 0.3.12.19
    //60.3.21.21 1)AIT 8433
    //60.3.11.22 1)3861
    //9.4.11.10 1)PIR ALARM
    //9.4.11.11 1)reduce volume
    //9.4.12.12 1)where update app ,only delete /system/Wireless/*.wav
    //9.4.12.13  1)set mic vol:0x0080  speak vol:0x1200 2)JPUSH and BIZ 3)SetBellFlashing where call or start AP
    //9.4.22.14  1)8433 2)use libPPPP_API_20150423.a
    //9.4.22.15  1)8433 2)open api
    //9.4.12.14  1)use libPPPP_API_20150423.a
    //9.4.12.15  1)Improve the startup speed
    //9.4.22.16  1)8433
    //9.4.12.16  1)use libPPPP_API_20150519.a
    //9.4.12.17  1)set mic vol:0x0400  speak vol:0x1200
    //9.4.12.18  1)sync

    /* add begin by yiqing, 2015-06-15, ԭ��: */
    //1)use libPPPP_API_20150609.a 2)define LDPUSH
    //9.4.12.19
    //9.4.22.19  //8433

    /* add begin by yiqing, 2015-06-26, ԭ��: */
    //9.4.12.20 //lock_type = 0  no

    /* add begin by yiqing, 2015-07-16, ԭ��: ������Ƶ��λ����*/
    /* add begin by yiqing, 2015-08-27, ԭ��: ������Ƶ��λ����,ÿ�ΰ�����ʱ����fm34�Ƿ񷵻�0x5a5a*/
    //9.4.12.21

    /* add begin by yiqing, 2015-09-11*/
    //�������ʱ����λfm34оƬ���µ�����������⣬����:��i2c��̶��ѹ��Ž����߹رչ��š�
    //9.4.12.22

    /* add begin by yiqing, 2015-10-28*/
    //�ı�fm34����λ�ã���֮ǰ����ʱ����Ϊ���г�ʱ���߽�ͨ����
    //9.4.12.23

    /* add begin by yiqing, 2015-11-05*/
    //use libPPPP_API_20151105.a
    //�����ַ���
    //9.4.12.24
    //9.4.22.24
    /* add begin by yiqing, 2015-11-20*/
    //use libPPPP_API_20151112.a
    //9.4.12.25

    /* add begin by yiqing, 2015-11-26*/
    //use libPPPP_API_20151123.a
    //9.4.12.26
    //9.4.11.26

    nVersion = 26;
#endif

#ifdef FUHONG
    //12.3.11.10 1)3861
    //12.3.11.11 1)IR led ctrl 2)status led ctrl
    //12.3.11.12 1)flip
    //12.3.11.13 1)mirror-flip
    nVersion = 13;
#endif

#ifdef EYESIGHT
    //15.3.11.10 1)BASE OF 60.3.11.22 2)8433
    nVersion = 10;
#endif

#ifdef JINQIANXIANG
    //16.3.11.10 1)3861
    nVersion = 10;
#endif


#ifdef KANGJIEDENG
    //5.3.12.16 1)initial version
    nVersion = 16;
#endif

#ifdef FRISEN
    nVersion = 14;
#endif

#ifdef FACTOP
    nVersion = 14;
#endif

#ifdef YUELAN
    //7.3.11.10
    //7.3.11.11 1)send mail, when calling
    nVersion = 11;
#endif

#ifdef BELINK
    //11.3.12.10

    /* add begin by yiqing, 2015-10-31,8433*/
    //11.3.22.10

    /* add begin by yiqing, 2015-11-09���������ַ���*/
    //11.3.22.11

    /* add begin by yiqing, 2015-11-11,���л��߼��ʱ�򿪺���Ƶ�Դ���ۿ�ʱ������*/
    //11.3.22.12

    /* add begin by yiqing, 2015-11-26*/
    //ʹ����obj�ַ���
    //ʹ��libPPPP_API_20151123.a
    //11.3.22.13

    /* add begin by yiqing, 2015-12-24*/
    //��������״̬��MOTO_D2
    //�޸���Ƶ����
    //11.3.22.14

    /* add begin by yiqing, 2015-12-29ʹ��LibPPPP_API_20151211.a*/
    //11.3.22.15
    nVersion = 15;
#endif



#ifdef FEEDDOG
    //9.3.12.14
    //9.3.12.15 1)status led 2)red led 3)wave file
    //9.3.12.16 1)8388s 0x12 ctrl mic volume
    //9.3.12.17 1)wave file play 2)8388s mic PGA(0x12)
    //9.3.12.18 1)8388s mic PGA(0x12) restore
    //9.3.12.19 1)WF_CALLING 2)AP Mode wifi scan
    //9.3.12.20 1)8388s PGA(0x12) 0xda->0xe2
    //9.3.12.21 1)private API
    //9.3.12.22 1)JPUSH and Biz
    //9.3.12.23 1)where at www,not open lock
    //9.3.12.24 1)use libPPPP_API_20150423.a 2)define BAGGIO_API
    //9.3.12.25 1)Improve the startup speed
    //9.2.12.10 1)old kernel
    //9.3.12.26 1)Modify lock configuration
    //9.3.12.27 1)use libPPPP_API_20150519.a
    //9.2.12.11 1)old kernel 2)use libPPPP_API_20150519.a
    //9.3.12.28 1)new kernel 2)use libPPPP_API_20150609.a  3)define LDPUSH
    //9.3.12.29 1)define ZHONGKONG
    /* add begin by yiqing, 2015-11-05*/
    //9.3.12.29 1)use libPPPP_API_20151105.a 2)use new string
    nVersion = 29;

#endif

#ifdef ZIGBEE
    //8.3.12.14
    //8.3.12.15 1)forbidden reset key
    //8.3.12.16 1)BELL_CALL_LED high 6 second
    //8.3.12.17 1)PhoneDateSync
    //8.3.12.18 1)PIR Alarm
    nVersion = 18;
#endif

#ifdef KONX
    nVersion = 14;
#endif

#ifdef ZILINK
    //3.3.1214    1)XQ libBPPP_API.a 2)factory version
    //3.3.12.15    1)8002 ctrl _MOTO_D5->_MOTO_D0
    //3.3.12.16    1)use libBPPP_API.a
    //3.3.12.17    1)unuse libBPPP_API.a
    //3.3.12.18     1)reuse libBPPP_API.a
    //3.3.12.19     1)use libPPP_API.a
    //3.3.12.20     1)biz server
    //3.3.12.21     1)OLD P2P 2)BIZ TEST SERVER
    //3.3.12.22     1)remove Encrypt
    //3.3.12.23     1)Update wolfson WM8988/WM8750 driver
    //3.3.12.24     1)syspack all of resource
    //3.3.11.25     1)max val 127   2)Automatically set the time zone
    //3.3.11.26
    //3.3.12.26
    //3.3.12.27     1)where VideoParamInit_3861 end��sleep(1)��2)JPUSH and Biz
    //3.3.12.28     1)biz:b_calling jPush:j_calling
    //3.3.12.29     1)use libPPPP_API_20150423.a
    //3.3.12.30     1)Setting up call waiting time of 40 seconds
    //3.3.12.31     1)use libPPPP_API_20150519.a
    //3.3.12.32     1)where stop talk,set led off;
    //3.3.12.33     1)Optimization of sound processing
    //3.3.12.34     1)define XGPUSH 2)use libPPPP_API_20150529
    //3.3.12.35     1)use libPPPP_API_20150609 2)define LDPUSH
    //3.3.12.36     1)set lock_type = 0 2)waiting time of 40 3)opening lock is 5
    //3.3.12.37     1)can delete the log
    /* add begin by yiqing, 2015-08-31, ԭ��:������������ģʽ��8���Ϊ5�� */
    //3.3.12.38
    /* add begin by yiqing, 2016-01-21*/
    //3.3.12.39     1)use libPPPP_API_20151211.a  2)sync
    nVersion = 39;
#endif

#ifdef ZHENGSHOW
    //4.3.11.14
    //4.3.11.15     1)use jPush
    //4.3.12.16     1)jPush and Biz
    //4.3.12.17     1)old kernel
    //4.3.12.18     1)old kernel biz:b_calling jPush:j_calling
    //4.3.12.19     1)old kernel where init delete other *.wav  2)define DEFAULT_UNABLE
    //4.3.12.20     1)old kernel new lib,new string,test p2p
    //4.3.12.21
    //4.3.12.22     1)old kernel use libPPPP_API_20150423.a,old BIz
    //4.3.12.23     1)old kernel   2)Improve the startup speed  3)own
    //4.3.12.23     1)old kernel   2)UK customers
    //4.3.12.24     1)new kernel   2)UK customers
    //4.3.12.24     1)new kernel   2)own
    //4.3.12.25     1)old kernel   2)own   3)define LOCK_TYPE_NC
    //4.3.12.26     1)old kernel   2)UK   3)use libPPPP_API_20150508.a,old BIz
    //4.3.12.27     1)old kernel   2)use libPPPP_API_20150511.a 3)UK
    //4.3.12.28     1)old kernel   2)use libPPPP_API_20150511.a 3)own
    //4.3.12.29     1)old kernel   2)use libPPPP_API_20150514.a 3)own
    //4.3.12.30     1)old kernel   2)use libPPPP_API_20150515.a 3)own
    //4.3.12.30     1)old kernel   2)use libPPPP_API_20150515.a 3)UK
    //4.3.12.31     1)new kernel   2)use libPPPP_API_20150515.a 3)own
    //4.3.12.32     1)new kernel   2)use libPPPP_API_20150516.a 3)own
    //4.3.12.33     1)old kernel   2)use libBPPP_API_20150516.a 3)UK
    //4.3.12.34     1)old kernel   2)use libPPPP_API_20150519.a 3)UK
    //4.3.12.35     1)new kernel   2)use libPPPP_API_20150519.a 3)own
    //4.3.12.36     1)new kernel   2)own 3)define LOCK_TYPE_NC
    //4.3.12.37     1)old kernel   2)use libPPPP_API_20150529.a 3)UK 4)define LDPUSH
    //4.3.12.38     1)old kernel   2)use libPPPP_API_20150609.a 3)UK

#if defined  (OLD_KERNEL_OBJ)
    /* add begin by yiqing, 2015-06-11, ԭ��: */
    //1)old kernel   2)use libPPPP_API_20150609.a 3)own
    //4.4.12.10

    /* add begin by yiqing, 2015-06-13, ԭ��:�������bug */
    //4.4.12.11

    /* add begin by yiqing, 2015-07-06, ԭ��: ����������������ֻ���*/
    //where GetPlayAlarmAudioState == 1,usleep(1000*1000)
    //4.4.12.12
    nVersion = 12;
    //nVersion = 24;

#elif  defined (UK_CUSTOMERS_OLD_KERNEL)
    /* add begin by yiqing, 2015-06-11, ԭ��:ͬ��4.3.12.38�汾 */
    //4.3.12.38

    /* add begin by yiqing, 2015-06-13, ԭ��: �������bug*/
    //4.3.12.39

    /* add begin by yiqing, 2015-09-04, ԭ��: ȥ���������ÿ�����ʱΪ1s*/
    //4.3.12.40

    /* add begin by yiqing, 2015-10-21,���е�ʱ���ӳ�2��������*/
    //4.3.12.41

    /* add begin by yiqing, 2015-11-05,��������ǰ��汾���irc���ƺ���ɵľ�ͷ�����Ʋ���������*/
    //4.3.12.42
    nVersion = 42;

#elif  defined (UK_CUSTOMERS_NEW_KERNEL)
    /* add begin by yiqing, 2015-06-11, ԭ��:ͬ��4.3.12.38�汾 */
    //4.5.12.10

    /* add begin by yiqing, 2015-06-13, ԭ��: �������bug*/
    //4.5.12.11

    /* add begin by yiqing, 2015-09-04, ԭ��: ȥ���������ÿ�����ʱΪ1s*/
    //4.5.12.12

    /* add begin by yiqing, 2015-10-09,���е�ʱ���ӳ�2������*/
    //4.5.12.13

    /* add begin by yiqing, 2015-11-05,��������ǰ��汾���irc���ƺ���ɵľ�ͷ�����Ʋ���������*/
    //4.5.12.14

    /* add begin by yiqing, 2016-03-28*/
    //#define SUPPORT_FM34
    //#define NEW_BRAOD_AES
    //4.5.12.15

    /* add begin by yiqing, 2016-05-13*/
    //���͵�ʱ��һ̨�����������ͻ���ȡ����������
    //��������p2p
    //����������ȡ���ͼģʽ����Ƶ���ȵ�ģʽ
    //#undefine NEW_BRAOD_AES
    //���ApiLisense,8Byte,DeviceId ��32Byte��Ϊ24Byte
    //4.5.12.16

    /* add begin by yiqing, 2016-05-19*/
    //#define NEW_BRAOD_AES
    //4.5.12.17

	/* add begin by yiqing, 2016-06-07,test*/
	//undefine NEW_BRAOD_AES
	//4.5.12.18

	/* add begin by yiqing, 2016-06-08*/
	//�������biz���ͺ������������������Ͳ��˵�����
	//4.5.12.19
    

	/* add begin by yiqing, 2016-06-20*/
	//�ɰ�����ӵ��������͹���
	//undefine PPCS_AES_P2P
	//undefine NEW_BRAOD_AES
	//4.5.12.20

	/* add begin by yiqing, 2016-06-21*/
	////define PPCS_AES_P2P
	//4.5.11.20

	/* add begin by yiqing, 2016-06-20*/
	//check_user.cgi���type�ֶΣ��°��ӷ���type=1
	//define PPCS_AES_P2P
	//define NEW_BRAOD_AES
	//4.5.12.21

	/* add begin by yiqing, 2016-07-14*/
	//undefine NEW_BRAOD_AES
	//ʹ���������Ͽ�
	//4.5.12.22

	/* add begin by yiqing, 2016-07-14*/
	//ʹ���������¿�
	//undefine NEW_BRAOD_AES
	//4.5.11.22

	/* add begin by yiqing, 2016-07-19*/
	//define FCM_PUSH
	//4.5.11.23

	/* add begin by yiqing, 2016-07-19*/
	//sync
	//4.5.12.23
	nVersion = 23;

#elif defined (PREFIX_OBJ)  //new kernel
    /* add begin by yiqing, 2015-06-11, ԭ��: */
    //4.6.12.10

    /* add begin by yiqing, 2015-06-13, ԭ��:�������bug */
    //4.6.12.11
    nVersion = 11;

#elif defined (PREFIX_ZSKJ)
    /* add begin by yiqing, 2015-06-11, ԭ��: */
    //4.7.12.10

    /* add begin by yiqing, 2015-06-13, ԭ��: �������bug*/
    //4.7.12.11

    /* add begin by yiqing, 2015-06-29, ԭ��:��ʱ���԰汾���ɺ� */
    //4.7.12.12-test

    /* add begin by yiqing, 2015-07-06, ԭ��: ��ʱ���԰汾 �ɺ� ����������������ֻ���*/
    //where GetPlayAlarmAudioState == 1,usleep(1000*1000)
    //4.7.12.13-test

    /* add begin by yiqing, 2015-07-08, ԭ��:�����ſͻ�������ʱֹͣ�ɼ���Ƶ */
    //4.7.12.14-test

    /* add begin by yiqing, 2015-07-23, ԭ��:ͬ�����İ�� */
    //4.7.12.15

    /* add begin by yiqing, 2015-08-28, ԭ��: ���Žŷ��򣬸�Ϊ����ʱ���ߣ�����������*/
    //4.7.12.16
    /* add begin by yiqing, 2015-08-31, ԭ��: */
    //4.7.12.17

    /* add begin by yiqing, 2015-09-04, ԭ��:�ֻ���ͨ��֪ͨmcu��mcu������֪ͨ�����˳����� */
    //4.7.12.18

    /* add begin by yiqing, 2015-09-22,��PIR����*/
    //4.7.12.19

    /* add begin by yiqing, 2015-10-14,FM34*/
    //4.7.12.20

    /* add begin by yiqing, 2015-10-28,��fm34�ļ���ɺ��е�ʱ���Ϊ���г�ʱ���߽�ͨ��*/
    //4.7.12.21


    /* add begin by yiqing, 2015-10-28,֪ͨ��Ƭ���ܽ���D3��ΪD6*/
    //4.7.12.22

    /* add begin by yiqing, 2015-11-04,�޸Ľ�ͨ�����Ͽ������û��Ƶû������bug��������������*/
    //4.7.12.23

    /* add begin by yiqing, 2016-03-17*/
    //define YINETWORK
    //4.7.12.24

    /* add begin by yiqing, 2016-03-22,use daemon.bell.v22,�޸�mac��ַΪ���*/
    //undefine SUPPORT_FM34
    //4.7.12.25

    /* add begin by yiqing, 2016-04-01,*/
    //4.7.12.26


    /* add begin by yiqing, 2016-04-01*/
    //4.7.11.26

    /* add begin by yiqing, 2016-04-06*/
    //4.7.12.27
    //define SUPPORT_FM34
    //define SUPPORT_IRCUT

    /* add begin by yiqing, 2016-07-06*/
	//undefine SUPPORT_FM34
	//undefine SUPPORT_IRCUT
    //4.7.11.28

	/* add begin by yiqing, 2016-07-08*/
	//sync
	//4.7.12.29
    //define SUPPORT_FM34
    //define SUPPORT_IRCUT

	/* add begin by yiqing, 2016-07-12*/
	//sync
	//4.7.11.29

	/* add begin by yiqing, 2016-07-15*/
	//4.7.11.30
	//gcm fcm
    nVersion = 30;

#elif defined (OLD_KERNEL_XDBL)
    //4.8.12.10
    nVersion = 10;

#elif defined (NEW_KERNEL_XDBL)
    //4.9.12.10
    nVersion = 10;

#elif defined (PPCS_P2P_TEST)
    //4.10.11.10

    /* add begin by yiqing, 2016-05-03,���͵�ʱ��һ̨�����������ͻ���ȡ����������*/
    //4.10.11.11

    /* add begin by yiqing, 2016-05-10,test*/
    //define SUPPORT_FM34
    //define SUPPORT_IRCUT
    //����Ÿ�İ�׿����
    //4.10.11.12

    /* add begin by yiqing, 2016-05-13*/
    //����aes���ַ�����id
    //4.10.11.13
    nVersion = 13;

#elif defined (PREFIX_8433)
	/* add begin by yiqing, 2016-07-08*/
	//ʹ������Ƽ������Ʒ�����
	//8433
	//4.10.21.10
	nVersion = 10;
#endif

#endif

#ifdef BAFANGDIANZI
    //61.3.21.10     1)8433
    //61.3.11.10     1)3861
    //61.3.11.11     1)where set camera param ,save the param
    //61.3.21.11
    //61.3.11.12     1)set default frameRate:30 Resolution:VGA(720P)
    //61.3.11.13     1)set default bparam.stVencParam.byframerate = 60;
    /* add begin by yiqing, 2015-08-07, ԭ��:���¾�ͷ��֡�ʵ���100��vga */
    //61.3.11.14
    nVersion = 14;
#endif


    bparam.stIEBaseParam.sys_ver  = ( CUSTOMER_ID << 24 ) | ( MAJOR_VERSION << 16 ) | (VER_SOFTWARE << 8) | nVersion;
    Textout( "========sys_ver 0x%08x==========", bparam.stIEBaseParam.sys_ver );
    Textout( "========sys_ver %d.%d.%d.%d",CUSTOMER_ID,MAJOR_VERSION,VER_SOFTWARE,nVersion);
}

void SendSystemVer( void )
{
    NotifyToDaemon( 0x03, &bparam, sizeof( IEPARAMLIST ) );
}


