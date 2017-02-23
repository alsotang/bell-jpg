#include<stdio.h>
#include<stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#include "param.h"
#include "debug.h"

#include "sensorapi.h"

#include "ak3894_api.h"

unsigned char videocmd = 0;
unsigned short videoparam = 0;
unsigned char videoctrl = 0;

char videoCaptureFlag = 1;//标记当前是否采集视频，由于上电初始化就采集，所以标记为1

//#ifdef SENSOR_3894
uvcCtrlParam_t uvcCtrlParam;
//#endif

sem_t   savesem;
sem_t   camsem;

void NoteCamSem( void )
{
    sem_post( &camsem );
}


void NoteSaveSem()
{
    sem_post( &savesem );
}

void VideoParamInit_8433( void )
{
#ifdef SENSOR_8433
#ifdef USE_SENSOR_DEFAULT

    if ( GetUseSensorDefaultFlag() == 1 ) {
#ifdef BELINK
        bparam.stVencParam.bysize = 0;
        bparam.stVencParam.brightness = 128;
        bparam.stVencParam.contrast = 136;
        bparam.stVencParam.saturation = 134;
        bparam.stVencParam.chroma = 0;
#else
        TSENSORDEFAULT param;
        GetSensorDefault( &param );

        SetUseSensorDefaultFlag( SENSOR_DEFAULT_DISABLE );

        bparam.stVencParam.brightness = param.brightness;
        bparam.stVencParam.contrast = param.contrast;
        bparam.stVencParam.saturation = param.saturation;
        bparam.stVencParam.chroma = param.hue;
#endif


        Textout( "Sensor default,brightness=%d, contrast=%d, saturation=%d, hue=%d", bparam.stVencParam.brightness,
                 bparam.stVencParam.contrast, bparam.stVencParam.saturation, bparam.stVencParam.chroma );

        NoteSaveSem();
    }
    /* add begin by yiqing, 2015-12-25*/
    //H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );

    H264SetBrightness( bparam.stVencParam.brightness );
    H264SetHue( bparam.stVencParam.chroma );
    H264SetSaturation( bparam.stVencParam.saturation );
    H264SetContrast( bparam.stVencParam.contrast );
#else
    H264SetBrightness( ( bparam.stVencParam.brightness - 128 ) >> 2 );
    H264SetHue( ( bparam.stVencParam.chroma - 128 ) >> 2 );
    H264SetSaturation( bparam.stVencParam.saturation >> 1 );
    H264SetContrast( bparam.stVencParam.contrast / 4 );
#endif

    H264SetMirr( bparam.stVencParam.videomode );

    H264SetGOP( H264_GOP );
    H264SetRateMode( H264_CBR_MODE );
    H264SetBitRate( bparam.stVencParam.bitrate );
#endif
}

void VideoParamInit_3861( void )
{
#ifdef SENSOR_3861
    H264SetBrightness(bparam.stVencParam.brightness);
    H264SetContrast(bparam.stVencParam.contrast >> 3);

    if ( bparam.stVencParam.videoenv > 2 ) {
        bparam.stVencParam.videoenv = 0x00;
    }

    H264EnvMode( bparam.stVencParam.videoenv );

    char mirrflip = bparam.stVencParam.videomode;

#ifdef CHANGE_VIDEO_MIRROR
    if ( mirrflip == 0 )        mirrflip = 4; //normal
    else if ( mirrflip == 1 )   mirrflip = 3; //flip
    else if ( mirrflip == 2 )   mirrflip = 2; //mirr
    else if ( mirrflip == 3 )   mirrflip = 5; //mirr flip
#else
    if ( mirrflip == 0 )        mirrflip = 5; //normal
    else if ( mirrflip == 1 )   mirrflip = 3; //flip
    else if ( mirrflip == 2 )   mirrflip = 2; //mirr
    else if ( mirrflip == 3 )   mirrflip = 4; //mirr flip
#endif
    sleep(1);
    H264SetMirr( mirrflip );
#endif
}

