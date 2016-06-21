#if	1
/* * Standard includes */
#include <ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/soundcard.h>

/* * Mandatory variables. */
#define BUF_SIZE 4096
int audio_fd;
unsigned char audio_buffer[BUF_SIZE];

char* DEVICE_NAME = "/dev/dsp";
int open_mode = O_RDONLY;	//O_RDONLY, O_WRONLY, O_RDWR

int startRecord()
{
    //Open device
    if ( ( audio_fd = open( DEVICE_NAME, open_mode, 0 ) ) == -1 )
    {
        /* Open of device failed */
        printf("Can not Open Audio Device %s\n", DEVICE_NAME);
        return -1;
    }

	int mask;

    if ( ioctl( audio_fd, SNDCTL_DSP_GETFMTS, &mask ) == -1 )
    {
        /* Handle fatal error ... */
		printf("SNDCTL_DSP_GETFMTS ERROR\n");
		return -1;
    }

	printf("Support Audio Format = 0x%08X", (unsigned int)mask);

    if ( mask & AFMT_MPEG )
    {
        /* ���豸֧��MPEG������ʽ ... */
    }

	int format;
    format = AFMT_S16_LE;

    if ( ioctl( audio_fd, SNDCTL_DSP_SETFMT, &format ) == -1 )
    {
        /* fatal error */
        perror( "SNDCTL_DSP_SETFMT" );
        exit( 1 );
    }

    if ( format != AFMT_S16_LE )
    {
        /* ���豸��֧��ѡ��Ĳ�����ʽ. */
    }

    int len;

    if ( ( len = read( audio_fd, audio_buffer, count ) ) == -1 )
    {
        perror( "audio read" );
        exit( 1 );
    }
	/*
    countΪ¼�����ݵ��ֽڸ���������Ϊ2��ָ������
		�����ܳ���audio_buffer�� ��С��
		�Ӷ��ֽڵĸ������Ծ�ȷ�Ĳ���ʱ�䣬
		����8kHZ 16 - bit stereo������Ϊ8000 * 2 * 2 = 32000bytes / second��
		����֪����ʱֹͣ¼����Ψһ������

            �����ò�����ʽ֮ǰ�������Ȳ����豸�ܹ�֧����Щ������ʽ���������£�


    ���ò�����ʽ


    ����ͨ����Ŀ
    */
    int channels = 2;

    /* 1=mono, 2=stereo */
    if ( ioctl( audio_fd, SNDCTL_DSP_CHANNELS, &channels ) == -1 )
    {
        /* Fatal error */
        perror( "SNDCTL_DSP_CHANNELS" );
        exit( 1 );
    }

    if ( channels != 2 )
    {
        /* ���豸��֧��������ģʽ ... */
    }

    //���ò�������
    int speed = 11025;

    if ( ioctl( audio_fd, SNDCTL_DSP_SPEED, &speed ) == -1 )
    {
        /* Fatal error */
        perror( "SNDCTL_DSP_SPEED" );
        exit( Error code );
    }

    if ( /* ���ص����ʣ���Ӳ��֧�ֵ����ʣ�����Ҫ�����ʲ��ܴ�... */ )
    {
        /* ���豸��֧����Ҫ������... */
    }

    //��Ƶ�豸ͨ����Ƶ�ķ���������Ҫ�Ĳ���ʱ�ӣ�
    //��˲����ܲ������е�Ƶ�ʡ����������������ӽ�Ҫ���Ƶ������
    //�û�����Ҫ��鷵�ص�����ֵ���������С�����Ժ��ԣ�������̫��
#endif
