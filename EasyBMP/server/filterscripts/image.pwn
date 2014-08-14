//The script can only handle 1 image at a time, and show only 1 image.

#include <a_samp>

#if defined IMAGE_MAKER_INCLUDED
	#endinput
#else
	#define IMAGE_MAKER_INCLUDED
	#pragma library IMAGE_MAKER
#endif

native GetImageRAtPos(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY);
native GetImageGAtPos(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY);
native GetImageBAtPos(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY);
native GetImageWidth(const BMP24BIT_FileName[]);
native GetImageHeight(const BMP24BIT_FileName[]);
native SetPixelRGBAAtPos(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY,red,green,blue,alpha=0);
native SetImageSize(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY);
//native GetImageRGBAtPos(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY,&DecimalRed,&DecimalGreen,&DecimalBlue);//sorry I don't know how to set adresses from a plugin...

//fast image processing
native FImageOpen(const BMP24BIT_FileName[]);
native FImageSave();// only save the image when you have used FSet*
native FGetImageRAtPos(BMP_PosX,BMP_PosY);
native FGetImageGAtPos(BMP_PosX,BMP_PosY);
native FGetImageBAtPos(BMP_PosX,BMP_PosY);
native FGetImageWidth();
native FGetImageHeight();
native FSetPixelRGBAAtPos(BMP_PosX,BMP_PosY,red,green,blue,alpha=0);
native FSetImageSize(BMP_PosX,BMP_PosY);
//native FGetImageRGBAtPos(const BMP_PosX,BMP_PosY,&DecimalRed,&DecimalGreen,&DecimalBlue);//sorry I don't know how to set adresses from a plugin...

stock FGetImageSize(&MaxX,&MaxY)
{
    MaxX =  FGetImageWidth();
	MaxY =  FGetImageHeight();
	return 1;
}

stock ImageClose()
	return FImageSave();
	
stock ImageOpen(const filename[])
	return FImageOpen(filename);

enum pixelenum {
	R,
	G,
	B,
	T
}

//1024 = 32x32

new
	pixel[32][32][pixelenum],
	Text:Tpixel[32][32],
	Float:OFFSETX = 320.0,
	Float:OFFSETY = 240.0,
	ImageMaxX = 32,
	ImageMaxY = 32;

public OnFilterScriptInit()
{
    LoadImageFromFile("scriptfiles/32.bmp",0,0);
    print("load");
    return 1;
}

public OnPlayerConnect(playerid)
{
    ShowImageForPlayer(playerid);
    print("load");
    return 1;
}

//native ETN(val1,val2,val3,val4);
stock ETN(val1,val2,val3,val4){

	new
		v1,
		v2,
		v3,
		v4,
		t;

	v1 = val1*16777216;
	v2 = val2*65536;
	v3 = val3*256;
	v4 = val4;

	t = v1+v2+v3+v4;

	return t;
}

//native SetPixelColor(i,a,Rg,Gg,Bg,Tg=255);
stock SetPixelColor(i,a,Rg,Gg,Bg,Tg=255){
	pixel[i][a][R] = Rg;
	pixel[i][a][G] = Gg;
	pixel[i][a][B] = Bg;
	pixel[i][a][T] = Tg;
    TextDrawColor(Tpixel[i][a],RGBAToColor(pixel[i][a][R],pixel[i][a][G],pixel[i][a][B],pixel[i][a][T]));
    //TextDrawHideForAll(Tpixel[i][a]);
    //TextDrawShowForAll(Tpixel[i][a]);
    return 1;
}

//native SetPixelColorH(i,a,h);
stock SetPixelColorH(i,a,h){
    TextDrawColor(Tpixel[i][a],h);
    //TextDrawHideForAll(Tpixel[i][a]);
    //TextDrawShowForAll(Tpixel[i][a]);
    return 1;
}

//native GetPixelColor(i,a,&Rg,&Gg,&Bg,&Tg);
stock GetPixelColor(i,a,&Rg,&Gg,&Bg,&Tg){
	Rg = pixel[i][a][R];
	Gg = pixel[i][a][G];
	Bg = pixel[i][a][B];
	Tg = pixel[i][a][T];
	return 1;
}

//native GetImageOffset(&Float:Xbit,&Float:Ybit);
stock GetImageOffset(&Float:Xbit,&Float:Ybit){
	Xbit = OFFSETX,
	Ybit = OFFSETY;
	return 1;
}

