/*
* Default Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
* AMX Includes
*/
#include "./SDK/amx/amx.h"
#include "./SDK/plugincommon.h"

#include "./Bitmap/EasyBMP.h"

extern void * pAMXFunctions;

using namespace std;  

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	cout << "    EasyBMP (c) 2010 by Gamer_Z";
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	cout << "    EasyBMP (c) 2010 by Gamer_Z";
}

int posx;
int posy;
char *tmp;
char *tmp2;

static cell AMX_NATIVE_CALL n_GetImageRAtPos( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	Image.ReadFromFile(tmp);
	posx = params[2];
	posy = params[3];
	return Image(posx,posy)->Red;
}

static cell AMX_NATIVE_CALL n_GetImageGAtPos( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	Image.ReadFromFile(tmp);
	posx = params[2];
	posy = params[3];
	return Image(posx,posy)->Green;
}

static cell AMX_NATIVE_CALL n_GetImageBAtPos( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	Image.ReadFromFile(tmp);
	posx = params[2];
	posy = params[3];
	return Image(posx,posy)->Blue;
}
/*
static cell AMX_NATIVE_CALL n_GetImageRGBAAtPos( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	Image.ReadFromFile(tmp);
	posx = params[2];
	posy = params[3];
	params[4] = Image(posx,posy)->Red;
	params[5] = Image(posx,posy)->Green;
	params[6] = Image(posx,posy)->Blue;
	//params[7] = Image(posx,posy)->Alpha;
	return 1;
}
*/
static cell AMX_NATIVE_CALL n_GetImageWidth( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	Image.ReadFromFile(tmp);
	return Image.TellWidth();
}

static cell AMX_NATIVE_CALL n_GetImageHeight( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	Image.ReadFromFile(tmp);
	return Image.TellHeight();
}

static cell AMX_NATIVE_CALL n_SetPixelRGBA( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	BMP Image;
	posx = params[2];
	posy = params[3];
	Image.ReadFromFile(tmp);
	RGBApixel value;
	
	value.Red = (ebmpBYTE)params[4];
	value.Green = (ebmpBYTE)params[5];
	value.Blue = (ebmpBYTE)params[6];
	value.Alpha = (ebmpBYTE)params[7];
	
	Image.SetBitDepth(24);
	Image.GetPixel(posx,posy);
	Image.SetPixel(posx,posy,value);
	return Image.WriteToFile(tmp);
}

static cell AMX_NATIVE_CALL n_SetImageSize( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp);
	posx = params[2];
	posy = params[3];
	BMP Image;
	Image.ReadFromFile(tmp);
	Image.CreateStandardColorTable();
	Image.SetSize(posx,posy);
	return Image.WriteToFile(tmp);
}

BMP GlobalImage;

static cell AMX_NATIVE_CALL n_FGetImageRAtPos( AMX* amx, cell* params ){
	posx = params[1];
	posy = params[2];
	return GlobalImage(posx,posy)->Red;
}

static cell AMX_NATIVE_CALL n_FGetImageGAtPos( AMX* amx, cell* params ){
	posx = params[1];
	posy = params[2];
	return GlobalImage(posx,posy)->Green;
}

static cell AMX_NATIVE_CALL n_FGetImageBAtPos( AMX* amx, cell* params ){
	posx = params[1];
	posy = params[2];
	return GlobalImage(posx,posy)->Blue;
}
/*
static cell AMX_NATIVE_CALL n_FGetImageRGBAAtPos( AMX* amx, cell* params ){
	posx = params[1];
	posy = params[2];
	params[3] = GlobalImage(posx,posy)->Red;
	params[4] = GlobalImage(posx,posy)->Green;
	params[5] = GlobalImage(posx,posy)->Blue;
	//params[6] = GlobalImage(posx,posy)->Alpha;
	return 1;
}
*/
static cell AMX_NATIVE_CALL n_FGetImageWidth( AMX* amx, cell* params ){
	return GlobalImage.TellWidth();
}

static cell AMX_NATIVE_CALL n_FGetImageHeight( AMX* amx, cell* params ){
	return GlobalImage.TellHeight();
}

static cell AMX_NATIVE_CALL n_FSetPixelRGBA( AMX* amx, cell* params ){
	posx = params[1];
	posy = params[2];
	RGBApixel value;
	
	value.Red = (ebmpBYTE)params[4];
	value.Green = (ebmpBYTE)params[5];
	value.Blue = (ebmpBYTE)params[6];
	value.Alpha = (ebmpBYTE)params[7];
	
	GlobalImage.SetBitDepth(24);
	GlobalImage.GetPixel(posx,posy);
	GlobalImage.SetPixel(posx,posy,value);
	return 1;
}

static cell AMX_NATIVE_CALL n_FSetImageSize( AMX* amx, cell* params ){
	posx = params[1];
	posy = params[2];
	GlobalImage.CreateStandardColorTable();
	GlobalImage.SetSize(posx,posy);
	return 1;
}

static cell AMX_NATIVE_CALL n_FOpenImage( AMX* amx, cell* params ){
	amx_StrParam(amx,params[1],tmp2);
	return GlobalImage.ReadFromFile(tmp2);
}

static cell AMX_NATIVE_CALL n_FSaveImage( AMX* amx, cell* params ){
	return GlobalImage.WriteToFile(tmp2);
}

AMX_NATIVE_INFO easybmpAMXNatives[ ] =
{
	{"GetImageRAtPos", n_GetImageRAtPos},
	{"GetImageGAtPos", n_GetImageGAtPos},
	{"GetImageBAtPos", n_GetImageBAtPos},
	{"GetImageWidth", n_GetImageWidth},
	{"GetImageHeight", n_GetImageHeight},
	{"SetPixelRGBAAtPos", n_SetPixelRGBA},
	{"SetImageSize", n_SetImageSize},
	//{"GetImageRGBAAtPos", n_GetImageRGBAAtPos},
	{"FGetImageRAtPos", n_FGetImageRAtPos},
	{"FGetImageGAtPos", n_FGetImageGAtPos},
	{"FGetImageBAtPos", n_FGetImageBAtPos},
	{"FGetImageWidth", n_FGetImageWidth},
	{"FGetImageHeight", n_FGetImageHeight},
	{"FSetPixelRGBAAtPos", n_FSetPixelRGBA},
	{"FSetImageSize", n_FSetImageSize},
	//{"FGetImageRGBAAtPos", n_FGetImageRGBAAtPos},
	{"FImageOpen", n_FOpenImage},
	{"FImageSave", n_FSaveImage},
	{0,                0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	return amx_Register( amx, easybmpAMXNatives, -1 );
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}
