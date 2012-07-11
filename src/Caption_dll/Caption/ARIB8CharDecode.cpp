#include <string>
#include <map>
// mark10als
#include <Windows.h>
//#include <Shlwapi.h>
//#include <wincrypt.h>
//#pragma comment (lib, "crypt32.lib")
#include "CalcMD5.h"
#include "CommRoutine.h"
#include "ColorDef.h"
// mark10als
#include "ARIB8CharDecode.h"

static CLUT_DAT DefClut[]={
	{  0,  0,  0,255}, //0
	{255,  0,  0,255},
	{  0,255,  0,255},
	{255,255,  0,255},
	{  0,  0,255,255},
	{255,  0,255,255}, //5
	{  0,255,255,255},
	{255,255,255,255},
	{  0,  0,  0,  0},
	{170,  0,  0,255},
	{  0,170,  0,255}, //10
	{170,170,  0,255},
	{  0,  0,170,255},
	{170,  0,170,255},
	{  0,170,170,255},
	{170,170,170,255}, //15
	{  0,  0, 85,255},
	{  0, 85,  0,255},
	{  0, 85, 85,255},
	{  0, 85,170,255},
	{  0, 85,255,255}, //20
	{  0,170, 85,255},
	{  0,170,255,255},
	{  0,255, 85,255},
	{  0,255,170,255},
	{ 85,  0,  0,255}, //25
	{ 85,  0, 85,255},
	{ 85,  0,170,255},
	{ 85,  0,255,255},
	{ 85, 85,  0,255},
	{ 85, 85, 85,255}, //30
	{ 85, 85,170,255},
	{ 85, 85,255,255},
	{ 85,170,  0,255},
	{ 85,170, 85,255},
	{ 85,170,170,255}, //35
	{ 85,170,255,255},
	{ 85,255,  0,255},
	{ 85,255, 85,255},
	{ 85,255,170,255},
	{ 85,255,255,255}, //40
	{170,  0, 85,255},
	{170,  0,255,255},
	{170, 85,  0,255},
	{170, 85, 85,255},
	{170, 85,170,255}, //45
	{170, 85,255,255},
	{170,170, 85,255},
	{170,170,255,255},
	{170,255,  0,255},
	{170,255, 85,255}, //50
	{170,255,170,255},
	{170,255,255,255},
	{255,  0, 85,255},
	{255,  0,170,255},
	{255, 85,  0,255}, //55
	{255, 85, 85,255},
	{255, 85,170,255},
	{255, 85,255,255},
	{255,170,  0,255},
	{255,170, 85,255}, //60
	{255,170,170,255},
	{255,170,255,255},
	{255,255, 85,255},
	{255,255,170,255},
	{  0,  0,  0,128}, //65
	{255,  0,  0,128},
	{  0,255,  0,128},
	{255,255,  0,128},
	{  0,  0,255,128},
	{255,  0,255,128}, //70
	{  0,255,255,128},
	{255,255,255,128},
	{170,  0,  0,128},
	{  0,170,  0,128},
	{170,170,  0,128}, //75
	{  0,  0,170,128},
	{170,  0,170,128},
	{  0,170,170,128},
	{170,170,170,128},
	{  0,  0, 85,128}, //80
	{  0, 85,  0,128},
	{  0, 85, 85,128},
	{  0, 85,170,128},
	{  0, 85,255,128},
	{  0,170, 85,128}, //85
	{  0,170,255,128},
	{  0,255, 85,128},
	{  0,255,170,128},
	{ 85,  0,  0,128},
	{ 85,  0, 85,128}, //90
	{ 85,  0,170,128},
	{ 85,  0,255,128},
	{ 85, 85,  0,128},
	{ 85, 85, 85,128},
	{ 85, 85,170,128}, //95
	{ 85, 85,255,128},
	{ 85,170,  0,128},
	{ 85,170, 85,128},
	{ 85,170,170,128},
	{ 85,170,255,128}, //100
	{ 85,255,  0,128},
	{ 85,255, 85,128},
	{ 85,255,170,128},
	{ 85,255,255,128},
	{170,  0, 85,128}, //105
	{170,  0,255,128},
	{170, 85,  0,128},
	{170, 85, 85,128},
	{170, 85,170,128},
	{170, 85,255,128}, //110
	{170,170, 85,128},
	{170,170,255,128},
	{170,255,  0,128},
	{170,255, 85,128},
	{170,255,170,128}, //115
	{170,255,255,128},
	{255,  0, 85,128},
	{255,  0,170,128},
	{255, 85,  0,128},
	{255, 85, 85,128}, //120
	{255, 85,170,128},
	{255, 85,255,128},
	{255,170,  0,128},
	{255,170, 85,128},
	{255,170,170,128}, //125
	{255,170,255,128},
	{255,255, 85,128}
};

static char AsciiTable[][3]={
	"�I","�h","��","��","��","��","�f",
	"�i","�j","��","�{","�C","�|","�D","�^",
	"�O","�P","�Q","�R","�S","�T","�U","�V",
	"�W","�X","�F","�G","��","��","��","�H",
	"��","�`","�a","�b","�c","�d","�e","�f",
	"�g","�h","�i","�j","�k","�l","�m","�n",
	"�o","�p","�q","�r","�s","�t","�u","�v",
	"�w","�x","�y","�m","��","�n","�O","�Q",
	"�e","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","�o","�b","�p","�P"
};
static char HiraTable[][3]={
	"��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","�@","�@","�@","�T",
	"�U","�[","�B","�u","�v","�A","�E"
};
static char KanaTable[][3]={
	"�@","�A","�B","�C","�D","�E","�F",
	"�G","�H","�I","�J","�K","�L","�M","�N",
	"�O","�P","�Q","�R","�S","�T","�U","�V",
	"�W","�X","�Y","�Z","�[","�\","�]","�^",
	"�_","�`","�a","�b","�c","�d","�e","�f",
	"�g","�h","�i","�j","�k","�l","�m","�n",
	"�o","�p","�q","�r","�s","�t","�u","�v",
	"�w","�x","�y","�z","�{","�|","�}","�~",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","��",
	"��","��","��","��","��","��","��","�R",
	"�S","�[","�B","�u","�v","�A","�E"
};

// mark10als
// ���p�p�̃e�[�u��
static char HalfAsciiTable[][3]={
	"!","\"","#","$","%","&","'",
	"(",")","*","+",",","-",".","/",
	"0","1","2","3","4","5","6","7",
	"8","9",":",";","<","=",">","?",
	"@","A","B","C","D","E","F","G",
	"H","I","J","K","L","M","N","O",
	"P","Q","R","S","T","U","V","W",
	"X","Y","Z","[","\\","]","^","_",
	"'","a","b","c","d","e","f","g",
	"h","i","j","k","l","m","n","o",
	"p","q","r","s","t","u","v","w",
	"x","y","z","{","|","}","�P"
};
static char SpaceTable[][3]={
	"�@",
	" "
};
// ARIB�̒ǉ��L�� �� �ǉ������̃e�[�u����`�́uCaptionMain.cpp�v�Ɉڂ�

static BYTE DefaultMacro0[]={
	0x1B,0x24,0x39,0x1B,0x29,0x4A,0x1B,0x2A,0x30,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro1[]={
	0x1B,0x24,0x39,0x1B,0x29,0x31,0x1B,0x2A,0x30,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro2[]={
	0x1B,0x24,0x39,0x1B,0x29,0x20,0x40,0x1B,0x2A,0x30,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro3[]={
	0x1B,0x28,0x32,0x1B,0x29,0x34,0x1B,0x2A,0x35,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro4[]={
	0x1B,0x28,0x32,0x1B,0x29,0x33,0x1B,0x2A,0x35,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro5[]={
	0x1B,0x28,0x32,0x1B,0x29,0x20,0x40,0x1B,0x2A,0x35,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro6[]={
	0x1B,0x28,0x20,0x41,0x1B,0x29,0x20,0x42,0x1B,0x2A,0x20,0x43,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro7[]={
	0x1B,0x28,0x20,0x44,0x1B,0x29,0x20,0x45,0x1B,0x2A,0x20,0x46,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro8[]={
	0x1B,0x28,0x20,0x47,0x1B,0x29,0x20,0x48,0x1B,0x2A,0x20,0x49,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacro9[]={
	0x1B,0x28,0x20,0x4A,0x1B,0x29,0x20,0x4B,0x1B,0x2A,0x20,0x4C,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacroA[]={
	0x1B,0x28,0x20,0x4D,0x1B,0x29,0x20,0x4E,0x1B,0x2A,0x20,0x4F,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacroB[]={
	0x1B,0x24,0x39,0x1B,0x29,0x20,0x42,0x1B,0x2A,0x30,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacroC[]={
	0x1B,0x24,0x39,0x1B,0x29,0x20,0x43,0x1B,0x2A,0x30,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacroD[]={
	0x1B,0x24,0x39,0x1B,0x29,0x20,0x44,0x1B,0x2A,0x30,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacroE[]={
	0x1B,0x28,0x31,0x1B,0x29,0x30,0x1B,0x2A,0x4A,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};
static BYTE DefaultMacroF[]={
	0x1B,0x28,0x4A,0x1B,0x29,0x32,0x1B,0x2A,0x20,0x41,0x1B,0x2B,0x20,0x70,0x0F,0x1B,0x7D
};

// mark10als
// ARIB�̒ǉ��L�� �� �ǉ������̃e�[�u����`
// ���̂́A�uCaptionMain.cpp�v�Ő錾

#define ARIB_MAX		495
#define ARIB_MAX2		137

typedef struct _GAIJI_TABLE{
	string usARIB8;
	string strChar;
} GAIJI_TABLE;

extern GAIJI_TABLE GaijiTable[];

extern GAIJI_TABLE GaijiTbl2[];

extern BOOL m_bUnicode;

// mark10als

CARIB8CharDecode::CARIB8CharDecode(void)
{
}

CARIB8CharDecode::~CARIB8CharDecode(void)
{
}

void CARIB8CharDecode::InitCaption(void)
{
	if( m_wSWFMode==14 ){
		m_G0.iMF = MF_DRCS_1;
		m_G0.iMode = MF_MODE_DRCS;
		m_G0.iByte = 1;

		m_G2.iMF = MF_JIS_KANJI1;
		m_G2.iMode = MF_MODE_G;
		m_G2.iByte = 2;
	}else{
		m_G0.iMF = MF_JIS_KANJI1;
		m_G0.iMode = MF_MODE_G;
		m_G0.iByte = 2;

		m_G2.iMF = MF_HIRA;
		m_G2.iMode = MF_MODE_G;
		m_G2.iByte = 1;
	}
/*
	m_G0.iMF = MF_JIS_KANJI1;
	m_G0.iMode = MF_MODE_G;
	m_G0.iByte = 2;
*/
	m_G1.iMF = MF_ASCII;
	m_G1.iMode = MF_MODE_G;
	m_G1.iByte = 1;
/*
	m_G2.iMF = MF_HIRA;
	m_G2.iMode = MF_MODE_G;
	m_G2.iByte = 1;
*/
	m_G3.iMF = MF_MACRO;
	m_G3.iMode = MF_MODE_OTHER;
	m_G3.iByte = 1;

	m_GL = &m_G0;
	m_GR = &m_G2;

	m_strDecode = "";
	m_emStrSize = STR_NORMAL;

	m_bCharColorIndex = 7;
	m_bBackColorIndex = 8;
	m_bRasterColorIndex = 8;
	m_bDefPalette = 0;

	m_bUnderLine = FALSE;
	m_bShadow = FALSE;
	m_bBold = FALSE;
	m_bItalic = FALSE;
	m_bFlushMode = 0;
	m_bHLC = 0;


	switch(m_wSWFMode){
	case 7:
		//960x540��
		m_wClientW = 960;
		m_wClientH = 540;
		m_wCharW = 36;
		m_wCharH = 36;
		m_wCharHInterval = 4;
		m_wCharVInterval = 24;
		break;
	case 8:
		//960x540�c
		m_wClientW = 960;
		m_wClientH = 540;
		m_wCharW = 36;
		m_wCharH = 36;
		m_wCharHInterval = 12;
		m_wCharVInterval = 24;
		break;
	case 9:
		//720x480��
		m_wClientW = 720;
		m_wClientH = 480;
		m_wCharW = 36;
		m_wCharH = 36;
		m_wCharHInterval = 4;
		m_wCharVInterval = 16;
		break;
	case 10:
		//720x480�c
		m_wClientW = 720;
		m_wClientH = 480;
		m_wCharW = 36;
		m_wCharH = 36;
		m_wCharHInterval = 8;
		m_wCharVInterval = 24;
		break;
	case 14:
		//C�v���t�@�C��
		//�\���̈�320x180�A�\�����20x24�ŌŒ�
		m_wClientW = 320;
		m_wClientH = 180;
		m_wCharW = 18;
		m_wCharH = 18;
		m_wCharHInterval = 2;
		m_wCharVInterval = 6;
		break;
	default:
	m_wClientW=0;
	m_wClientH=0;
	m_wCharW=36;
	m_wCharH=36;
	m_wCharHInterval=0;
	m_wCharVInterval=0;
		break;
	}
//	m_wSWFMode=0;
	m_wClientX=0;
	m_wClientY=0;
	m_wPosX=0;
	m_wPosY=0;
	m_wMaxChar = 0;
	m_dwWaitTime = 0;

	m_pCaptionList = NULL;

	m_bPSI = FALSE;
	// mark10als
	m_bRPC = FALSE;
	m_wRPC = 0;
	m_bGaiji = FALSE;
	// mark10als
}

BOOL CARIB8CharDecode::Caption( const BYTE* pbSrc, DWORD dwSrcSize, vector<CAPTION_DATA>* pCaptionList )
{
	if( pbSrc == NULL || dwSrcSize == 0 || pCaptionList == NULL){
		return FALSE;
	}
	InitCaption();
	m_pCaptionList = pCaptionList;

	BOOL bRet = TRUE;
	DWORD dwReadCount = 0;
	while(dwReadCount<dwSrcSize){
		DWORD dwReadSize = 0;
		BOOL bRet = Analyze(pbSrc+dwReadCount, dwSrcSize-dwReadCount, &dwReadSize );
		if( bRet == TRUE ){
			if( m_strDecode.size() > 0 ){
				CheckModify();
			}
		}else{
			pCaptionList->clear();
			break;
		}
		m_strDecode = "";
		dwReadCount+=dwReadSize;
	}
	return bRet;
}

BOOL CARIB8CharDecode::IsSmallCharMode(void)
{
	if( m_bPSI == FALSE ){
		return FALSE;
	}
	BOOL bRet = FALSE;
	switch(m_emStrSize){
		case STR_SMALL:
			bRet = TRUE;
			break;
		case STR_MEDIUM:
			bRet = TRUE;
			break;
		case STR_NORMAL:
			bRet = FALSE;
			break;
		case STR_MICRO:
			bRet = TRUE;
			break;
		case STR_HIGH_W:
			bRet = FALSE;
			break;
		case STR_WIDTH_W:
			bRet = FALSE;
			break;
		case STR_W:
			bRet = FALSE;
			break;
		case STR_SPECIAL_1:
			bRet = FALSE;
			break;
		case STR_SPECIAL_2:
			bRet = FALSE;
			break;
		default:
			break;
	}
	return bRet;
}

BOOL CARIB8CharDecode::Analyze( const BYTE* pbSrc, DWORD dwSrcSize, DWORD* pdwReadSize )
{
	if( pbSrc == NULL || dwSrcSize == 0 || pdwReadSize == NULL){
		return FALSE;
	}
	BOOL bRet = TRUE;
	DWORD dwReadSize = 0;

	while( dwReadSize < dwSrcSize ){
		DWORD dwReadBuff = 0;
		//1�o�C�g�ڃ`�F�b�N
		if( pbSrc[dwReadSize] <= 0x20 ){
			//C0����R�[�h
			bRet = C0( pbSrc+dwReadSize, &dwReadBuff );
			dwReadSize += dwReadBuff;
			if( bRet == FALSE ){
				return FALSE;
			}else if( bRet == 2 ){
				bRet = TRUE;
				break;
			}
		}else if( pbSrc[dwReadSize] > 0x20 && pbSrc[dwReadSize] < 0x7F ){
			//GL�����̈�
			if( GL( pbSrc+dwReadSize, &dwReadBuff ) == FALSE ){
				return FALSE;
			}
			dwReadSize += dwReadBuff;
		}else if( pbSrc[dwReadSize] >= 0x7F && pbSrc[dwReadSize] <= 0xA0 ){
			//C1����R�[�h
			bRet = C1( pbSrc+dwReadSize, &dwReadBuff );
			dwReadSize += dwReadBuff;
			if( bRet == FALSE ){
				return FALSE;
			}else if( bRet == 2 ){
				bRet = TRUE;
				break;
			}
		}else if( pbSrc[dwReadSize] > 0xA0 && pbSrc[dwReadSize] < 0xFF ){
			//GR�����̈�
			if( GR( pbSrc+dwReadSize, &dwReadBuff ) == FALSE ){
				return FALSE;
			}
			dwReadSize += dwReadBuff;
		}
	}

	*pdwReadSize = dwReadSize;
	return bRet;
}

BOOL CARIB8CharDecode::C0( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	m_bGaiji = FALSE;
	if( pbSrc == NULL || pdwReadSize == NULL ){
		return FALSE;
	}

	DWORD dwReadSize = 0;
	DWORD dwReadBuff = 0;

	BOOL bRet = TRUE;

	switch(pbSrc[0]){
	case 0x20:
		//SP ��
		//�󔒂͕����T�C�Y�̉e������
		if(( IsSmallCharMode() == FALSE ) && ( m_emStrSize != STR_MEDIUM )){
	//		m_strDecode += "�@";
			AddToString( SpaceTable[0], m_bGaiji );
		}else{
	//		m_strDecode += ' ';
			AddToString( SpaceTable[1], m_bGaiji );
		}
		dwReadSize = 1;
		break;
	case 0x0D:
		//APR ���s
		// mark10als
		if (!m_bUnicode) {
		m_strDecode += "\r\n";
		} else {
			CheckModify();
			m_wPosX = 0;
			m_wPosY += (m_wCharH + m_wCharVInterval);
			m_wTmpPosX = m_wClientX;
		}
		dwReadSize = 1;
		break;
	case 0x0E:
		//LS1 GL��G1�Z�b�g
		m_GL = &m_G1;
		dwReadSize = 1;
		m_bModGL = TRUE;
		break;
	case 0x0F:
		//LS0 GL��G0�Z�b�g
		m_GL = &m_G0;
		dwReadSize = 1;
		m_bModGL = TRUE;
		break;
	case 0x19:
		//SS2 �V���O���V�t�g
		if( SS2( pbSrc+1, &dwReadBuff ) == FALSE ){
			return FALSE;
		}
		dwReadSize = 1+dwReadBuff;
		break;
	case 0x1D:
		//SS3 �V���O���V�t�g
		if( SS3( pbSrc+1, &dwReadBuff ) == FALSE ){
			return FALSE;
		}
		dwReadSize = 1+dwReadBuff;
		break;
	case 0x1B:
		//ESC �G�X�P�[�v�V�[�P���X
		if( ESC( pbSrc+1, &dwReadBuff ) == FALSE ){
			return FALSE;
		}
		dwReadSize = 1+dwReadBuff;
		break;
	case 0x16:
			//PAPF
			CheckModify();
			WORD m_wTmpCharW;
			if( m_emStrSize == STR_SMALL || m_emStrSize == STR_MEDIUM ){
				m_wTmpCharW = (m_wCharW + m_wCharHInterval) / 2;
			} else {
				m_wTmpCharW = (m_wCharW + m_wCharHInterval);
			}
			m_wPosX = m_wTmpPosX - m_wClientX;
			WORD CTLtmp;
			CTLtmp = (pbSrc[1]&0x7F)-0x40;
			for( WORD i=1; i<=CTLtmp; i++ ){
				if( m_wTmpPosX > (m_wMaxPosX - m_wTmpCharW) ){
					CheckModify();
					m_wPosX = 0;
					m_wPosY += (m_wCharH + m_wCharVInterval);
					m_wTmpPosX = m_wClientX;
				}
				m_wPosX += m_wTmpCharW;
				m_wTmpPosX += m_wTmpCharW;
			}
			dwReadSize = 2;
		break;
	case 0x1C:
			//APS
			CheckModify();

			// mark10als
			if (!m_bUnicode) {
			// modified by odaru
			m_wPosY = 60*(pbSrc[1]-0x40) + 30;
			m_wPosX = m_wCharW*(pbSrc[2]-0x40);
			if( m_emStrSize == STR_SMALL || m_emStrSize == STR_MEDIUM ){
				m_wPosX=m_wPosX/2;
			}

			if(m_emStrSize == STR_SMALL) {
				m_wPosY = 30 *(pbSrc[1]-0x40);
			}
			} else {
				m_wPosY = (m_wCharH + m_wCharVInterval) * (pbSrc[1] - 0x40 + 1);
				m_wPosX = (m_wCharW + m_wCharHInterval) * (pbSrc[2] - 0x40);
				if( m_emStrSize == STR_SMALL || m_emStrSize == STR_MEDIUM ){
					m_wPosX = m_wPosX / 2;
				}
				if(m_emStrSize == STR_SMALL) {
					m_wPosY = m_wPosY / 2;
				}
			}
			m_wTmpPosX = m_wClientX + m_wPosX;
			// mark10als

			dwReadSize = 3;
		break;
	case 0x0C:
			//CS
		{
			dwReadSize = 1;
			CAPTION_DATA Item;
			Item.bClear = TRUE;
			Item.dwWaitTime = m_dwWaitTime*100;
			if( m_pCaptionList != NULL ){
				m_pCaptionList->push_back(Item);
			}
			bRet = 2;
			m_dwWaitTime = 0;
		}
		break;
	case 0x09:
			//APF
		{
			CheckModify();
			WORD m_wTmpCharW;
			if( m_emStrSize == STR_SMALL || m_emStrSize == STR_MEDIUM ){
				m_wTmpCharW = (m_wCharW + m_wCharHInterval) / 2;
			} else {
				m_wTmpCharW = (m_wCharW + m_wCharHInterval);
			}
			m_wPosX = m_wTmpPosX - m_wClientX;
				if( m_wTmpPosX > (m_wMaxPosX - m_wTmpCharW) ){
					CheckModify();
					m_wPosX = 0;
					m_wPosY += (m_wCharH + m_wCharVInterval);
					m_wTmpPosX = m_wClientX;
				}
				m_wPosX += m_wTmpCharW;
				m_wTmpPosX += m_wTmpCharW;
			dwReadSize = 1;
		}
		break;
	default:
		//���T�|�[�g�̐���R�[�h
			//APB�AAPD�AAPU
			dwReadSize = 1;
		break;
	}

	*pdwReadSize = dwReadSize;

	return bRet;
}

BOOL CARIB8CharDecode::C1( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	m_bGaiji = FALSE;
	if( pbSrc == NULL || pdwReadSize == NULL ){
		return FALSE;
	}
	DWORD dwReadSize = 0;
	DWORD dwReadBuff = 0;

	BOOL bRet = TRUE;

	CheckModify();

	switch(pbSrc[0]){
	case 0x89:
		//MSZ ���p�w��
		m_emStrSize = STR_MEDIUM;
		dwReadSize = 1;
		break;
	case 0x8A:
		//NSZ �S�p�w��
		m_emStrSize = STR_NORMAL;
		dwReadSize = 1;
		break;
	case 0x80:
		//BKF ������
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x00;
		dwReadSize = 1;
		break;
	case 0x81:
		//RDF ������
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x01;
		dwReadSize = 1;
		break;
	case 0x82:
		//GRF ������
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x02;
		dwReadSize = 1;
		break;
	case 0x83:
		//YLF ������
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x03;
		dwReadSize = 1;
		break;
	case 0x84:
		//BLF ������
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x04;
		dwReadSize = 1;
		break;
	case 0x85:
		//MGF �����}�[���^
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x05;
		dwReadSize = 1;
		break;
	case 0x86:
		//CNF �����V�A��
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x06;
		dwReadSize = 1;
		break;
	case 0x87:
		//WHF ������
		m_bCharColorIndex = (m_bDefPalette<<4) | 0x07;
		dwReadSize = 1;
		break;
	case 0x88:
		//SSZ ���^�T�C�Y
		m_emStrSize = STR_SMALL;
		dwReadSize = 1;
		break;
	case 0x8B:
		//SZX �w��T�C�Y
		if( pbSrc[1] == 0x60 ){
			m_emStrSize = STR_MICRO;
		}else if( pbSrc[1] == 0x41 ){
			m_emStrSize = STR_HIGH_W;
		}else if( pbSrc[1] == 0x44 ){
			m_emStrSize = STR_WIDTH_W;
		}else if( pbSrc[1] == 0x45 ){
			m_emStrSize = STR_W;
		}else if( pbSrc[1] == 0x6B ){
			m_emStrSize = STR_SPECIAL_1;
		}else if( pbSrc[1] == 0x64 ){
			m_emStrSize = STR_SPECIAL_2;
		}
		dwReadSize = 2;
		break;
	case 0x90:
		//COL �F�w��
		if( pbSrc[1] == 0x20 ){
			dwReadSize = 3;
			m_bDefPalette = pbSrc[2]&0x0F;
		}else{
			switch(pbSrc[1]&0xF0){
				case 0x40:
					m_bCharColorIndex = pbSrc[1]&0x0F;
					break;
				case 0x50:
					m_bBackColorIndex = pbSrc[1]&0x0F;
					break;
				case 0x60:
					//���T�|�[�g
					break;
				case 0x70:
					//���T�|�[�g
					break;
				default:
					break;
			}
			dwReadSize = 2;
		}
		break;
	case 0x91:
		//FLC �t���b�V���O����
		if( pbSrc[1] == 0x40 ){
			m_bFlushMode = 1;
		}else if( pbSrc[1] == 0x47 ){
			m_bFlushMode = 2;
		}else if( pbSrc[1] == 0x4F ){
			m_bFlushMode = 0;
		}
		dwReadSize = 2;
		break;
	case 0x93:
		//POL �p�^�[���ɐ�
		//���T�|�[�g
		dwReadSize = 2;
		break;
	case 0x94:
		//WMM �������݃��[�h�ύX
		//���T�|�[�g
		dwReadSize = 2;
		break;
	case 0x95:
		//MACRO �}�N����`
		//���T�|�[�g
		{
		DWORD dwCount = 0;
		do{
			dwCount++;
		}while( pbSrc[dwCount] != 0x4F );
		dwReadSize = dwCount;
		}
		break;
	case 0x97:
		//HLC �͂ݐ���
		m_bHLC = pbSrc[1]&0x0F;
		dwReadSize = 2;
		break;
	case 0x98:
		//RPC �����J��Ԃ�
		// mark10als
		m_bRPC = TRUE;
		m_wRPC = pbSrc[1] -0x40;
		// mark10als
		dwReadSize = 2;
		break;
	case 0x99:
		//SPL �A���_�[���C�� ���U�C�N�̏I��
		m_bBold = FALSE;
		bRet = 2;
		dwReadSize = 1;
		break;
	case 0x9A:
		//STL �A���_�[���C�� ���U�C�N�̊J�n
		m_bBold = TRUE;
		dwReadSize = 1;
		break;
	case 0x9D:
		//TIME ���Ԑ���
		CheckModify();
		if( pbSrc[1] == 0x20 ){
			m_dwWaitTime += pbSrc[2]-0x40;		// modified by odaru
	//		m_dwWaitTime = pbSrc[2]-0x40;
			dwReadSize = 3;
		}else{
			DWORD dwCount = 0;
			do{
				dwCount++;
			}while( pbSrc[dwCount] != 0x43 && pbSrc[dwCount] != 0x40 && pbSrc[dwCount] != 0x41 && pbSrc[dwCount] != 0x42 );
			dwReadSize = dwCount;
		}
		break;
	case 0x9B:
		//CSI �R���g���[���V�[�P���X
		if( CSI( pbSrc, &dwReadBuff ) == FALSE ){
			return FALSE;
		}
		dwReadSize = dwReadBuff;
		break;
	default:
		//���T�|�[�g�̐���R�[�h
		dwReadSize = 1;
		break;
	}

	*pdwReadSize = dwReadSize;

	return bRet;
}

BOOL CARIB8CharDecode::GL( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	m_bGaiji = FALSE;
	if( pbSrc == NULL || pdwReadSize == NULL ){
		return FALSE;
	}

	DWORD dwReadSize = 0;
	if( m_GL->iMode == MF_MODE_G ){
		//�����R�[�h
		switch( m_GL->iMF ){
			case MF_JISX_KANA:
				//JISX X0201��0x7F�܂ł�ASCII�Ɠ���
			case MF_ASCII:
			case MF_PROP_ASCII:
				{
				if(( IsSmallCharMode() == FALSE ) && ( m_emStrSize != STR_MEDIUM )){
					//�S�p�Ȃ̂Ńe�[�u������SJIS�R�[�h�擾
	//				m_strDecode += AsciiTable[pbSrc[0]-0x21];
					AddToString( AsciiTable[pbSrc[0]-0x21], m_bGaiji );
				}else{
					//���p�Ȃ̂ł��̂܂ܓ����
	//				m_strDecode += pbSrc[0];
					AddToString( HalfAsciiTable[pbSrc[0]-0x21], m_bGaiji );
				}
				dwReadSize = 1;
				}
				break;
			case MF_HIRA:
			case MF_PROP_HIRA:
				{
				//�Ђ炪��
				//�e�[�u������SJIS�R�[�h�擾
	//			m_strDecode += HiraTable[pbSrc[0]-0x21];
				AddToString( HiraTable[pbSrc[0]-0x21], m_bGaiji );
				dwReadSize = 1;
				}
				break;
			case MF_KANA:
			case MF_PROP_KANA:
				{
				//�J�^�J�i
				//�e�[�u������SJIS�R�[�h�擾
	//			m_strDecode += KanaTable[pbSrc[0]-0x21];
				AddToString( KanaTable[pbSrc[0]-0x21], m_bGaiji );
				dwReadSize = 1;
				}
				break;
			case MF_MACRO:
				{
				DWORD dwTemp=0;
				//�}�N��
				//PSI/SI�ł͖��T�|�[�g
				switch(pbSrc[0]){
					case 0x60:
						Analyze(DefaultMacro0, sizeof(DefaultMacro0),&dwTemp);
						break;
					case 0x61:
						Analyze(DefaultMacro1, sizeof(DefaultMacro1),&dwTemp);
						break;
					case 0x62:
						Analyze(DefaultMacro2, sizeof(DefaultMacro2),&dwTemp);
						break;
					case 0x63:
						Analyze(DefaultMacro3, sizeof(DefaultMacro3),&dwTemp);
						break;
					case 0x64:
						Analyze(DefaultMacro4, sizeof(DefaultMacro4),&dwTemp);
						break;
					case 0x65:
						Analyze(DefaultMacro5, sizeof(DefaultMacro5),&dwTemp);
						break;
					case 0x66:
						Analyze(DefaultMacro6, sizeof(DefaultMacro6),&dwTemp);
						break;
					case 0x67:
						Analyze(DefaultMacro7, sizeof(DefaultMacro7),&dwTemp);
						break;
					case 0x68:
						Analyze(DefaultMacro8, sizeof(DefaultMacro8),&dwTemp);
						break;
					case 0x69:
						Analyze(DefaultMacro9, sizeof(DefaultMacro9),&dwTemp);
						break;
					case 0x6A:
						Analyze(DefaultMacroA, sizeof(DefaultMacroA),&dwTemp);
						break;
					case 0x6B:
						Analyze(DefaultMacroB, sizeof(DefaultMacroB),&dwTemp);
						break;
					case 0x6C:
						Analyze(DefaultMacroC, sizeof(DefaultMacroC),&dwTemp);
						break;
					case 0x6D:
						Analyze(DefaultMacroD, sizeof(DefaultMacroD),&dwTemp);
						break;
					case 0x6E:
						Analyze(DefaultMacroE, sizeof(DefaultMacroE),&dwTemp);
						break;
					case 0x6F:
						Analyze(DefaultMacroF, sizeof(DefaultMacroF),&dwTemp);
						break;
					default:
						break;
				}
				dwReadSize = 1;
				}
				break;
			case MF_KANJI:
			case MF_JIS_KANJI1:
			case MF_JIS_KANJI2:
			case MF_KIGOU:
				//����
				{
				if( ToSJIS( pbSrc[0], pbSrc[1] ) == FALSE ){
					ToCustomFont( pbSrc[0], pbSrc[1] );
				}
				dwReadSize = 2;
				}
				break;
			default:
				dwReadSize = m_GL->iByte;
				break;
		}
	}else{
		if( m_GL->iMF == MF_MACRO){
			DWORD dwTemp=0;
			//�}�N��
			//PSI/SI�ł͖��T�|�[�g
			switch(pbSrc[0]){
				case 0x60:
					Analyze(DefaultMacro0, sizeof(DefaultMacro0),&dwTemp);
					break;
				case 0x61:
					Analyze(DefaultMacro1, sizeof(DefaultMacro1),&dwTemp);
					break;
				case 0x62:
					Analyze(DefaultMacro2, sizeof(DefaultMacro2),&dwTemp);
					break;
				case 0x63:
					Analyze(DefaultMacro3, sizeof(DefaultMacro3),&dwTemp);
					break;
				case 0x64:
					Analyze(DefaultMacro4, sizeof(DefaultMacro4),&dwTemp);
					break;
				case 0x65:
					Analyze(DefaultMacro5, sizeof(DefaultMacro5),&dwTemp);
					break;
				case 0x66:
					Analyze(DefaultMacro6, sizeof(DefaultMacro6),&dwTemp);
					break;
				case 0x67:
					Analyze(DefaultMacro7, sizeof(DefaultMacro7),&dwTemp);
					break;
				case 0x68:
					Analyze(DefaultMacro8, sizeof(DefaultMacro8),&dwTemp);
					break;
				case 0x69:
					Analyze(DefaultMacro9, sizeof(DefaultMacro9),&dwTemp);
					break;
				case 0x6A:
					Analyze(DefaultMacroA, sizeof(DefaultMacroA),&dwTemp);
					break;
				case 0x6B:
					Analyze(DefaultMacroB, sizeof(DefaultMacroB),&dwTemp);
					break;
				case 0x6C:
					Analyze(DefaultMacroC, sizeof(DefaultMacroC),&dwTemp);
					break;
				case 0x6D:
					Analyze(DefaultMacroD, sizeof(DefaultMacroD),&dwTemp);
					break;
				case 0x6E:
					Analyze(DefaultMacroE, sizeof(DefaultMacroE),&dwTemp);
					break;
				case 0x6F:
					Analyze(DefaultMacroF, sizeof(DefaultMacroF),&dwTemp);
					break;
				default:
					break;
			}
			dwReadSize = 1;
		}else if( m_GL->iMode == MF_MODE_DRCS){
			WORD DRCSCharCode = (( m_GR->iMF ) << 8) | (pbSrc[0] & 0x7f);
			
		//	printf( "%04X\n", DRCSCharCode );
			
			string tmpDRCSChar = Get_dicCharcode_Char(DRCSCharCode);
			string tmpStr = tmpDRCSChar.substr( 0, 4 );
			if (tmpStr != "[�O:"){
				m_bGaiji = TRUE;
			}
			AddToString( tmpDRCSChar.c_str(), m_bGaiji );
			dwReadSize = m_GL->iByte;
		}else{
			dwReadSize = m_GL->iByte;
		}
	}

	*pdwReadSize = dwReadSize;

	return TRUE;
}


BOOL CARIB8CharDecode::GR( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	m_bGaiji = FALSE;
	if( pbSrc == NULL || pdwReadSize == NULL ){
		return FALSE;
	}

	DWORD dwReadSize = 0;
	if( m_GR->iMode == MF_MODE_G ){
		//�����R�[�h
		switch( m_GR->iMF ){
			case MF_ASCII:
			case MF_PROP_ASCII:
				{
				if(( IsSmallCharMode() == FALSE ) && ( m_emStrSize != STR_MEDIUM )){
					//�S�p�Ȃ̂Ńe�[�u������SJIS�R�[�h�擾
	//				m_strDecode += AsciiTable[(pbSrc[0]&0x7F)-0x21];
					AddToString( AsciiTable[(pbSrc[0]&0x7F)-0x21], m_bGaiji );
				}else{
					//���p�Ȃ̂ł��̂܂ܓ����
	//				m_strDecode += pbSrc[0]&0x7F;
					AddToString( HalfAsciiTable[(pbSrc[0]&0x7F)-0x21], m_bGaiji );
				}
				dwReadSize = 1;
				}
				break;
			case MF_HIRA:
			case MF_PROP_HIRA:
				{
				//�Ђ炪��
				//�e�[�u������SJIS�R�[�h�擾
	//			m_strDecode += HiraTable[(pbSrc[0]&0x7F)-0x21];
				AddToString( HiraTable[(pbSrc[0]&0x7F)-0x21], m_bGaiji );
				dwReadSize = 1;
				}
				break;
			case MF_JISX_KANA:
				//JIX X0201��0x80�ȍ~�͔��p�J�i
			case MF_KANA:
			case MF_PROP_KANA:
				{
				//�J�^�J�i
				//�e�[�u������SJIS�R�[�h�擾
	//			m_strDecode += KanaTable[(pbSrc[0]&0x7F)-0x21];
				AddToString( KanaTable[(pbSrc[0]&0x7F)-0x21], m_bGaiji );
				dwReadSize = 1;
				}
				break;
			case MF_MACRO:
				{
				DWORD dwTemp=0;
				//�}�N��
				//PSI/SI�ł͖��T�|�[�g
				switch(pbSrc[0]){
					case 0x60:
						Analyze(DefaultMacro0, sizeof(DefaultMacro0),&dwTemp);
						break;
					case 0x61:
						Analyze(DefaultMacro1, sizeof(DefaultMacro1),&dwTemp);
						break;
					case 0x62:
						Analyze(DefaultMacro2, sizeof(DefaultMacro2),&dwTemp);
						break;
					case 0x63:
						Analyze(DefaultMacro3, sizeof(DefaultMacro3),&dwTemp);
						break;
					case 0x64:
						Analyze(DefaultMacro4, sizeof(DefaultMacro4),&dwTemp);
						break;
					case 0x65:
						Analyze(DefaultMacro5, sizeof(DefaultMacro5),&dwTemp);
						break;
					case 0x66:
						Analyze(DefaultMacro6, sizeof(DefaultMacro6),&dwTemp);
						break;
					case 0x67:
						Analyze(DefaultMacro7, sizeof(DefaultMacro7),&dwTemp);
						break;
					case 0x68:
						Analyze(DefaultMacro8, sizeof(DefaultMacro8),&dwTemp);
						break;
					case 0x69:
						Analyze(DefaultMacro9, sizeof(DefaultMacro9),&dwTemp);
						break;
					case 0x6A:
						Analyze(DefaultMacroA, sizeof(DefaultMacroA),&dwTemp);
						break;
					case 0x6B:
						Analyze(DefaultMacroB, sizeof(DefaultMacroB),&dwTemp);
						break;
					case 0x6C:
						Analyze(DefaultMacroC, sizeof(DefaultMacroC),&dwTemp);
						break;
					case 0x6D:
						Analyze(DefaultMacroD, sizeof(DefaultMacroD),&dwTemp);
						break;
					case 0x6E:
						Analyze(DefaultMacroE, sizeof(DefaultMacroE),&dwTemp);
						break;
					case 0x6F:
						Analyze(DefaultMacroF, sizeof(DefaultMacroF),&dwTemp);
						break;
					default:
						break;
				}
				dwReadSize = 1;
				}
				break;
			case MF_KANJI:
			case MF_JIS_KANJI1:
			case MF_JIS_KANJI2:
			case MF_KIGOU:
				{
				//����
				if( ToSJIS( (pbSrc[0]&0x7F), (pbSrc[1]&0x7F) ) == FALSE ){
					ToCustomFont( (pbSrc[0]&0x7F), (pbSrc[1]&0x7F) );
				}
				dwReadSize = 2;
				}
				break;
			default:
				dwReadSize = m_GR->iByte;
				break;
		}
	}else{
		if( m_GR->iMF == MF_MACRO ){
			DWORD dwTemp=0;
			//�}�N��
			//PSI/SI�ł͖��T�|�[�g
			switch(pbSrc[0]){
				case 0x60:
					Analyze(DefaultMacro0, sizeof(DefaultMacro0),&dwTemp);
					break;
				case 0x61:
					Analyze(DefaultMacro1, sizeof(DefaultMacro1),&dwTemp);
					break;
				case 0x62:
					Analyze(DefaultMacro2, sizeof(DefaultMacro2),&dwTemp);
					break;
				case 0x63:
					Analyze(DefaultMacro3, sizeof(DefaultMacro3),&dwTemp);
					break;
				case 0x64:
					Analyze(DefaultMacro4, sizeof(DefaultMacro4),&dwTemp);
					break;
				case 0x65:
					Analyze(DefaultMacro5, sizeof(DefaultMacro5),&dwTemp);
					break;
				case 0x66:
					Analyze(DefaultMacro6, sizeof(DefaultMacro6),&dwTemp);
					break;
				case 0x67:
					Analyze(DefaultMacro7, sizeof(DefaultMacro7),&dwTemp);
					break;
				case 0x68:
					Analyze(DefaultMacro8, sizeof(DefaultMacro8),&dwTemp);
					break;
				case 0x69:
					Analyze(DefaultMacro9, sizeof(DefaultMacro9),&dwTemp);
					break;
				case 0x6A:
					Analyze(DefaultMacroA, sizeof(DefaultMacroA),&dwTemp);
					break;
				case 0x6B:
					Analyze(DefaultMacroB, sizeof(DefaultMacroB),&dwTemp);
					break;
				case 0x6C:
					Analyze(DefaultMacroC, sizeof(DefaultMacroC),&dwTemp);
					break;
				case 0x6D:
					Analyze(DefaultMacroD, sizeof(DefaultMacroD),&dwTemp);
					break;
				case 0x6E:
					Analyze(DefaultMacroE, sizeof(DefaultMacroE),&dwTemp);
					break;
				case 0x6F:
					Analyze(DefaultMacroF, sizeof(DefaultMacroF),&dwTemp);
					break;
				default:
					break;
			}
			dwReadSize = 1;
		}else if( m_GR->iMode == MF_MODE_DRCS){
			WORD DRCSCharCode = (( m_GR->iMF ) << 8) | (pbSrc[0] & 0x7f);
			
		//	printf( "%04X\n", DRCSCharCode );
			
			string tmpDRCSChar = Get_dicCharcode_Char(DRCSCharCode);
			string tmpStr = tmpDRCSChar.substr( 0, 4 );
			if (tmpStr != "[�O:"){
				m_bGaiji = TRUE;
			}
			AddToString( tmpDRCSChar.c_str(), m_bGaiji );
			dwReadSize = m_GR->iByte;
		}else{
			dwReadSize = m_GR->iByte;
		}
	}

	*pdwReadSize = dwReadSize;

	return TRUE;
}

BOOL CARIB8CharDecode::ToSJIS( const BYTE bFirst, const BYTE bSecond )
{
	m_bGaiji = FALSE;
	if( bFirst >= 0x75 && bSecond >= 0x21 ){
		return FALSE;
	}

	unsigned char ucFirst = bFirst;
	unsigned char ucSecond = bSecond;
	
	ucFirst = ucFirst - 0x21;
	if( ( ucFirst & 0x01 ) == 0 ){
		ucSecond += 0x1F;
		if( ucSecond >= 0x7F ){
			ucSecond += 0x01;
		}
	}else{
		ucSecond += 0x7E;
	}
	ucFirst = ucFirst>>1;
	if( ucFirst >= 0x1F ){
		ucFirst += 0xC1;
	}else{
		ucFirst += 0x81;
	}

	char cDec[3] = "";
	cDec[0] = ucFirst;
	cDec[1] = ucSecond;

	// mark10als
//	m_strDecode += cDec;
	AddToString( cDec, m_bGaiji );
	// mark10als

	return TRUE;
}

BOOL CARIB8CharDecode::ToCustomFont( const BYTE bFirst, const BYTE bSecond )
{
	unsigned short usSrc = (unsigned short)(bFirst<<8) | bSecond;
	m_bGaiji = TRUE;
	string tmpGaiji = "";
	//	ARIB �ǉ�����
	if( 0x7521 <= usSrc && usSrc <= 0x757E ){
		tmpGaiji = GaijiTbl2[usSrc-0x7521].strChar;
	}else if( 0x7621 <= usSrc && usSrc <= 0x764B ){
		tmpGaiji = GaijiTbl2[usSrc-0x7621+94].strChar;
	//	ARIB �ǉ��L��
	}else if(0x7A21 <= usSrc && usSrc <= 0x7A7E ){
		tmpGaiji = GaijiTable[usSrc-0x7A20].strChar;
	}else if(0x7B21 <= usSrc && usSrc <= 0x7B7E ){
		tmpGaiji = GaijiTable[usSrc-0x7B20+100].strChar;
	}else if(0x7C21 <= usSrc && usSrc <= 0x7C7E ){
		tmpGaiji = GaijiTable[usSrc-0x7C20+200].strChar;
	}else if(0x7D21 <= usSrc && usSrc <= 0x7D7E ){
		tmpGaiji = GaijiTable[usSrc-0x7D20+300].strChar;
	}else if(0x7E21 <= usSrc && usSrc <= 0x7E7E ){
		tmpGaiji = GaijiTable[usSrc-0x7E20+400].strChar;
	}
	if (tmpGaiji == "") {
		if (GaijiTable[0].strChar != "") {
			tmpGaiji = GaijiTable[0].strChar;
		} else {
			m_bGaiji = FALSE;
			AddToString( "�E", m_bGaiji );
			return FALSE;
		}
	}
	AddToString( tmpGaiji.c_str(), m_bGaiji );
	return TRUE;
}

	// mark10als
BOOL CARIB8CharDecode::AddToString( const char* cDec, BOOL m_bGaiji )
{
	if ((m_wPosX == 0) && (m_wPosY == 0)){
		m_wPosY = (m_wCharH + m_wCharVInterval);
	}
	int wkLen = 256;
	CHAR cTmpDec[256] = {0};
	WCHAR str[256] = {0};
	CHAR strUTF8[256] = {0};
	string tmpcDec;
	if( m_emStrSize == STR_MEDIUM ){
		// �S�p -> ���p
		tmpcDec = GetHalfChar(cDec);
	} else {
		tmpcDec = cDec;
	}
	if ((m_bUnicode) && (!m_bGaiji)) {
		// CP 932 to UTF-8
		MultiByteToWideChar(932, 0, tmpcDec.c_str(), -1, str, wkLen);
		WideCharToMultiByte(CP_UTF8, 0, str, -1, strUTF8, wkLen, NULL, NULL);
		strcpy_s(cTmpDec, wkLen, strUTF8);
	} else {
		strcpy_s(cTmpDec, wkLen, tmpcDec.c_str());
	}
	WORD m_wTmpCharW;
	if( m_emStrSize == STR_SMALL || m_emStrSize == STR_MEDIUM ){
		m_wTmpCharW = (m_wCharW + m_wCharHInterval) / 2;
	} else {
		m_wTmpCharW = (m_wCharW + m_wCharHInterval);
	}
	m_wMaxPosX = m_wClientX + m_wClientW;
	if( m_bRPC ){
		if( m_wRPC == 0 ){
			for( ; m_wTmpPosX <= (m_wMaxPosX - m_wTmpCharW); ){
				m_strDecode += cTmpDec;
				m_wTmpPosX += m_wTmpCharW;
			}
			CheckModify();
			m_wPosX = 0;
			m_wPosY += (m_wCharH + m_wCharVInterval);
			m_wTmpPosX = m_wClientX;
		} else {
			for( WORD i=1; i<=m_wRPC; i++ ){
				if( m_wTmpPosX > (m_wMaxPosX - m_wTmpCharW) ){
					CheckModify();
					m_wPosX = 0;
					m_wPosY += (m_wCharH + m_wCharVInterval);
					m_wTmpPosX = m_wClientX;
				}
				m_strDecode += cTmpDec;
				m_wTmpPosX += m_wTmpCharW;
			}
		}
	}else{
		if( m_wTmpPosX > (m_wMaxPosX - m_wTmpCharW) ){
			CheckModify();
			m_wPosX = 0;
			m_wPosY += (m_wCharH + m_wCharVInterval);
			m_wTmpPosX = m_wClientX;
		}
		m_strDecode += cTmpDec;
		m_wTmpPosX += m_wTmpCharW;
	}
	m_bRPC = FALSE;
	m_wRPC = 0;
	m_bGaiji = FALSE;
	return TRUE;
}
	// mark10als

BOOL CARIB8CharDecode::ESC( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	if( pbSrc == NULL ){
		return FALSE;
	}

	DWORD dwReadSize = 0;
	if( pbSrc[0] == 0x24 ){
		if( pbSrc[1] >= 0x28 && pbSrc[1] <= 0x2B ){
			if( pbSrc[2] == 0x20 ){
				//2�o�C�gDRCS
				switch(pbSrc[1]){
					case 0x28:
						m_G0.iMF = pbSrc[3];
						m_G0.iMode = MF_MODE_DRCS;
						m_G0.iByte = 2;
						break;
					case 0x29:
						m_G1.iMF = pbSrc[3];
						m_G1.iMode = MF_MODE_DRCS;
						m_G1.iByte = 2;
						break;
					case 0x2A:
						m_G2.iMF = pbSrc[3];
						m_G2.iMode = MF_MODE_DRCS;
						m_G2.iByte = 2;
						break;
					case 0x2B:
						m_G3.iMF = pbSrc[3];
						m_G3.iMode = MF_MODE_DRCS;
						m_G3.iByte = 2;
						break;
					default:
						break;
				}
				dwReadSize = 4;
			}else if( pbSrc[2] == 0x28 ){
				//�����o�C�g�A���y����
				switch(pbSrc[1]){
					case 0x28:
						m_G0.iMF = pbSrc[3];
						m_G0.iMode = MF_MODE_OTHER;
						m_G0.iByte = 1;
						break;
					case 0x29:
						m_G1.iMF = pbSrc[3];
						m_G1.iMode = MF_MODE_OTHER;
						m_G1.iByte = 1;
						break;
					case 0x2A:
						m_G2.iMF = pbSrc[3];
						m_G2.iMode = MF_MODE_OTHER;
						m_G2.iByte = 1;
						break;
					case 0x2B:
						m_G3.iMF = pbSrc[3];
						m_G3.iMode = MF_MODE_OTHER;
						m_G3.iByte = 1;
						break;
					default:
						break;
				}
				dwReadSize = 4;
			}else{
				//2�o�C�gG�Z�b�g
				switch(pbSrc[1]){
					case 0x29:
						m_G1.iMF = pbSrc[2];
						m_G1.iMode = MF_MODE_G;
						m_G1.iByte = 2;
						break;
					case 0x2A:
						m_G2.iMF = pbSrc[2];
						m_G2.iMode = MF_MODE_G;
						m_G2.iByte = 2;
						break;
					case 0x2B:
						m_G3.iMF = pbSrc[2];
						m_G3.iMode = MF_MODE_G;
						m_G3.iByte = 2;
						break;
					default:
						break;
				}
				dwReadSize = 3;
			}
		}else{
			//2�o�C�gG�Z�b�g
			m_G0.iMF = pbSrc[1];
			m_G0.iMode = MF_MODE_G;
			m_G0.iByte = 2;
			dwReadSize = 2;
		}
	}else if( pbSrc[0] >= 0x28 && pbSrc[0] <= 0x2B ){
		if( pbSrc[1] == 0x20 ){
			//1�o�C�gDRCS
			switch(pbSrc[0]){
				case 0x28:
					m_G0.iMF = pbSrc[2];
					m_G0.iMode = MF_MODE_DRCS;
					m_G0.iByte = 1;
					break;
				case 0x29:
					m_G1.iMF = pbSrc[2];
					m_G1.iMode = MF_MODE_DRCS;
					m_G1.iByte = 1;
					break;
				case 0x2A:
					m_G2.iMF = pbSrc[2];
					m_G2.iMode = MF_MODE_DRCS;
					m_G2.iByte = 1;
					break;
				case 0x2B:
					m_G3.iMF = pbSrc[2];
					m_G3.iMode = MF_MODE_DRCS;
					m_G3.iByte = 1;
					break;
				default:
					break;
			}
			dwReadSize = 3;
		}else{
			//1�o�C�gG�Z�b�g
			switch(pbSrc[0]){
				case 0x28:
					m_G0.iMF = pbSrc[1];
					m_G0.iMode = MF_MODE_G;
					m_G0.iByte = 1;
					break;
				case 0x29:
					m_G1.iMF = pbSrc[1];
					m_G1.iMode = MF_MODE_G;
					m_G1.iByte = 1;
					break;
				case 0x2A:
					m_G2.iMF = pbSrc[1];
					m_G2.iMode = MF_MODE_G;
					m_G2.iByte = 1;
					break;
				case 0x2B:
					m_G3.iMF = pbSrc[1];
					m_G3.iMode = MF_MODE_G;
					m_G3.iByte = 1;
					break;
				default:
					break;
			}
			dwReadSize = 2;
		}
	}else if( pbSrc[0] == 0x6E ){
		//GL��G2�Z�b�g
		m_GL = &m_G2;
		dwReadSize = 1;
		m_bModGL = TRUE;
	}else if( pbSrc[0] == 0x6F ){
		//GL��G3�Z�b�g
		m_GL = &m_G3;
		dwReadSize = 1;
		m_bModGL = TRUE;
	}else if( pbSrc[0] == 0x7C ){
		//GR��G3�Z�b�g
		m_GR = &m_G3;
		dwReadSize = 1;
	}else if( pbSrc[0] == 0x7D ){
		//GR��G2�Z�b�g
		m_GR = &m_G2;
		dwReadSize = 1;
	}else if( pbSrc[0] == 0x7E ){
		//GR��G1�Z�b�g
		m_GR = &m_G1;
		dwReadSize = 1;
	}else{
		//���T�|�[�g
		dwReadSize = 1;
		*pdwReadSize = dwReadSize;
		return FALSE;
	}

	*pdwReadSize = dwReadSize;

	return TRUE;
}

BOOL CARIB8CharDecode::SS2( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	m_bModGL = FALSE;
	MF_MODE* LastG;
	LastG = m_GL;
	//�ꎞ�I�ɓ���ւ���
	m_GL = &m_G2;
	//GL�����̈�
	BOOL bRet = GL( pbSrc, pdwReadSize );
	if( m_bModGL != FALSE ){
		return bRet;
	}
	if( bRet != FALSE ){
		//���ɖ߂�
		m_GL = LastG;
		return bRet;
	}
	//���ɖ߂�
	m_GL = LastG;
	return TRUE;
}

BOOL CARIB8CharDecode::SS3( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	m_bModGL = FALSE;
	MF_MODE* LastG;
	LastG = m_GL;
	//�ꎞ�I�ɓ���ւ���
	m_GL = &m_G3;
	//GL�����̈�
	BOOL bRet = GL( pbSrc, pdwReadSize );
	if( m_bModGL != FALSE ){
		return bRet;
	}
	if( bRet != FALSE ){
		//���ɖ߂�
		m_GL = LastG;
		return bRet;
	}
	//���ɖ߂�
	m_GL = LastG;
	return TRUE;
}

BOOL CARIB8CharDecode::CSI( const BYTE* pbSrc, DWORD* pdwReadSize )
{
	if( pbSrc == NULL || pdwReadSize == NULL ){
		return FALSE;
	}
	DWORD dwReadSize = 0;

	do{
		dwReadSize++;
	}while( pbSrc[dwReadSize] != 0x20 );
	dwReadSize++;
	
	switch(pbSrc[dwReadSize]){
		case 0x53:
			//SWF
			{
				BOOL bCharMode = FALSE;
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( bCharMode == FALSE ){
							m_wSWFMode = wParam;
						}else{
							//���T�|�[�g
						}
					}else if(pbSrc[i] == 0x3B){
						bCharMode = TRUE;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x6E:
			//RCS
			{
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						m_bRasterColorIndex = (BYTE)wParam;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x61:
			//ACPS
			{
				BOOL bSeparate = FALSE;
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( bSeparate == FALSE ){
							m_wPosX = wParam;
						}else{
							m_wPosY = wParam;
						}
					}else if(pbSrc[i] == 0x3B){
						bSeparate = TRUE;
						m_wPosX = wParam;
						wParam = 0;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
				// mark10als
				m_wTmpPosX = m_wPosX;
				if (m_bUnicode) {
					m_wPosX += 2000;
					m_wPosY += 2000;
				}
			}
			break;
		case 0x56:
			//SDF
			{
				BOOL bSeparate = FALSE;
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( bSeparate == FALSE ){
							m_wClientW = wParam;
						}else{
							m_wClientH = wParam;
						}
					}else if(pbSrc[i] == 0x3B){
						bSeparate = TRUE;
						m_wClientW = wParam;
						wParam = 0;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
				// mark10als
				if (m_wCharHInterval == 0) {
					m_wCharHInterval = ((m_wClientW * 10) / 155) - 36;
				}
				if (m_wCharVInterval == 0) {
					m_wCharVInterval = (m_wClientH / 8) - 36;
				}
			}
			break;
		case 0x5F:
			//SDP
			{
				BOOL bSeparate = FALSE;
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( bSeparate == FALSE ){
							m_wClientX = wParam;
						}else{
							m_wClientY = wParam;
						}
					}else if(pbSrc[i] == 0x3B){
						bSeparate = TRUE;
						m_wClientX = wParam;
						wParam = 0;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x57:
			//SSM
			{
				BOOL bSeparate = FALSE;
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( bSeparate == FALSE ){
							m_wCharW = wParam;
						}else{
							m_wCharH = wParam;
						}
					}else if(pbSrc[i] == 0x3B){
						bSeparate = TRUE;
						m_wCharW = wParam;
						wParam = 0;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x58:
			//SHS
			{
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						m_wCharHInterval = wParam;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x59:
			//SVS
			{
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						m_wCharVInterval = wParam;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x42:
			//GSM
			//���T�|�[�g
			break;
		case 0x5D:
			//GAA
			//���T�|�[�g
			break;
		case 0x5E:
			//SRC
			//���T�|�[�g
			break;
		case 0x62:
			//TCC
			//���T�|�[�g
			break;
		case 0x65:
			//CFS
			//���T�|�[�g
			break;
		case 0x63:
			//ORN
			{
				BOOL bSeparate = FALSE;
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( bSeparate == FALSE ){
							if( wParam == 0x02 ){
								m_bShadow = TRUE;
							}
						}
					}else if(pbSrc[i] == 0x3B){
						bSeparate = TRUE;
						if( wParam == 0x02 ){
							m_bShadow = TRUE;
						}
						wParam = 0;
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x64:
			//MDF
			{
				WORD wParam = 0;
				for( DWORD i=1; i<dwReadSize; i++ ){
					if( pbSrc[i] == 0x20 ){
						if( wParam == 0 ){
							m_bBold = FALSE;
							m_bItalic = FALSE;
						}else if( wParam == 1 ){
							m_bBold = TRUE;
						}else if( wParam == 2 ){
							m_bItalic = TRUE;
						}else if( wParam == 3 ){
							m_bBold = TRUE;
							m_bItalic = TRUE;
						}
					}else{
						wParam = wParam*10+(pbSrc[i]&0x0F);
					}
				}
			}
			break;
		case 0x66:
			//XCS
			//���T�|�[�g
			break;
		case 0x68:
			//PRA
			//���T�|�[�g
			break;
		case 0x54:
			//CCC
			//���T�|�[�g
			break;
		case 0x67:
			//SCR
			//���T�|�[�g
			break;
		case 0x69:
			//ACS
			//���T�|�[�g
			if (dwReadSize != 3 || pbSrc[dwReadSize-2] <= 0x31)
				break;
			while (pbSrc[++dwReadSize] != 0x9B)
				;
			dwReadSize += 3;
			break;
		default:
			break;
	}
	dwReadSize++;

	*pdwReadSize = dwReadSize;

	return TRUE;
}

void CARIB8CharDecode::CheckModify(void)
{
	if( m_bPSI == TRUE ){
		return;
	}
	if( m_strDecode.length() > 0 ){
		if( IsChgPos() == FALSE ){
			CAPTION_CHAR_DATA CharItem;
			CreateCaptionCharData(&CharItem);
			(*m_pCaptionList)[m_pCaptionList->size()-1].CharList.push_back(CharItem);
			m_strDecode = "";
		}else{
			CAPTION_DATA Item;
			CreateCaptionData(&Item);
			m_pCaptionList->push_back(Item);

			CAPTION_CHAR_DATA CharItem;
			CreateCaptionCharData(&CharItem);
			(*m_pCaptionList)[m_pCaptionList->size()-1].CharList.push_back(CharItem);
			m_strDecode = "";
			m_dwWaitTime = 0;
		}
	}
}

void CARIB8CharDecode::CreateCaptionData(CAPTION_DATA* pItem)
{
	pItem->bClear = FALSE;
	pItem->dwWaitTime = m_dwWaitTime*100;
	pItem->wSWFMode = m_wSWFMode;
	pItem->wClientX = m_wClientX;
	pItem->wClientY = m_wClientY;
	pItem->wClientW = m_wClientW;
	pItem->wClientH = m_wClientH;
	pItem->wPosX = m_wPosX;
	pItem->wPosY = m_wPosY;
}

void CARIB8CharDecode::CreateCaptionCharData(CAPTION_CHAR_DATA* pItem)
{
	pItem->strDecode = m_strDecode;

	pItem->stCharColor = DefClut[m_bCharColorIndex];
	pItem->stBackColor = DefClut[m_bBackColorIndex];
	pItem->stRasterColor = DefClut[m_bRasterColorIndex];

	pItem->bUnderLine = m_bUnderLine;
	pItem->bShadow = m_bShadow;
	pItem->bBold = m_bBold;
	pItem->bItalic = m_bItalic;
	pItem->bFlushMode = m_bFlushMode;
	pItem->bHLC = m_bHLC<<4;

	pItem->wCharW = m_wCharW;
	pItem->wCharH = m_wCharH;
	pItem->wCharHInterval = m_wCharHInterval;
	pItem->wCharVInterval = m_wCharVInterval;
	pItem->emCharSizeMode = m_emStrSize;
}

BOOL CARIB8CharDecode::IsChgPos(void)
{
	if( m_pCaptionList == NULL || m_strDecode.length() == 0){
		return FALSE;
	}
	if( m_pCaptionList->size() == 0 ){
		return TRUE;
	}
	int iIndex = (int)m_pCaptionList->size()-1;
	if( (*m_pCaptionList)[iIndex].wClientH != m_wClientH ){
		return TRUE;
	}
	if( (*m_pCaptionList)[iIndex].wClientW != m_wClientW ){
		return TRUE;
	}
	if( (*m_pCaptionList)[iIndex].wClientX != m_wClientX ){
		return TRUE;
	}
	if( (*m_pCaptionList)[iIndex].wClientY != m_wClientY ){
		return TRUE;
	}
	if( (*m_pCaptionList)[iIndex].wPosX != m_wPosX ){
		return TRUE;
	}
	if( (*m_pCaptionList)[iIndex].wPosY != m_wPosY ){
		return TRUE;
	}

	return FALSE;
}

/*
BOOL CalcMD5FromDRCSPattern(BYTE *pbHash, const BYTE *pbPatternData, const DWORD dwDataLen)
{
	HCRYPTPROV hProv = NULL;
	HCRYPTHASH hHash = NULL;
	BOOL bRet = FALSE;
	if( !::CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) ){
		hProv = NULL;
		goto EXIT;
	}
	if( !::CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash) ){
		hHash = NULL;
		goto EXIT;
	}
	if( !::CryptHashData(hHash, pbPatternData, dwDataLen, 0) ) goto EXIT;
	DWORD dwHashLen = 16;
	if( !::CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0) ) goto EXIT;
	bRet = TRUE;

EXIT:
	if( hHash ) ::CryptDestroyHash(hHash);
	if( hProv ) ::CryptReleaseContext(hProv, 0);
	return bRet;
}
*/
#define GET_PIXEL_1(b,x) ( ((b)[(x)/8]>>(7-(x)%8)) & 0x1 )
#define GET_PIXEL_2(b,x) ( ((b)[(x)/4]>>((3-(x)%4)*2)) & 0x3 )

BOOL CARIB8CharDecode::DRCSHeaderparse( const BYTE* pbSrc, DWORD dwSrcSize, BOOL bDRCS_0 )
{
	if( pbSrc == NULL || dwSrcSize == 0 ){
		return FALSE;
	}

	BYTE bNumberOfCode = pbSrc[0];
	DWORD dwRead = 1;
	for( int i=0; i<bNumberOfCode; i++ ){
		if( dwSrcSize < dwRead + 3 ){
			return FALSE;
		}
		WORD wDRCCode = (pbSrc[dwRead]<<8) | pbSrc[dwRead+1];
	//	WORD wDRCCode = bDRCS_0 ? (pbSrc[dwRead]<<8) | pbSrc[dwRead+1] :
	//	                         ((pbSrc[dwRead]-MF_DRCS_0)<<8) | pbSrc[dwRead+1];
			
	//		printf( "%04X DRCSHeaderparse\n", wDRCCode );
			
		BYTE bNumberOfFont = pbSrc[dwRead+2];
		BOOL bFirstFont = TRUE;
		dwRead += 3;
		for( int j=0; j<bNumberOfFont; j++ ){
			if( dwSrcSize < dwRead + 4 ){
				return FALSE;
			}
			BYTE bMode = pbSrc[dwRead] & 0x0F;
			BYTE bDepth = pbSrc[dwRead+1];
			BYTE bPixPerByte = bDepth==0 ? 8 : 4;
			BYTE bWidth = pbSrc[dwRead+2];
			BYTE bHeight = pbSrc[dwRead+3];
			if( !(bMode==0 && bDepth==0 || bMode==1 && bDepth==2) || bWidth>DRCS_SIZE_MAX || bHeight>DRCS_SIZE_MAX ){
				//���T�|�[�g(�^�p�K��O)
				return FALSE;
			}
			dwRead += 4;
			if( dwSrcSize < dwRead + (bHeight*bWidth+bPixPerByte-1) / bPixPerByte ){
				return FALSE;
			}
			// 
			if ( bFirstFont ){
				bFirstFont = FALSE;
				DWORD dwDRCS_pat_size = (bHeight*bWidth+bPixPerByte-1) / bPixPerByte;
				BYTE md5[16] = {0};
				char md5char[33] = {0};
				string MD5Str = "";
				CalcMD5FromDRCSPattern( md5, md5char, pbSrc+dwRead, dwDRCS_pat_size);
				MD5Str = md5char;
				string DRCSGaiji_str = Get_dicHash_Char(MD5Str);
				if (DRCSGaiji_str == "NF") {
					// �n�b�V�������ǉ�
					DRCSGaiji_str = "[�O:"+ MD5Str + "]";
					Add_dicHash_Char(MD5Str, DRCSGaiji_str);
					string BMPname = GetAppPath() + "\\Gaiji\\" + MD5Str + ".bmp";
					WCHAR str[_MAX_PATH] = {0};
					MultiByteToWideChar(932, 0, BMPname.c_str(), -1, str, _MAX_PATH);
					//�t�@�C�����Ȃ���Ώ�������
					HANDLE hFile = CreateFile(str, GENERIC_WRITE, 0,NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
					if( hFile != INVALID_HANDLE_VALUE ){
						//�����ŐV�K�ǉ�
						DRCS_PATTERN drcs;
						drcs.wDRCCode = wDRCCode;
						drcs.wGradation = bDepth + 2;
			
						DWORD dwSizeImage = 0;
						//�r�b�g�}�b�v�̎d�l�ɂ�荶�����瑖��
						for( int y=bHeight-1; y>=0; y-- ){
							for( int x=0; x<bWidth; x++ ){
								int nPix = bDepth==0 ? GET_PIXEL_1(pbSrc+dwRead, y*bWidth+x) * 3 :
								                       GET_PIXEL_2(pbSrc+dwRead, y*bWidth+x);
								if( x%2==0 ){
									drcs.bBitmap[dwSizeImage++] = (BYTE)(nPix<<4);
								}else{
									drcs.bBitmap[dwSizeImage-1] |= (BYTE)nPix;
								}
							}
							//�r�b�g�}�b�v�̎d�l�ɂ��X�g���C�h��4�o�C�g���E�ɂ���
							dwSizeImage = (dwSizeImage + 3) / 4 * 4;
						}
						BITMAPINFOHEADER bmiHeader = {0};
						bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
						bmiHeader.biWidth = bWidth;
						bmiHeader.biHeight = bHeight;
						bmiHeader.biPlanes = 1;
						bmiHeader.biBitCount = 4;
						bmiHeader.biCompression = BI_RGB;
						bmiHeader.biSizeImage = dwSizeImage;
						drcs.bmiHeader = bmiHeader;
	
						//�ǂ�Ȕz�F�ɂ��Ă��\��Ȃ��Bcolors[4]�ȏ�̐F�͏o�����Ȃ�
						RGBQUAD colors[16] = {{255,255,255,0}, {170,170,170,0}, {85,85,85,0}, {0,0,0,0}};
						BITMAPFILEHEADER bmfHeader = {0};
						bmfHeader.bfType = 0x4D42;
						bmfHeader.bfOffBits = sizeof(bmfHeader) + sizeof(bmiHeader) + sizeof(colors);
						bmfHeader.bfSize = bmfHeader.bfOffBits + dwSizeImage;
						DWORD dwWritten;
						WriteFile(hFile, &bmfHeader, sizeof(bmfHeader), &dwWritten, NULL);
						WriteFile(hFile, &bmiHeader, sizeof(bmiHeader), &dwWritten, NULL);
						WriteFile(hFile, &colors, sizeof(colors), &dwWritten, NULL);
						WriteFile(hFile, drcs.bBitmap, dwSizeImage, &dwWritten, NULL);
						CloseHandle(hFile);
					}
					if ( Get_dicCharcode_Char(wDRCCode) != DRCSGaiji_str ) {
						Add_dicCharcode_Char(wDRCCode, DRCSGaiji_str);
					}
				}
			}	// if ( bFirstFont ){
			dwRead += (bHeight*bWidth+bPixPerByte-1) / bPixPerByte;
		}	// for( int j=0; j<bNumberOfFont; j++ ){
	}	// 	for( int i=0; i<bNumberOfCode; i++ ){
	return TRUE;
}