//native SetImageDrawStyle(style);
stock SetImageDrawStyle(style){
	if(style == 0){
		for(new i; i < ImageMaxX; i++){
		    for(new a; a < ImageMaxY; a++){
		        TextDrawHideForPlayer(playerid,Tpixel[i][a]);
		        TextDrawSetString(Tpixel[i][a],".");
		    	TextDrawShowForPlayer(playerid,Tpixel[i][a]);
			}
		}
	}else
	if(style == 1){
		for(new i; i < ImageMaxX; i++){
		    for(new a; a < ImageMaxY; a++){
		        TextDrawHideForPlayer(playerid,Tpixel[i][a]);
		        TextDrawSetString(Tpixel[i][a],"'");
		    	TextDrawShowForPlayer(playerid,Tpixel[i][a]);
			}
		}
	}else{
		for(new i; i < ImageMaxX; i++){
		    for(new a; a < ImageMaxY; a++){
		        TextDrawHideForPlayer(playerid,Tpixel[i][a]);
		        TextDrawSetString(Tpixel[i][a],".");
		    	TextDrawShowForPlayer(playerid,Tpixel[i][a]);
			}
		}
	}
	return 1;
}

//native SetImageOffset(Float:Xbit,Float:Ybit,refresh=0);
stock SetImageOffset(Float:Xbit,Float:Ybit,refresh=0){//You need to manually show the image for each player after using this OR if refresh is on the image will be shown to all players

	OFFSETX = Xbit,
	OFFSETY = Ybit;

	for(new i; i < ImageMaxX; i++){
	    for(new a; a < ImageMaxY; a++){
	        TextDrawHideForAll(Tpixel[i][a]);
			TextDrawDestroy(Tpixel[i][a]);
	    	Tpixel[i][a] = TextDrawCreate(OFFSETX+i*4,OFFSETY+a*4,".");
	    	//TextDrawTextSize(Tpixel[i][a],200,200);
	    	TextDrawTextSize(Tpixel[i][a],2,2);
		    TextDrawLetterSize(Tpixel[i][a],2,2);
	    	//TextDrawColor(Tpixel[i][a],0);
	    	SetPixelColor(i,a,pixel[i][a][R],pixel[i][a][G],pixel[i][a][B]);
	    	TextDrawUseBox(Tpixel[i][a],0);
	    	TextDrawBoxColor(Tpixel[i][a],0xFFFFFF00);
	    	TextDrawSetShadow(Tpixel[i][a],0);
	    	TextDrawSetOutline(Tpixel[i][a],0);
	    	TextDrawBackgroundColor(Tpixel[i][a],0xFFFFFF00);
	    	if(refresh){
	    	    TextDrawHideForAll(Tpixel[i][a]);
	    	    TextDrawShowForAll(Tpixel[i][a]);
	    	}
		}
	}

	return 1;
}

//native HideImageForAll();
stock HideImageForAll(){
	for(new i; i < ImageMaxX; i++){
	    for(new a; a < ImageMaxY; a++){
	        TextDrawHideForAll(Tpixel[i][a]);
	    }
	}
	return 1;
}

//native ShowImageForAll();
stock ShowImageForAll(){
	for(new i; i < ImageMaxX; i++){
	    for(new a; a < ImageMaxY; a++){
	        TextDrawShowForAll(Tpixel[i][a]);
	    }
	}
	return 1;
}

//native HideImageForPlayer(playerid);
stock HideImageForPlayer(playerid){
	for(new i; i < ImageMaxX; i++){
	    for(new a; a < ImageMaxY; a++){
	        TextDrawHideForPlayer(playerid,Tpixel[i][a]);
	    }
	}
	return 1;
}

//native ShowImageForPlayer(playerid);
stock ShowImageForPlayer(playerid){
	for(new i; i < ImageMaxX; i++){
	    for(new a; a < ImageMaxY; a++){
	        TextDrawShowForPlayer(playerid,Tpixel[i][a]);
	    }
	}
	return 1;
}