#ifdef SENSOR_3894
void VideoParamInit_3894( void )
{
    bparam.stVencParam.brightness = 128;
    bparam.stVencParam.contrast = 128;
    bparam.stVencParam.saturation = 128;
    bparam.stVencParam.chroma = 90;
	NoteSaveSem();
	
	uvcCtrlParam.cur_value = 0;
	H264_SetUvcCtrlParam(eUvcParam_Brightness,&uvcCtrlParam);//-127---128

	uvcCtrlParam.cur_value = 16;
	H264_SetUvcCtrlParam(eUvcParam_Contrast,&uvcCtrlParam); //0---30

	uvcCtrlParam.cur_value = 0;
	H264_SetUvcCtrlParam(eUvcParam_Hue,&uvcCtrlParam);//-180---180

	uvcCtrlParam.cur_value = 64;
	H264_SetUvcCtrlParam(eUvcParam_saturation,&uvcCtrlParam);//0---127

	uvcCtrlParam.cur_value = 10;
	H264_SetUvcCtrlParam(eUvcParam_Sharpness,&uvcCtrlParam);//0---60

	uvcCtrlParam.cur_value = 90;
	H264_SetUvcCtrlParam(eUvcParam_Gamma,&uvcCtrlParam);//20---250

	uvcCtrlParam.cur_value = 1;
	H264_SetUvcCtrlParam(eUvcParam_WhiteBalanceTemperatureAuto,&uvcCtrlParam);//0---1

	uvcCtrlParam.cur_value = 6000;
	H264_SetUvcCtrlParam(eUvcParam_WhiteBalanceTemperature,&uvcCtrlParam);//2500---7000

	uvcCtrlParam.cur_value = 0;
	H264_SetUvcCtrlParam(eUvcParam_Backlight_Compensation,&uvcCtrlParam);//0---2

	uvcCtrlParam.cur_value = 0;
	H264_SetUvcCtrlParam(eUvcParam_Gain,&uvcCtrlParam);//0---2

	uvcCtrlParam.cur_value = 2;
	H264_SetUvcCtrlParam(eUvcParam_PowerLineFrequency,&uvcCtrlParam);//0---2

}
#endif
void camera_control( unsigned char index, unsigned int param )
{
    char flag = 0;
    int nFlag=0;
    //Textout("========================================================");
    Textout("index:%d, param:%d",index,param);
    if ( videoctrl == 0x00 ) {
        videoparam = param;

        switch ( index ) {
            case 0:         //720p vga qvga
                if ( bparam.stVencParam.bysize == videoparam ) {
                    flag = 0x01;
                    printf( "video size is same\n" );
                }

                else {
                    bparam.stVencParam.bysize = videoparam;
                    printf( "bysize %d\n", bparam.stVencParam.bysize );
                }

                break;

            case 1:         //bright
                bparam.stVencParam.brightness = videoparam;

                if ( bparam.stVencParam.brightness <= 0 ) {
                    bparam.stVencParam.brightness = 0;
                }

                if ( bparam.stVencParam.brightness > 255 ) {
                    bparam.stVencParam.brightness = 255;
                }

                break;

            case 2:         //contrast
                bparam.stVencParam.contrast = videoparam;
                break;

            case 3:         //mode
                bparam.stVencParam.videoenv = videoparam;
                break;

            case 5:         //mirr flip
                bparam.stVencParam.videomode = videoparam;
                break;

            case 6:         //framerate
                if ( videoparam > 0 && videoparam <= 60 ) {
                    bparam.stVencParam.byframerate = videoparam;
                }

                break;

            case 7:         //default
#if defined(SENSOR_3861)
                bparam.stVencParam.brightness = 0;
                bparam.stVencParam.contrast = 128;
#elif defined(BELINK)
                bparam.stVencParam.bysize = 0;
                bparam.stVencParam.brightness = 128;
                bparam.stVencParam.contrast = 136;
                bparam.stVencParam.saturation = 134;
                bparam.stVencParam.chroma = 0;
#elif defined(USE_SENSOR_DEFAULT)
                SetUseSensorDefaultFlag( SENSOR_DEFAULT_ENABLE );
#else
                bparam.stVencParam.brightness = 128;
                bparam.stVencParam.contrast = 128;
                bparam.stVencParam.saturation = 128;
                bparam.stVencParam.chroma = 0;
#endif

                break;

            case 8:         //saturation
                bparam.stVencParam.saturation = videoparam;
                break;

            case 9:         //hue
                bparam.stVencParam.chroma = videoparam;
                break;

            case 10:        //osd
                //bparam.stVencParam.OSDEnable = param;
                break;

            case 12:
                //bparam.stVencParam.byframeratesub = param;
                break;

                /* BEGIN: Added by wupm, 2013/6/6 */
            case 13:
                bparam.stVencParam.bitrate = videoparam;
                break;

            case 14:    //sharpness
                bparam.stVencParam.ircut  = videoparam;
                break;

            case 100:
                bparam.stPTZParam.byRate = videoparam;
                break;

            case 101:
                switch(videoparam) {
                    case 0:
                        Textout("livestream:snapshot video");
#ifdef SENSOR_3861
                        bparam.stVencParam.byframerate = 5;
						bparam.stVencParam.bysize = 1;                 
						SetSnapshotVideo(TRUE);
						H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
#endif

#ifdef SENSOR_3894
						Textout("livestream: 5fps VGA");
						bparam.stVencParam.byframerate = 5;
						bparam.stVencParam.bysize = 0;//VGA
						H264_ChangeResolution(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#endif


                                            
#ifdef SENSOR_8433
						Textout("livestream: 5fps VGA");
                        //MjpgSetSize(3);
						bparam.stVencParam.byframerate = 5;

						if(0 !=bparam.stVencParam.bysize)
						{
							bparam.stVencParam.bysize = 0;//VGA
							H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
						}
						else
						{
							H264SetFrameRate(bparam.stVencParam.byframerate);
						}
						
#endif
                        break;
                    case 1:
                        
#ifdef SENSOR_3861
						Textout("livestream: 5fps QVGA");
                        bparam.stVencParam.byframerate = 5;
						bparam.stVencParam.bysize = 1;
						SetSnapshotVideo(FALSE);
                        H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
#endif

#ifdef SENSOR_3894
						Textout("livestream: 10fps VGA");
						bparam.stVencParam.byframerate = 10;
						bparam.stVencParam.bysize = 0;//VGA
						H264_ChangeResolution(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#endif


#ifdef SENSOR_8433
						Textout("livestream: 10fps VGA");
						bparam.stVencParam.byframerate = 10;
						if(0 !=bparam.stVencParam.bysize)
						{
							bparam.stVencParam.bysize = 0;//VGA
							H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
						}
						else
						{
							H264SetFrameRate(bparam.stVencParam.byframerate);
						}
                        H264SetGOP( bparam.stVencParam.byframerate );
                        //MjpgSetSize(3);	
#endif
                        break;
                    case 2:
                        Textout("livestream: 15fps VGA");
#ifdef SENSOR_3861					
                        bparam.stVencParam.byframerate = 15;
                        bparam.stVencParam.bysize = 0;
                        SetSnapshotVideo(FALSE);
                        H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
#endif		

#ifdef SENSOR_3894
						Textout("livestream: 15fps VGA");
						bparam.stVencParam.byframerate = 15;
						bparam.stVencParam.bysize = 0;//VGA
						H264_ChangeResolution(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#endif

#ifdef SENSOR_8433
						bparam.stVencParam.byframerate = 15;
						if(0 !=bparam.stVencParam.bysize)
						{
							bparam.stVencParam.bysize = 0;//VGA
							H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
						}
						else
						{
							H264SetFrameRate(bparam.stVencParam.byframerate);
						}
                        H264SetGOP( bparam.stVencParam.byframerate );//关键帧间隔
                        //MjpgSetSize(3);
#endif
                        break;
                    case 3:
                        Textout("livestream: 15fps 720P");
                        bparam.stVencParam.byframerate = 15;
                        bparam.stVencParam.bysize = 3;
                        SetSnapshotVideo(FALSE);
#ifdef SENSOR_3894
						H264_ChangeResolution(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#else
                        H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
#endif
#ifdef SENSOR_3894
						H264_SetIFramePeriod(bparam.stVencParam.byframerate);
#else
                        H264SetGOP(bparam.stVencParam.byframerate);
#endif
#ifdef SENSOR_8433
                        //MjpgSetSize(3);
#endif
                        break;
                    default:
                        Textout("Unkown parameter 101, value=%d", videoparam);
                        break;
                }
            default:
                break;
        }

        if ( flag == 0x00 ) {
            videocmd = index;
            videoparam = param;
            videoctrl = 1;
            NoteCamSem();

            /* BEGIN: Added by yiqing, 2015/4/14 */
            NoteSaveSem();
        }
    }

    else {
        printf( "video process %d videocmd %d\n", videoctrl, videocmd );
    }
}

void VideoParamChange( void )
{
    //Textout("*************************************************************");
    Textout("videocmd:%d",videocmd);
    if ( videoctrl == 0x00 ) {
        return;
    }

    switch ( videocmd ) {
        case 0:         //720p vga qvga
#ifdef SENSOR_3894
			H264_ChangeResolution(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#else
            H264SetSize(bparam.stVencParam.bysize, bparam.stVencParam.byframerate );
#endif
            break;

        case 1:
#if defined(SENSOR_3861) || defined(USE_SENSOR_DEFAULT)
            H264SetBrightness(bparam.stVencParam.brightness);
#elif defined (SENSOR_8433)
            H264SetBrightness( ( bparam.stVencParam.brightness - 128 ) >> 2 );
#elif defined (SENSOR_3894)
			uvcCtrlParam.cur_value = (bparam.stVencParam.brightness - 127);
			H264_SetUvcCtrlParam(eUvcParam_Brightness,&uvcCtrlParam);
#endif

            break;

        case 2:
#if defined(SENSOR_3861)
            H264SetContrast(bparam.stVencParam.contrast >> 3);
#elif defined(USE_SENSOR_DEFAULT)
            H264SetContrast( bparam.stVencParam.contrast );
#elif defined(SENSOR_8433)
            H264SetContrast( bparam.stVencParam.contrast / 4 );
#elif defined(SENSOR_3894)
			uvcCtrlParam.cur_value = (bparam.stVencParam.contrast /8);
			if(uvcCtrlParam.cur_value >30)
				uvcCtrlParam.cur_value = 30;
			H264_SetUvcCtrlParam(eUvcParam_Contrast,&uvcCtrlParam);
#endif
            break;

        case 3:         //mode
#ifdef SENSOR_3894
			uvcCtrlParam.cur_value = videoparam;
			H264_SetUvcCtrlParam(eUvcParam_PowerLineFrequency,&uvcCtrlParam);
#else
            H264EnvMode(videoparam);
#endif
            break;

        case 5:         //mirr flip
#ifdef SENSOR_3861
#ifdef CHANGE_VIDEO_MIRROR
            if ( videoparam == 0 )  videoparam = 3; //normal
            else if ( videoparam == 1 )     videoparam = 5; //flip
#else
            if ( videoparam == 0 )      videoparam = 5; //normal
            else if ( videoparam == 1 )      videoparam = 3; //flip
#endif
            else if ( videoparam == 2 )      videoparam = 2; //mirr
            else if ( videoparam == 3 ) videoparam = 4;     //mirr flip
#endif

#ifdef SENSOR_3894
			H264_SetMirr(videoparam);
#else
            H264SetMirr( videoparam );
#endif
            break;

        case 6:         //framerate
#ifdef SENSOR_3894
			H264_ChangeResolution(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#else
            H264SetFrameRate(bparam.stVencParam.byframerate);
#endif
            break;

        case 7:
#if defined (SENSOR_3861)
            VideoParamInit_3861();
#elif defined (SENSOR_8433)
            VideoParamInit_8433();
#elif defined (SENSOR_3894)
			VideoParamInit_3894();
#endif
            break;

        case 8:         //saturation
#ifdef SENSOR_3894     
			uvcCtrlParam.cur_value = (bparam.stVencParam.saturation >> 1);
			H264_SetUvcCtrlParam(eUvcParam_saturation,&uvcCtrlParam);
#else
#ifdef USE_SENSOR_DEFAULT
            H264SetSaturation( bparam.stVencParam.saturation );
#else
            H264SetSaturation( bparam.stVencParam.saturation >> 1 );
#endif
#endif
            break;

        case 9:         //hue
#ifdef SENSOR_3894
			uvcCtrlParam.cur_value = (bparam.stVencParam.chroma - 90)*2;
			H264_SetUvcCtrlParam(eUvcParam_Hue,&uvcCtrlParam);
#else
#ifdef USE_SENSOR_DEFAULT
            H264SetHue( bparam.stVencParam.chroma );
#else
            H264SetHue( ( bparam.stVencParam.chroma - 128 ) >> 2 );
#endif
#endif
            break;

        case 10:        //osd
            //bparam.stVencParam.OSDEnable = param;
            break;

        case 12:
            //bparam.stVencParam.byframeratesub = param;
            break;

		case 13:
#ifdef SENSOR_3894
			H264_SetBitrate( bparam.stVencParam.bitrate );
#else
			H264SetBitRate( bparam.stVencParam.bitrate );
#endif
			break;

        case 14:    //sharpness
            //bparam.stVencParam.sharpness = videoparam;
            //H264SetShapness();
            break;

        default:
            Textout("Unkown cmd=%d", videocmd);
            break;
    }

    videoctrl = 0;
}

void* videoparamProc( void* p )
{
    if ( ( sem_init( &camsem, 0, 0 ) ) != 0 ) {
        printf( "sem init failed\n" );
    }

    while ( 1 ) {
        sem_wait( &camsem );
        VideoParamChange();
        usleep( 500*1000 );

    }
}
void* FlashSaveProc( void* p )
{
    if ( ( sem_init( &savesem, 0, 0 ) ) != 0 ) {
        printf( "sem init failed\n" );
    }

    while ( 1 ) {
        sem_wait( &savesem );
        SaveSystemParam( &bparam );
    }
}
void StopVideoCaptureEx()
{
    if(1 == videoCaptureFlag) {
		printf("StopVideoCapture\n");
#ifdef SENSOR_3894
		H264_StopVideoCapture();
#else
        StopVideoCapture();
#endif
        videoCaptureFlag = 0;
    }
}

void StartVideoCaptureEx()
{
    if(0 == videoCaptureFlag) {
		printf("StartVideoCapture7\n");
#ifdef SENSOR_3894
		H264_StartVideoCapture(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#else
        StartVideoCapture(bparam.stVencParam.bysize, bparam.stVencParam.byframerate);
#endif
#if defined(SENSOR_8433)
        VideoParamInit_8433();
#elif defined(SENSOR_3861)
        VideoParamInit_3861();
#endif
		videoCaptureFlag = 1;
    }
}

void NoteMainStreamSend()
{
    NoteP2pUser();
    NoteJpegUser();
    //NoteSDUser();
}

unsigned char GetMainFrameRate()
{
    return bparam.stVencParam.byframerate;
}

unsigned char GetSubFrameRate()
{
    return bparam.stVencParam.byframerate; 
}

void VideoInInit( void )
{
    pthread_t   videoparamthread;
    pthread_t       savethread;

    pthread_create( &savethread, 0, &FlashSaveProc, NULL );
    pthread_create( &videoparamthread, 0, &videoparamProc, NULL );

    pthread_detach(savethread);
    pthread_detach(videoparamthread);
}


