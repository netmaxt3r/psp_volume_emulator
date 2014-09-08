/*
volumecontrol


hiroi01����iniLibrary���g�킹�Ă��炢�܂����B
���肪�Ƃ��������܂��B
*/

#include <pspkernel.h>
#include <pspctrl.h>
#include <systemctrl.h>//pad��͂Ɏg��
#include <pspimpose_driver.h>
#include <string.h>

#include "conf.h"

/*-----------------------------------------------------------------*/

PSP_MODULE_INFO("myVol", 0x1000, 0, 0);

#define INI_PATH "/volcon.ini"

/*------------------------------------------------------------------*/
// �v���g�^�C�v�錾
int main_thread(SceSize args, void *argp);
int module_start(SceSize args, void *argp);
int module_stop(SceSize args, void *argp);

/*------------------------------------------------------------------*/
// �L�[�p�ϐ� ini�̍��ڕ��K�v
#define CONF_NUM 7
INI_Key conf[CONF_NUM];

// �ݒ�t�@�C���p�ϐ�
u32 VolMaxButtons = 0;
u32 VolMinButtons = 0;
int MaxTime = 0;
int MinTime = 0;

u32 SetButtons;
int SetLevel;
int SetTime;
/*------------------------------------------------------------------*/


int Count_Buttons(u32 buttons, int count) {
	SceCtrlData pad;
	clock_t time;

	// �w�肷��{�^�����Z�b�g
	pad.Buttons = buttons;

	// ���݂̎��� + �w�肵������
	count = 1000000 * count;		//count�b
	time = sceKernelLibcClock() + count;

	// �{�^���������܂Ń��[�v
	while((pad.Buttons & buttons) == buttons)
	{
		// �f�B���C
		sceKernelDelayThread(50000);

		// �p�b�h�����擾����
		sceCtrlPeekBufferPositive(&pad, 1);
		// ���݂̎��Ԃ��w�肵�����Ԃ��߂�����
		if(sceKernelLibcClock() > time)
			return 1;
	}

	return 0;
}

/*------------------------------------------------------------------*/

//���C��
int main_thread(SceSize args, void *argp)
{

	// wait / �s�v�Ȃ��̂����邩��
	while( 1 )
	{
		if(
			sceKernelFindModuleByName("sceKernelLibrary")
		)
		{
			break;
		}
		sceKernelDelayThread(1000);
	}

	if(SetLevel < 0)SetLevel=0;
	if(SetLevel > 30)SetLevel=30;
	

	SceCtrlData pad;
	while (1)
	{
		
		sceKernelDelayThread(50000);
		sceCtrlPeekBufferPositive(&pad, 1);
		
		if((pad.Buttons & (PSP_CTRL_VOLDOWN&PSP_CTRL_RTRIGGER))){
			int cVol =0;
			cVol = sceImposeGetParam(PSP_IMPOSE_MAIN_VOLUME);
			if(cVol<30){
				cVol++;
				sceImposeSetParam(PSP_IMPOSE_MAIN_VOLUME,cVol);
			}


		}
	}

	return 0;
}


int module_start(SceSize args, void *argp)
{



	int thid = sceKernelCreateThread("volumecontrol", main_thread, 32, 0x800, 0, NULL);
	if(thid >= 0)sceKernelStartThread(thid, args, argp);

	return 0;
}


int module_stop(SceSize args, void *argp)
{
	return 0;
}