//native LoadImageFromFile(const filename[], draw=0, showforall=0, showforplayer = -1);
stock LoadImageFromFile(const filename[], showforall=0, showforplayer = -1){

	new
	    MaxX,
	    MaxY;

	#define multiplier 2
	for(new i; i < ImageMaxX; i++){

	    for(new a; a < ImageMaxY; a++){

	    	Tpixel[i][a] = TextDrawCreate(OFFSETX+i*multiplier,OFFSETY+a*multiplier,".");
	    	TextDrawTextSize(Tpixel[i][a],100*multiplier,100*multiplier);
	    	TextDrawColor(Tpixel[i][a],0);
	    	TextDrawUseBox(Tpixel[i][a],0);
	    	TextDrawBoxColor(Tpixel[i][a],0xFFFFFF00);
	    	TextDrawSetShadow(Tpixel[i][a],0);
	    	TextDrawSetOutline(Tpixel[i][a],0);
	    	TextDrawBackgroundColor(Tpixel[i][a],0xFFFFFF00);

		}
	}
	
	ImageOpen(filename);
	FGetImageSize(MaxX,MaxY);
	if((MaxX != -1 && MaxY != -1) || (MaxX > 32 || MaxY > 32)){
		for(new i; i < MaxX; i++){
		    for(new a; a < MaxY; a++){
		        new Tmp[pixelenum];
				FGetImageRGBAtPos(i,a,Tmp[R],Tmp[G],Tmp[B]);
				SetPixelColor(i,a,Tmp[R],Tmp[G],Tmp[B]);
				if(showforall){
				    TextDrawHideForAll(Tpixel[i][a]);
				    TextDrawShowForAll(Tpixel[i][a]);
				}
				if(showforplayer != -1){
			        TextDrawHideForPlayer(showforplayer,Tpixel[i][a]);
			        TextDrawShowForPlayer(showforplayer,Tpixel[i][a]);
				}
		    }
		}
	}else{
	    print("Wrong image size!");
	    return 0;
	}
	
	ImageMaxX = MaxX;
	ImageMaxY = MaxY;
	
	return 1;
}

stock SetPixelRGBAtPosEx(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY,val,{ Color_Index, _ }: color)
{
	new
	     red
	    ,green
	    ,blue
	    ;

	switch(color)
	{
	    case R:
	    {
			red = val;
			green = GetImageGAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
			blue = GetImageBAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
	    }
	    case G:
	    {
			red = GetImageRAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
			green = val;
			blue = GetImageBAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
	    }
	    case B:
	    {
			red = GetImageRAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
			green = GetImageGAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
			blue = val;
	    }
	    default:
	    {
	        return 0;
	    }
	}
	SetPixelRGBAAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY,red,green,blue);
	return 1;
}

stock GetImageRGBAtPos(const BMP24BIT_FileName[],BMP_PosX,BMP_PosY,&DecimalRed,&DecimalGreen,&DecimalBlue)
{
	DecimalRed = GetImageRAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
	DecimalGreen = GetImageGAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
	DecimalBlue = GetImageBAtPos(BMP24BIT_FileName,BMP_PosX,BMP_PosY);
	return 1;
}

stock FGetImageRGBAtPos(BMP_PosX,BMP_PosY,&DecimalRed,&DecimalGreen,&DecimalBlue)
{
	DecimalRed = FGetImageRAtPos(BMP_PosX,BMP_PosY);
	DecimalGreen = FGetImageGAtPos(BMP_PosX,BMP_PosY);
	DecimalBlue = FGetImageBAtPos(BMP_PosX,BMP_PosY);
	return 1;
}
stock PutTextIntoImage(const BMP24BIT_FileName[],string[],mode = 0)
{
	new lenght = strlen(string);
	if(lenght >= MAX_BMP_STRING-1)
	{
	    return 0;
	}
	switch(mode)
	{
	    case 0:
	    {
			for(new i = 0; i < lenght; i++)
			{
			    //printf("string[%i] = %c | ASCIItoINT returned %d",i,string[i],ASCIItoINT(string[i]));
			    SetPixelRGBAtPosEx(BMP24BIT_FileName,i,0,ASCIItoINT(string[i]),0);
			}
			SetPixelRGBAtPosEx(BMP24BIT_FileName,lenght+1,0,255,0);
		}
	    case 1:
	    {
			for(new i = 0; i < lenght; i++)
			{
			    //printf("string[%i] = %c | ASCIItoINT returned %d",i,string[i],ASCIItoINT(string[i]));
			    SetPixelRGBAtPosEx(BMP24BIT_FileName,i,0,ASCIItoINT(string[i]),1);
			}
			SetPixelRGBAtPosEx(BMP24BIT_FileName,lenght+1,0,255,1);
		}
	    case 2:
	    {
			for(new i = 0; i < lenght; i++)
			{
			    //printf("string[%i] = %c | ASCIItoINT returned %d",i,string[i],ASCIItoINT(string[i]));
			    SetPixelRGBAtPosEx(BMP24BIT_FileName,i,0,ASCIItoINT(string[i]),2);
			}
			SetPixelRGBAtPosEx(BMP24BIT_FileName,lenght+1,0,255,2);
		}
		default: return 0;
	}
	return 1;
}

