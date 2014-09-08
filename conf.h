//bases are mp3play and bright.prx by plum / and iso tool by takka
//thank you plum , takka !

//made by hiroi01


#ifndef __CONF_H__
#define	__CONF_H__

#include <stdbool.h>



//���(�t���O) for INI_Key foo.type
enum
{
	INI_TYPE_DYNAMIC = 1,	//
	INI_TYPE_STATIC = 2,	//
	INI_TYPE_HEX = 4,	//
	INI_TYPE_BUTTON = 8,	//
	INI_TYPE_STRING = 16,	//
	INI_TYPE_LIST = 32,
	INI_TYPE_BOOL = 64,
	INI_TYPE_DEC = 128,
};

typedef struct
{
	char key[64];//����
	
	//�L���X�g����̂��ʓ|�Ȃ̂ł��낢��Ȍ^�̃|�C���^�[�𑵂��Ă���
	union{
		int *i;
		char *s;
		u32 *u;
		bool *b;
	}value;//�E��
	
	union{
		int i;
		char *s;
		u32 u;
		bool b;
	}defaultValue;//�f�t�H���g�l
	
	u32 type;//���(�t���O)
	
	//�g��(��ނɂ���Ďg������g��Ȃ�������)
	void *ex;
//	void **exx;
	

	
	int keyNum;//key[0]�ł����g���Ȃ����烁�����[�̖��ʌ���?
	
} INI_Key;




void INI_Init_Key(INI_Key *key);
int INI_Read_Conf(const char *path, INI_Key *key);
int INI_Write_Conf(const char *ms_path, INI_Key *key, const char *lineFeedCode);
void INI_Set_Default(INI_Key *key);

void INI_Add_Hex(INI_Key *key, char *keyName,  u32 *value, u32 defaultValue, int *ex);
void INI_Add_Button(INI_Key *key, char *keyName,  u32 *value, u32 defaultValue);
void INI_Add_String(INI_Key *key, char *keyName, char *value, char *defaultValue);
void INI_Add_List(INI_Key *key, char *keyName, int *value, int defaultValue, const char *list[] );
void INI_Add_Bool(INI_Key *key, char *keyName, bool *value, bool defaultValue);

//�\�i���̐����Ȑ�����ǂݍ���
//@param : key
//         INI_Key�\����
//@param : keyName
//         ����
//@param : value
//         �ǂݍ��񂾒l���i�[���邽�߂̕ϐ��i�̃A�h���X�j int�^
//@param : defaultValue
//         �������ǂݍ��߂Ȃ������ꍇ�ȂǂɃZ�b�g�����f�t�H���g�l
//@param : ex
//         �ő�l���w��
//         �ǂݍ��񂾒l�������Ŏw�肵���l���傫���ꍇ��defaultValue�̒l���Z�b�g�����
//         �s�v�Ȃ� NULL ���킽���ĉ������A�����ɂȂ�܂�
//
//
//(�d�l�ύX�\��)
void INI_Add_Dec(INI_Key *key, char *keyName, int *value, int defaultValue, int *ex);

#endif

