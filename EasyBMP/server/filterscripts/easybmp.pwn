#include <a_samp>

#pragma dynamic 26000
#define MAX_BMP_STRING 256
#define MaxWidth  8
#define MaxHeight 8

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

enum ColorIndex
{
	 R
	,G
	,B
}

public OnFilterScriptInit()
{
	print("1");
	new FileName[64];
	format(FileName,64,"scriptfiles/image.bmp");

	new Color[ColorIndex][MaxWidth][MaxHeight];
	//printf("FileName: %s Width: %d Height: %d",FileName,GetImageWidth(FileName),GetImageHeight(FileName));
	for(new x = 0; x < GetImageWidth(FileName); x++)
	{
	    for(new y = 0; y < GetImageHeight(FileName); y++)
	    {
	        GetImageRGBAtPos(FileName,x,y,Color[R][x][y],Color[G][x][y],Color[B][x][y]);
	        //printf("Color from image \"%s\" at X: %d Y: %d is Red: %d Green: %d Blue: %d Alpha: 255 Hex: %s",FileName,x,y,Color[R][x][y],Color[G][x][y],Color[B][x][y],RGBAToHex(Color[R][x][y],Color[G][x][y],Color[B][x][y]));
	    }
	}
	SetImageSize("scriptfiles/my.bmp",MAX_BMP_STRING,1);
	PutTextIntoImage("scriptfiles/my.bmp","This is the first text layer, it is in the RED code.",0);
	PutTextIntoImage("scriptfiles/my.bmp","This is the second text layer, it is in the GREEN code.",1);
	PutTextIntoImage("scriptfiles/my.bmp","This is the third text layer, it is in the BLUE code.",2);

	printf("%s",ReadTextFromImage("scriptfiles/my.bmp",0));
	printf("%s",ReadTextFromImage("scriptfiles/my.bmp",1));
	printf("%s",ReadTextFromImage("scriptfiles/my.bmp",2));
	
	FImageOpen("scriptfiles/picture.bmp");
	
	printf("%d %d %d",FGetImageRAtPos(25,52),FGetImageGAtPos(25,52),FGetImageBAtPos(25,52));

	return 1;
}

public OnPlayerCommandText(playerid,cmdtext[])
{
	if(!strcmp(cmdtext,"/makeimage",true))
	{
	    new Float:Pos[3];
	    GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	    Pos[2] += 30.0;
	    Make2DImageIn3DSpace("scriptfiles/picture.bmp",Pos[0],Pos[1],Pos[2]);
	    return 1;
	}
	return 0;
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
	new string[MAX_BMP_STRING];
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
	//feature is coming..
	return 1;
}