stock ReadTextFromImage(const BMP24BIT_FileName[],mode = 0)
{
	new string[256];
	switch(mode)
	{
	    case 0:
	    {
			for(new i = 0; i < MAX_BMP_STRING; i++)
			{
			    string[i] = GetImageRAtPos(BMP24BIT_FileName,i,0);
			    if(string[i] == 255)
			    {
			        string[i] = '\0';
			        break;
			    }
			}
		}
		case 1:
		{
			for(new i = 0; i < MAX_BMP_STRING; i++)
			{
			    string[i] = GetImageGAtPos(BMP24BIT_FileName,i,0);
			    if(string[i] == 255)
			    {
			        string[i] = '\0';
			        break;
			    }
			}
		}
		case 2:
		{
			for(new i = 0; i < MAX_BMP_STRING; i++)
			{
			    string[i] = GetImageBAtPos(BMP24BIT_FileName,i,0);
			    if(string[i] == 255)
			    {
			        string[i] = '\0';
			        break;
			    }
			}
		}
		default: string[0] = '\0';
	}
	return string;
}

stock ASCIItoINT(const char_[])// only 1 character at a time!
{
	new charx[4];
	format(charx,4,"%d",char_);
	return strval(charx);
}

stock INTtoASCII(int_)
{
	if(int_ > 255 || int_ < 0)return 0;
	new str[2];
	format(str,2,"%s",int_);
	return str;
}

stock HexToInt(string[]) {
  if (string[0]==0) return 0;
  new i;
  new cur=1;
  new res=0;
  for (i=strlen(string);i>0;i--) {
    if (string[i-1]<58) res=res+cur*(string[i-1]-48); else res=res+cur*(string[i-1]-65+10);
    cur=cur*16;
  }
  return res;
}

stock IntToHex(number)
{
	new m=1;
	new depth=0;
	while (number>=m) {
		m = m*16;
		depth++;
	}
	depth--;
	new str[256];
	for (new i = depth; i >= 0; i--)
	{
		str[i] = ( number & 0x0F) + 0x30; // + (tmp > 9 ? 0x07 : 0x00)
		str[i] += (str[i] > '9') ? 0x07 : 0x00;
		number >>= 4;
	}
	if(strlen(str) == 0)strins(str,"00",0);
	else
	if(strlen(str) == 1)strins(str,"0",0);
	str[8] = '\0';
	return str;
}

stock RGBAToColor(red,green,blue,alpha = 255)
{
	new StrHex[16];
	format(StrHex,16,"%s%s%s%s",IntToHex(red),IntToHex(green),IntToHex(blue),IntToHex(alpha));
	return HexToInt(StrHex);
}

stock RGBAToHex(red,green,blue,alpha = 255)
{
	new StrHex[16];
	format(StrHex,16,"%s%s%s%s",IntToHex(red),IntToHex(green),IntToHex(blue),IntToHex(alpha));
	return StrHex;
}

stock RGBToHex(red,green,blue)// can be used in chat etc.. and sendclientmessage
{
	new StrHex[16];
	format(StrHex,16,"%s%s%s",IntToHex(red),IntToHex(green),IntToHex(blue));
	return StrHex;
}

Make2DImageIn3DSpace(const BMP24BIT_FileName[],Float:bmpworldX,Float:bmpworldY,Float:bmpworldZ)
{
    FImageOpen(BMP24BIT_FileName);
	new
		 X = FGetImageWidth()
		,Y = FGetImageHeight()
		,temp[ColorIndex]
		,SuperLargeString[16384] // 16384 cells = 65536 bytes (in memory), not so bad huh?
		;

	for(new b = 0; b < Y; b++)
	{
	    format(SuperLargeString,16384,"");
		for(new a = 0; a < X; a++)
		{
		    FGetImageRGBAtPos(a,b,temp[R],temp[G],temp[B]);
			strins(SuperLargeString,"{",strlen(SuperLargeString));
			strins(SuperLargeString,RGBToHex(temp[R],temp[G],temp[B]),strlen(SuperLargeString));
			strins(SuperLargeString,"}.",strlen(SuperLargeString));// after } is the character that represents an pixel
			if(a == (X-1))
			{
			    Create3DTextLabel(SuperLargeString,0xFFFFFFFF,bmpworldX,bmpworldY,(bmpworldZ-(b/10)),300.0,0);//(b/10) - distance heights from each 3d text, if 10 is larger the distance will be smaller
			}
		}
	}

	return 1;
}

Make3DImageIn3DSpace(const BMP24BIT_FileNamePrefix[],Float:bmpworldcenterX,Float:bmpworldcenterY,Float:bmpworldcenterZ)
{
	#pragma unused Make3DImageIn3DSpace
	#pragma unused Make2DImageIn3DSpace
	//feature is coming..
	return 1;
}
