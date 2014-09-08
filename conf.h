//bases are mp3play and bright.prx by plum / and iso tool by takka
//thank you plum , takka !

//made by hiroi01


#ifndef __CONF_H__
#define	__CONF_H__

#include <stdbool.h>



//種類(フラグ) for INI_Key foo.type
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
	char key[64];//左辺
	
	//キャストするのが面倒なのでいろいろな型のポインターを揃えておく
	union{
		int *i;
		char *s;
		u32 *u;
		bool *b;
	}value;//右辺
	
	union{
		int i;
		char *s;
		u32 u;
		bool b;
	}defaultValue;//デフォルト値
	
	u32 type;//種類(フラグ)
	
	//拡張(種類によって使ったり使わなかったり)
	void *ex;
//	void **exx;
	

	
	int keyNum;//key[0]でしか使われないからメモリーの無駄遣い?
	
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

//十進数の整数な数字を読み込む
//@param : key
//         INI_Key構造体
//@param : keyName
//         左辺
//@param : value
//         読み込んだ値を格納するための変数（のアドレス） int型
//@param : defaultValue
//         正しく読み込めなかった場合などにセットされるデフォルト値
//@param : ex
//         最大値を指定
//         読み込んだ値がここで指定した値より大きい場合はdefaultValueの値がセットされる
//         不要なら NULL をわたして下さい、無効になります
//
//
//(仕様変更予定)
void INI_Add_Dec(INI_Key *key, char *keyName, int *value, int defaultValue, int *ex);

#endif

