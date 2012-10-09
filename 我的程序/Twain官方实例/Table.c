/*
* File: Table.c
* company: J.F.L. Peripherals Solutions Inc.
* Date: Mai 19/98
* Description:
*			This file contain the code for fill the Table Entry.
*
*	Copyright © 1998 TWAIN Working Group: Adobe Systems Incorporated, 
*	Canon Information Systems, Eastman Kodak Company, 
*	Fujitsu Computer Products of America, Genoa Technology, 
*	Hewlett-Packard Company, Intel Corporation, Kofax Image Products, 
*	JFL Peripheral Solutions Inc., Ricoh Corporation, and Xerox Corporation.  
*	All rights reserved.
*/
#include <windows.h>
#include <string.h>
#include "twain.h"
#include "Table.h"

TABLEENTRY Destination[MAX_DEST] = 
								{
									{"Source Manager", 0},
									{"Source", 1}
								};

TABLEENTRY DataGroup[MAX_DG] = 
								{
									{"DG_CONTROL", DG_CONTROL},
									{"DG_IMAGE", DG_IMAGE}
								};

TABLEENTRY DataType[MAX_DAT] = 
								{
									{"DAT_CAPABILITY", DAT_CAPABILITY},
									{"DAT_CUSTOMDSDATA", DAT_CUSTOMDSDATA},
									{"DAT_CIECOLOR", DAT_CIECOLOR},
									{"DAT_EVENT", DAT_EVENT},
									{"DAT_EXTIMAGEINFO", DAT_EXTIMAGEINFO},
									{"DAT_GRAYRESPONSE", DAT_GRAYRESPONSE},
									{"DAT_IDENTITY", DAT_IDENTITY},
									{"DAT_IMAGEFILEXFER", DAT_IMAGEFILEXFER},
									{"DAT_IMAGEINFO", DAT_IMAGEINFO},
									{"DAT_IMAGELAYOUT", DAT_IMAGELAYOUT},
									{"DAT_IMAGEMEMXFER", DAT_IMAGEMEMXFER},
									{"DAT_IMAGENATIVEXFER", DAT_IMAGENATIVEXFER},
									{"DAT_JPEGCOMPRESSION", DAT_JPEGCOMPRESSION},
									{"DAT_NULL", DAT_NULL},
									{"DAT_PALETTE8", DAT_PALETTE8},
									{"DAT_PARENT", DAT_PARENT},
									{"DAT_PENDINGXFERS", DAT_PENDINGXFERS},
									{"DAT_RGBRESPONSE", DAT_RGBRESPONSE},
									{"DAT_SETUPFILEXFER", DAT_SETUPFILEXFER},
									{"DAT_SETUPMEMXFER", DAT_SETUPMEMXFER},
									{"DAT_STATUS", DAT_STATUS},
									{"DAT_USERINTERFACE", DAT_USERINTERFACE},
									{"DAT_XFERGROUP", DAT_XFERGROUP}
								};

TABLEENTRY Message[MAX_MSG] = 
								{
									{"MSG_CHECKSTATUS", MSG_CHECKSTATUS},
									{"MSG_CLOSEDS", MSG_CLOSEDS},
									{"MSG_CLOSEDSM", MSG_CLOSEDSM},
									{"MSG_CLOSEDSOK", MSG_CLOSEDSOK},
									{"MSG_CLOSEDSREQ", MSG_CLOSEDSREQ},
									{"MSG_DISABLEDS", MSG_DISABLEDS},
									{"MSG_ENABLEDS", MSG_ENABLEDS},
									{"MSG_ENABLEDSUIONLY", MSG_ENABLEDSUIONLY},
									{"MSG_ENDXFER", MSG_ENDXFER},
									{"MSG_GET", MSG_GET},
									{"MSG_GETCURRENT", MSG_GETCURRENT},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_GETFIRST", MSG_GETFIRST},
									{"MSG_GETNEXT", MSG_GETNEXT},
									{"MSG_NULL", MSG_NULL},
									{"MSG_OPENDS", MSG_OPENDS},
									{"MSG_OPENDSM", MSG_OPENDSM},
									{"MSG_PROCESSEVENT", MSG_PROCESSEVENT},
									{"MSG_QUERYSUPPORT", MSG_QUERYSUPPORT},
									{"MSG_RESET", MSG_RESET},
									{"MSG_SET", MSG_SET},
									{"MSG_USERSELECT", MSG_USERSELECT},
									{"MSG_XFERREADY", MSG_XFERREADY}
								};

TABLEENTRY Capability[MAX_CAP] = 
								{
									{"CAP_AUTHOR", CAP_AUTHOR},
									{"CAP_AUTOFEED", CAP_AUTOFEED},
									{"CAP_AUTOSCAN", CAP_AUTOSCAN},
									{"CAP_CAPTION", CAP_CAPTION},
									{"CAP_CLEARPAGE", CAP_CLEARPAGE},
									{"CAP_CUSTOMDSDATA", CAP_CUSTOMDSDATA},
									{"CAP_DEVICEONLINE", CAP_DEVICEONLINE},
									{"CAP_DUPLEX", CAP_DUPLEX},
									{"CAP_DUPLEXENABLED", CAP_DUPLEXENABLED},
									{"CAP_ENABLEDSUIONLY", CAP_ENABLEDSUIONLY},
									{"CAP_ENDORSER", CAP_ENDORSER},
									{"CAP_EXTENDEDCAPS", CAP_EXTENDEDCAPS},
									{"CAP_FEEDERENABLED", CAP_FEEDERENABLED},
									{"CAP_FEEDERLOADED", CAP_FEEDERLOADED},
									{"CAP_FEEDPAGE", CAP_FEEDPAGE},
									{"CAP_INDICATORS", CAP_INDICATORS},
									{"CAP_JOBCONTROL", CAP_JOBCONTROL},
									{"CAP_PAPERDETECTABLE", CAP_PAPERDETECTABLE},
									{"CAP_REWINDPAGE", CAP_REWINDPAGE},
									{"CAP_SUPPORTEDCAPS", CAP_SUPPORTEDCAPS},
									{"CAP_THUMBNAILSENABLED", CAP_THUMBNAILSENABLED},
									{"CAP_TIMEDATE", CAP_TIMEDATE},
									{"CAP_UICONTROLLABLE", CAP_UICONTROLLABLE},
									{"CAP_XFERCOUNT", CAP_XFERCOUNT},
									{"ICAP_AUTOBRIGHT", ICAP_AUTOBRIGHT},
									{"ICAP_BITDEPTH", ICAP_BITDEPTH},
									{"ICAP_BITDEPTHREDUCTION", ICAP_BITDEPTHREDUCTION},
									{"ICAP_BITORDER", ICAP_BITORDER},
									{"ICAP_BITORDERCODES", ICAP_BITORDERCODES},
									{"ICAP_BRIGHTNESS", ICAP_BRIGHTNESS},
									{"ICAP_CCITTKFACTOR", ICAP_CCITTKFACTOR},
									{"ICAP_COMPRESSION", ICAP_COMPRESSION},
									{"ICAP_CONTRAST", ICAP_CONTRAST},
									{"ICAP_CUSTHALFTONE", ICAP_CUSTHALFTONE},
									{"ICAP_EXPOSURETIME", ICAP_EXPOSURETIME},
									{"ICAP_EXTIMAGEINFO", ICAP_EXTIMAGEINFO},
									{"ICAP_FILTER", ICAP_FILTER},
									{"ICAP_FLASHUSED", ICAP_FLASHUSED},
									{"ICAP_FRAMES", ICAP_FRAMES},
									{"ICAP_GAMMA", ICAP_GAMMA},
									{"ICAP_HALFTONES", ICAP_HALFTONES},
									{"ICAP_HIGHLIGHT", ICAP_HIGHLIGHT},
									{"ICAP_IMAGEDATASET", ICAP_IMAGEDATASET},
									{"ICAP_IMAGEFILEFORMAT", ICAP_IMAGEFILEFORMAT},
									{"ICAP_JPEGPIXELTYPE", ICAP_JPEGPIXELTYPE},
									{"ICAP_LAMPSTATE", ICAP_LAMPSTATE},
									{"ICAP_LIGHTPATH", ICAP_LIGHTPATH},
									{"ICAP_LIGHTSOURCE", ICAP_LIGHTSOURCE},
									{"ICAP_MAXFRAMES", ICAP_MAXFRAMES},
									{"ICAP_MINIMUMHEIGHT", ICAP_MINIMUMHEIGHT},
									{"ICAP_MINIMUMWIDTH", ICAP_MINIMUMWIDTH},
									{"ICAP_ORIENTATION", ICAP_ORIENTATION},
									{"ICAP_PHYSICALHEIGHT", ICAP_PHYSICALHEIGHT},
									{"ICAP_PHYSICALWIDTH", ICAP_PHYSICALWIDTH},
									{"ICAP_PIXELFLAVOR", ICAP_PIXELFLAVOR},
									{"ICAP_PIXELFLAVORCODES", ICAP_PIXELFLAVORCODES},
									{"ICAP_PIXELTYPE", ICAP_PIXELTYPE},
									{"ICAP_PLANARCHUNKY", ICAP_PLANARCHUNKY},
									{"ICAP_ROTATION", ICAP_ROTATION},
									{"ICAP_SHADOW", ICAP_SHADOW},
									{"ICAP_SUPPORTEDSIZES", ICAP_SUPPORTEDSIZES},
									{"ICAP_THRESHOLD", ICAP_THRESHOLD},
									{"ICAP_TILES", ICAP_TILES},
									{"ICAP_TIMEFILL", ICAP_TIMEFILL},
									{"ICAP_UNDEFINEDIMAGESIZE", ICAP_UNDEFINEDIMAGESIZE},
									{"ICAP_UNITS", ICAP_UNITS},
									{"ICAP_XFERMECH", ICAP_XFERMECH},
									{"ICAP_XNATIVERESOLUTION", ICAP_XNATIVERESOLUTION},
									{"ICAP_XRESOLUTION", ICAP_XRESOLUTION},
									{"ICAP_XSCALING", ICAP_XSCALING},
									{"ICAP_YNATIVERESOLUTION", ICAP_YNATIVERESOLUTION},
									{"ICAP_YRESOLUTION", ICAP_YRESOLUTION},
									{"ICAP_YSCALING", ICAP_YSCALING}
								};


TABLEENTRY ConType[MAX_CONTYPE] = 
								{
									{"TWCC_BADPROTOCOL", TWCC_BADPROTOCOL},
									{"TWON_ARRAY", TWON_ARRAY},
									{"TWON_ENUMERATION", TWON_ENUMERATION},
									{"TWON_ONEVALUE", TWON_ONEVALUE},
									{"TWON_RANGE", TWON_RANGE}
								};


TABLEENTRY DG_SourceManager[MAX_DGSM] =
								{
									{"DG_CONTROL", DG_CONTROL}
								};

TABLEENTRY DG_Source[MAX_DGS] = 
								{
									{"DG_CONTROL", DG_CONTROL},
									{"DG_IMAGE", DG_IMAGE}
								};

TABLEENTRY DSM_DGControl[MAX_DSMDAT] = 
								{
									{"DAT_IDENTITY", DAT_IDENTITY},
									{"DAT_PARENT", DAT_PARENT},
									{"DAT_STATUS", DAT_STATUS}
								};

TABLEENTRY DS_DGControl[MAX_DSCONTROL] =
								{
									{"DAT_CAPABILITY", DAT_CAPABILITY},
									{"DAT_CUSTOMDSDATA", DAT_CUSTOMDSDATA},
									{"DAT_EVENT", DAT_EVENT},
									{"DAT_PENDINGXFERS", DAT_PENDINGXFERS},
									{"DAT_SETUPFILEXFER", DAT_SETUPFILEXFER},
									{"DAT_SETUPMEMXFER", DAT_SETUPMEMXFER},
									{"DAT_STATUS", DAT_STATUS},
									{"DAT_USERINTERFACE", DAT_USERINTERFACE},
									{"DAT_XFERGROUP", DAT_XFERGROUP}
								};

TABLEENTRY DS_DGImage[MAX_DSIMAGE] = 
								{
									{"DAT_CIECOLOR", DAT_CIECOLOR},
									{"DAT_EXTIMAGEINFO", DAT_EXTIMAGEINFO},
									{"DAT_GRAYRESPONSE", DAT_GRAYRESPONSE},
									{"DAT_IMAGEFILEXFER", DAT_IMAGEFILEXFER},
									{"DAT_IMAGEINFO", DAT_IMAGEINFO},
									{"DAT_IMAGELAYOUT", DAT_IMAGELAYOUT},
									{"DAT_IMAGEMEMXFER", DAT_IMAGEMEMXFER},
									{"DAT_IMAGENATIVEXFER", DAT_IMAGENATIVEXFER},
									{"DAT_JPEGCOMPRESSION", DAT_JPEGCOMPRESSION},
									{"DAT_PALETTE8", DAT_PALETTE8},
									{"DAT_RGBRESPONSE", DAT_RGBRESPONSE}
								};

TABLEENTRY MSG_Capability[MAX_CAPABILITY] =
								{ 
									{"MSG_GET", MSG_GET},
									{"MSG_GETCURRENT", MSG_GETCURRENT},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_QUERYSUPPORT", MSG_QUERYSUPPORT},
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_CieColor[MAX_CIECOLOR] = 		
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_CustomDSData[MAX_CUSTOMDSDATA] = 
								{
									{"MSG_GET", MSG_GET},
									{"MSG_SET", MSG_SET}
								};
	
TABLEENTRY MSG_Event[MAX_EVENT] = 
								{
									{"MSG_PROCESSEVENT", MSG_PROCESSEVENT}
								};

TABLEENTRY MSG_ExtImageInfo[MAX_EXTIMAGEINFO] = 
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_GrayResponse[MAX_GRAYRESPONSE] = 
								{
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_Identity[MAX_IDENTITY] = 
								{
									{"MSG_CLOSEDS", MSG_CLOSEDS},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_GETFIRST", MSG_GETFIRST},
									{"MSG_GETNEXT", MSG_GETNEXT},
									{"MSG_OPENDS", MSG_OPENDS},
									{"MSG_USERSELECT", MSG_USERSELECT},
								};

TABLEENTRY MSG_ImageFileXfer[MAX_IMAGEFILEXFER] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_ImageInfo[MAX_IMAGEINFO] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_ImageLayout[MAX_IMAGELAYOUT] = 
								{ 
									{"MSG_GET", MSG_GET},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_ImageMemXfer[MAX_IMAGEMEMXFER] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_ImageNativeXfer[MAX_IMAGENATIVEXFER] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_JpegCompression[MAX_JPEGCOMPRESSION] =
								{ 
									{"MSG_GET", MSG_GET},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_Null[MAX_NULL] = 
								{
									{"MSG_XFERREADY", MSG_XFERREADY},
									{"MSG_CLOSEDSREQ", MSG_CLOSEDSREQ},
									{"MSG_CLOSEDSOK", MSG_CLOSEDSOK}
								};

TABLEENTRY MSG_Palette8[MAX_PALETTE8] =
								{ 
									{"MSG_GET", MSG_GET},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_Parent[MAX_PARENT] =
								{
									{"MSG_CLOSEDSM", MSG_CLOSEDSM},
									{"MSG_OPENDSM", MSG_OPENDSM}
								};

TABLEENTRY MSG_PendingXfers[MAX_PENDINGXFERS] =
								{
									{"MSG_ENDXFER", MSG_ENDXFER}, 
									{"MSG_GET", MSG_GET},
									{"MSG_RESET",	MSG_RESET}
								};

TABLEENTRY MSG_RgbResponse[MAX_RGBRESPONSE] =
								{
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_SetupFileXfer[MAX_SETUPFILEXFER] =
								{ 
									{"MSG_GET", MSG_GET},
									{"MSG_GETDEFAULT", MSG_GETDEFAULT},
									{"MSG_RESET",	MSG_RESET},
									{"MSG_SET", MSG_SET}
								};

TABLEENTRY MSG_SetupMemXfer[MAX_SETUPMEMXFER] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_Status[MAX_STATUS] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEENTRY MSG_UserInterface[MAX_USERINTERFACE] =
								{
									{"MSG_DISABLEDS", MSG_DISABLEDS},
									{"MSG_ENABLEDS", MSG_ENABLEDS},
									{"MSG_ENABLEDSUIONLY", MSG_ENABLEDSUIONLY}
								};

TABLEENTRY MSG_XferGroup[MAX_XFERGROUP] =
								{
									{"MSG_GET", MSG_GET}
								};

TABLEMSG MsgTable[MAX_DAT] = 
								{
									{MSG_Capability, MAX_CAPABILITY},
									{MSG_CustomDSData, MAX_CUSTOMDSDATA},
									{MSG_CieColor, MAX_CIECOLOR},
									{MSG_Event, MAX_EVENT},
									{MSG_ExtImageInfo, MAX_EXTIMAGEINFO},
									{MSG_GrayResponse, MAX_GRAYRESPONSE},
									{MSG_Identity, MAX_IDENTITY},
									{MSG_ImageFileXfer, MAX_IMAGEFILEXFER},
									{MSG_ImageInfo, MAX_IMAGEINFO},
									{MSG_ImageLayout, MAX_IMAGELAYOUT},
									{MSG_ImageMemXfer, MAX_IMAGEMEMXFER},
									{MSG_ImageNativeXfer, MAX_IMAGENATIVEXFER},
									{MSG_JpegCompression, MAX_JPEGCOMPRESSION}, 
									{MSG_Null, MAX_NULL},
									{MSG_Palette8, MAX_PALETTE8},
									{MSG_Parent, MAX_PARENT},
									{MSG_PendingXfers, MAX_PENDINGXFERS},
									{MSG_RgbResponse, MAX_RGBRESPONSE},
									{MSG_SetupFileXfer, MAX_SETUPFILEXFER},
									{MSG_SetupMemXfer, MAX_SETUPMEMXFER},
									{MSG_Status, MAX_STATUS},
									{MSG_UserInterface, MAX_USERINTERFACE},
									{MSG_XferGroup, MAX_XFERGROUP}
								};

TABLEENTRY PixelType[MAX_PIXELTYPE] =
								{
									{"TWPT_BW", TWPT_BW},
									{"TWPT_GRAY", TWPT_GRAY},
									{"TWPT_RGB", TWPT_RGB},
									{"TWPT_PALETTE", TWPT_PALETTE},
									{"TWPT_CMY", TWPT_CMY},
									{"TWPT_CMYK", TWPT_CMYK},
									{"TWPT_YUV", TWPT_YUV},
									{"TWPT_YUVK", TWPT_YUVK},
									{"TWPT_CIEXYZ", TWPT_CIEXYZ}
								};

TABLEENTRY PaletteType[MAX_PALETTETYPE] =
								{
									{"TWPA_RGB", TWPA_RGB},
									{"TWPA_GRAY", TWPA_GRAY},
									{"TWPA_CMY", TWPA_CMY}
								};

TABLEENTRY FormatType[MAX_FORMATTYPE] =
								{
									{"TWFF_TIFF", TWFF_TIFF},
									{"TWFF_PICT", TWFF_PICT},
									{"TWFF_BMP", TWFF_BMP},
									{"TWFF_XBM", TWFF_XBM},
									{"TWFF_JFIF", TWFF_JFIF}
								};

TABLEENTRY CompressionType[MAX_COMPRESSIONTYPE] =
								{
									{"TWCP_NONE", TWCP_NONE},
									{"TWCP_PACKBITS", TWCP_PACKBITS},
									{"TWCP_GROUP31D", TWCP_GROUP31D},
									{"TWCP_GROUP31DEOL", TWCP_GROUP31DEOL},
									{"TWCP_GROUP32D", TWCP_GROUP32D},
									{"TWCP_GROUP4", TWCP_GROUP4},
									{"TWCP_JPEG", TWCP_JPEG},
									{"TWCP_LZW", TWCP_LZW},
									{"TWCP_JBIG", TWCP_JBIG}
								};

TABLEENTRY VerLanguageType[MAX_VERLANGUAGETYPE] =
								{
									{"TWLG_DAN", TWLG_DAN},
									{"TWLG_DUT", TWLG_DUT},
									{"TWLG_ENG", TWLG_ENG},
									{"TWLG_FCF", TWLG_FCF},
									{"TWLG_FIN", TWLG_FIN},
									{"TWLG_FRN", TWLG_FRN},
									{"TWLG_GER", TWLG_GER},
									{"TWLG_ICE", TWLG_ICE},
									{"TWLG_ITN", TWLG_ITN},
									{"TWLG_NOR", TWLG_NOR},
									{"TWLG_POR", TWLG_POR},
									{"TWLG_SPA", TWLG_SPA},
									{"TWLG_SWE", TWLG_SWE},
									{"TWLG_USA", TWLG_USA}
								};

TABLEENTRY VerContryType[MAX_VERCONTRYTYPE] = 
								{
									{"TWCY_AFGHANISTAN",TWCY_AFGHANISTAN},
									{"TWCY_ALGERIA", TWCY_ALGERIA},
									{"TWCY_AMERICANSAMOA", TWCY_AMERICANSAMOA},
									{"TWCY_ANDORRA", TWCY_ANDORRA},
									{"TWCY_ANGOLA", TWCY_ANGOLA},
									{"TWCY_ANGUILLA", TWCY_ANGUILLA},
									{"TWCY_ANTIGUA", TWCY_ANTIGUA},
									{"TWCY_ARGENTINA", TWCY_ARGENTINA},
									{"TWCY_ARUBA", TWCY_ARUBA},
									{"TWCY_ASCENSIONI", TWCY_ASCENSIONI},
									{"TWCY_AUSTRALIA", TWCY_AUSTRALIA},
									{"TWCY_AUSTRIA", TWCY_AUSTRIA},
									{"TWCY_BAHAMAS", TWCY_BAHAMAS},
									{"TWCY_BAHRAIN", TWCY_BAHRAIN},
									{"TWCY_BANGLADESH", TWCY_BANGLADESH},
									{"TWCY_BARBADOS", TWCY_BARBADOS},
									{"TWCY_BELGIUM", TWCY_BELGIUM},
									{"TWCY_BELIZE", TWCY_BELIZE},
									{"TWCY_BENIN", TWCY_BENIN},
									{"TWCY_BERMUDA", TWCY_BERMUDA},
									{"TWCY_BHUTAN", TWCY_BHUTAN},
									{"TWCY_BOLIVIA", TWCY_BOLIVIA},
									{"TWCY_BOTSWANA", TWCY_BOTSWANA},
									{"TWCY_BRITAIN", TWCY_BRITAIN},
									{"TWCY_BRITVIRGINIS", TWCY_BRITVIRGINIS},
									{"TWCY_BRAZIL", TWCY_BRAZIL},
									{"TWCY_BRUNEI", TWCY_BRUNEI},
									{"TWCY_BULGARIA", TWCY_BULGARIA},
									{"TWCY_BURKINAFASO", TWCY_BURKINAFASO},
									{"TWCY_BURMA", TWCY_BURMA},
									{"TWCY_BURUNDI", TWCY_BURUNDI},
									{"TWCY_CAMAROON", TWCY_CAMAROON},
									{"TWCY_CANADA", TWCY_CANADA},
									{"TWCY_CAPEVERDEIS", TWCY_CAPEVERDEIS},
									{"TWCY_CAYMANIS", TWCY_CAYMANIS},
									{"TWCY_CENTRALAFREP", TWCY_CENTRALAFREP},
									{"TWCY_CHAD", TWCY_CHAD},
									{"TWCY_CHILE", TWCY_CHILE},
									{"TWCY_CHINA", TWCY_CHINA},
									{"TWCY_CHRISTMASIS", TWCY_CHRISTMASIS},
									{"TWCY_COCOSIS", TWCY_COCOSIS},
									{"TWCY_COLOMBIA", TWCY_COLOMBIA},
									{"TWCY_COMOROS", TWCY_COMOROS},
									{"TWCY_CONGO", TWCY_CONGO},
									{"TWCY_COOKIS", TWCY_COOKIS},
									{"TWCY_COSTARICA", TWCY_COSTARICA},
									{"TWCY_CUBA", TWCY_CUBA},
									{"TWCY_CYPRUS", TWCY_CYPRUS},
									{"TWCY_CZECHOSLOVAKIA", TWCY_CZECHOSLOVAKIA},
									{"TWCY_DENMARK", TWCY_DENMARK},
									{"TWCY_DJIBOUTI", TWCY_DJIBOUTI},
									{"TWCY_DOMINICA", TWCY_DOMINICA},
									{"TWCY_DOMINCANREP", TWCY_DOMINCANREP},
									{"TWCY_EASTERIS", TWCY_EASTERIS},
									{"TWCY_ECUADOR", TWCY_ECUADOR},
									{"TWCY_EGYPT", TWCY_EGYPT},
									{"TWCY_ELSALVADOR", TWCY_ELSALVADOR},
									{"TWCY_EQGUINEA", TWCY_EQGUINEA},
									{"TWCY_ETHIOPIA", TWCY_ETHIOPIA},
									{"TWCY_FALKLANDIS", TWCY_FALKLANDIS},
									{"TWCY_FAEROEIS", TWCY_FAEROEIS},
									{"TWCY_FIJIISLANDS", TWCY_FIJIISLANDS},
									{"TWCY_FINLAND", TWCY_FINLAND},
									{"TWCY_FRANCE", TWCY_FRANCE},
									{"TWCY_FRANTILLES", TWCY_FRANTILLES},
									{"TWCY_FRGUIANA", TWCY_FRGUIANA},
									{"TWCY_FRPOLYNEISA", TWCY_FRPOLYNEISA},
									{"TWCY_FUTANAIS", TWCY_FUTANAIS},
									{"TWCY_GABON", TWCY_GABON},
									{"TWCY_GAMBIA", TWCY_GAMBIA},
									{"TWCY_GERMANY", TWCY_GERMANY},
									{"TWCY_GHANA", TWCY_GHANA},
									{"TWCY_GIBRALTER", TWCY_GIBRALTER},
									{"TWCY_GREECE", TWCY_GREECE},
									{"TWCY_GREENLAND", TWCY_GREENLAND},
									{"TWCY_GRENADA", TWCY_GRENADA},
									{"TWCY_GRENEDINES", TWCY_GRENEDINES},
									{"TWCY_GUADELOUPE", TWCY_GUADELOUPE},
									{"TWCY_GUAM", TWCY_GUAM},
									{"TWCY_GUANTANAMOBAY", TWCY_GUANTANAMOBAY},
									{"TWCY_GUATEMALA", TWCY_GUATEMALA},
									{"TWCY_GUINEA", TWCY_GUINEA},
									{"TWCY_GUINEABISSAU", TWCY_GUINEABISSAU},
									{"TWCY_GUYANA", TWCY_GUYANA},
									{"TWCY_HAITI", TWCY_HAITI},
									{"TWCY_HONDURAS", TWCY_HONDURAS},
									{"TWCY_HONGKONG", TWCY_HONGKONG},
									{"TWCY_HUNGARY", TWCY_HUNGARY},
									{"TWCY_ICELAND", TWCY_ICELAND},
									{"TWCY_INDIA", TWCY_INDIA},
									{"TWCY_INDONESIA", TWCY_INDONESIA},
									{"TWCY_IRAN", TWCY_IRAN},
									{"TWCY_IRAQ", TWCY_IRAQ},
									{"TWCY_IRELAND", TWCY_IRELAND},
									{"TWCY_ISRAEL", TWCY_ISRAEL},
									{"TWCY_ITALY", TWCY_ITALY},
									{"TWCY_IVORYCOAST", TWCY_IVORYCOAST},
									{"TWCY_JAMAICA", TWCY_JAMAICA},
									{"TWCY_JAPAN", TWCY_JAPAN},
									{"TWCY_JORDAN", TWCY_JORDAN},
									{"TWCY_KENYA", TWCY_KENYA},
									{"TWCY_KIRIBATI", TWCY_KIRIBATI},
									{"TWCY_KOREA", TWCY_KOREA},
									{"TWCY_KUWAIT", TWCY_KUWAIT},
									{"TWCY_LAOS", TWCY_LAOS},
									{"TWCY_LEBANON", TWCY_LEBANON},
									{"TWCY_LIBERIA", TWCY_LIBERIA},
									{"TWCY_LIBYA", TWCY_LIBYA},
									{"TWCY_LIECHTENSTEIN", TWCY_LIECHTENSTEIN},
									{"TWCY_LUXENBOURG", TWCY_LUXENBOURG},
									{"TWCY_MACAO", TWCY_MACAO},
									{"TWCY_MADAGASCAR", TWCY_MADAGASCAR},
									{"TWCY_MALAWI", TWCY_MALAWI},
									{"TWCY_MALAYSIA", TWCY_MALAYSIA},
									{"TWCY_MALDIVES", TWCY_MALDIVES},
									{"TWCY_MALI", TWCY_MALI},
									{"TWCY_MALTA", TWCY_MALTA},
									{"TWCY_MARSHALLIS", TWCY_MARSHALLIS},
									{"TWCY_MAURITANIA", TWCY_MAURITANIA},
									{"TWCY_MAURITIUS", TWCY_MAURITIUS},
									{"TWCY_MEXICO", TWCY_MEXICO},
									{"TWCY_MICRONESIA", TWCY_MICRONESIA},
									{"TWCY_MIQUELON", TWCY_MIQUELON},
									{"TWCY_MONACO", TWCY_MONACO},
									{"TWCY_MONGOLIA", TWCY_MONGOLIA},
									{"TWCY_MONTSERRAT", TWCY_MONTSERRAT},
									{"TWCY_MOROCCO", TWCY_MOROCCO},
									{"TWCY_MOZAMBIQUE", TWCY_MOZAMBIQUE},
									{"TWCY_NAMIBIA", TWCY_NAMIBIA},
									{"TWCY_NAURU", TWCY_NAURU},
									{"TWCY_NEPAL", TWCY_NEPAL},
									{"TWCY_NETHERLANDS", TWCY_NETHERLANDS},
									{"TWCY_NETHANTILLES", TWCY_NETHANTILLES},
									{"TWCY_NEVIS", TWCY_NEVIS},
									{"TWCY_NEWCALEDONIA", TWCY_NEWCALEDONIA},
									{"TWCY_NEWZEALAND", TWCY_NEWZEALAND},
									{"TWCY_NICARAGUA", TWCY_NICARAGUA},
									{"TWCY_NIGER", TWCY_NIGER},
									{"TWCY_NIGERIA", TWCY_NIGERIA},
									{"TWCY_NIUE", TWCY_NIUE},
									{"TWCY_NORFOLKI", TWCY_NORFOLKI},
									{"TWCY_NORWAY", TWCY_NORWAY},
									{"TWCY_OMAN", TWCY_OMAN},
									{"TWCY_PAKISTAN", TWCY_PAKISTAN},
									{"TWCY_PALAU", TWCY_PALAU},
									{"TWCY_PANAMA", TWCY_PANAMA},
									{"TWCY_PARAGUAY", TWCY_PARAGUAY},
									{"TWCY_PERU", TWCY_PERU},
									{"TWCY_PHILLIPPINES", TWCY_PHILLIPPINES},
									{"TWCY_PITCAIRNIS", TWCY_PITCAIRNIS},
									{"TWCY_PNEWGUINEA", TWCY_PNEWGUINEA},
									{"TWCY_POLAND", TWCY_POLAND},
									{"TWCY_PORTUGAL", TWCY_PORTUGAL},
									{"TWCY_QATAR", TWCY_QATAR},
									{"TWCY_REUNIONI", TWCY_REUNIONI},
									{"TWCY_ROMANIA", TWCY_ROMANIA},
									{"TWCY_RWANDA", TWCY_RWANDA},
									{"TWCY_SAIPAN", TWCY_SAIPAN},
									{"TWCY_SANMARINO", TWCY_SANMARINO},
									{"TWCY_SAOTOME", TWCY_SAOTOME},
									{"TWCY_SAUDIARABIA", TWCY_SAUDIARABIA},
									{"TWCY_SENEGAL", TWCY_SENEGAL},
									{"TWCY_SEYCHELLESIS", TWCY_SEYCHELLESIS},
									{"TWCY_SIERRALEONE", TWCY_SIERRALEONE},
									{"TWCY_SINGAPORE", TWCY_SINGAPORE},
									{"TWCY_SOLOMONIS", TWCY_SOLOMONIS},
									{"TWCY_SOMALI", TWCY_SOMALI},
									{"TWCY_SOUTHAFRICA", TWCY_SOUTHAFRICA},
									{"TWCY_SPAIN", TWCY_SPAIN},
									{"TWCY_SRILANKA", TWCY_SRILANKA},
									{"TWCY_STHELENA", TWCY_STHELENA},
									{"TWCY_STKITTS", TWCY_STKITTS},
									{"TWCY_STLUCIA", TWCY_STLUCIA},
									{"TWCY_STPIERRE", TWCY_STPIERRE},
									{"TWCY_STVINCENT", TWCY_STVINCENT},
									{"TWCY_SUDAN", TWCY_SUDAN},
									{"TWCY_SURINAME", TWCY_SURINAME},
									{"TWCY_SWAZILAND", TWCY_SWAZILAND},
									{"TWCY_SWEDEN", TWCY_SWEDEN},
									{"TWCY_SWITZERLAND", TWCY_SWITZERLAND},
									{"TWCY_SYRIA", TWCY_SYRIA},
									{"TWCY_TAIWAN", TWCY_TAIWAN},
									{"TWCY_TANZANIA", TWCY_TANZANIA},
									{"TWCY_THAILAND", TWCY_THAILAND},
									{"TWCY_TOBAGO", TWCY_TOBAGO},
									{"TWCY_TOGO", TWCY_TOGO},
									{"TWCY_TONGAIS", TWCY_TONGAIS},
									{"TWCY_TRINIDAD", TWCY_TRINIDAD},
									{"TWCY_TUNISIA", TWCY_TUNISIA},
									{"TWCY_TURKEY", TWCY_TURKEY},
									{"TWCY_TURKSCAICOS", TWCY_TURKSCAICOS},
									{"TWCY_TUVALU", TWCY_TUVALU},
									{"TWCY_UGANDA", TWCY_UGANDA},
									{"TWCY_USSR", TWCY_USSR},
									{"TWCY_UAEMIRATES", TWCY_UAEMIRATES},
									{"TWCY_UNITEDKINGDOM", TWCY_UNITEDKINGDOM},
									{"TWCY_USA", TWCY_USA},
									{"TWCY_URUGUAY", TWCY_URUGUAY},
									{"TWCY_VANUATU", TWCY_VANUATU},
									{"TWCY_VATICANCITY", TWCY_VATICANCITY},
									{"TWCY_VENEZUELA", TWCY_VENEZUELA},
									{"TWCY_WAKE", TWCY_WAKE},
									{"TWCY_WALLISIS", TWCY_WALLISIS},
									{"TWCY_WESTERNSAHARA", TWCY_WESTERNSAHARA},
									{"TWCY_WESTERNSAMOA", TWCY_WESTERNSAMOA},
									{"TWCY_YEMEN", TWCY_YEMEN},
									{"TWCY_YUGOSLAVIA", TWCY_YUGOSLAVIA},
									{"TWCY_ZAIRE", TWCY_ZAIRE},
									{"TWCY_ZAMBIA", TWCY_ZAMBIA},
									{"TWCY_ZIMBABWE", TWCY_ZIMBABWE}
								};

TABLEENTRY BitOrderType[MAX_BITORDERTYPE] =
								{
									{"TWBO_LSBFIRST", TWBO_LSBFIRST},
									{"TWBO_MSBFIRST", TWBO_MSBFIRST}
								};

TABLEENTRY FilterType[MAX_FILTERTYPE] =
								{
									{"TWFT_RED", TWFT_RED},
									{"TWFT_GREEN", TWFT_GREEN},
									{"TWFT_BLUE", TWFT_BLUE},
									{"TWFT_NONE", TWFT_NONE},
									{"TWFT_WHITE", TWFT_WHITE},
									{"TWFT_CYAN", TWFT_CYAN},
									{"TWFT_MAGENTA", TWFT_MAGENTA},
									{"TWFT_YELLOW", TWFT_YELLOW},
									{"TWFT_BLACK", TWFT_BLACK}
								};

TABLEENTRY LightPathType[MAX_LIGHTPATHTYPE] =								
								{
									{"TWLP_REFLECTIVE", TWLP_REFLECTIVE},
									{"TWLP_TRANSMISSIVE", TWLP_TRANSMISSIVE}
								};

TABLEENTRY LightSourceType[MAX_LIGHTSOURCETYPE] = 
								{
									{"TWLS_RED", TWLS_RED},
									{"TWLS_GREEN", TWLS_GREEN},
									{"TWLS_BLUE", TWLS_BLUE},
									{"TWLS_NONE", TWLS_NONE},
									{"TWLS_WHITE", TWLS_WHITE},
									{"TWLS_UV", TWLS_UV},
									{"TWLS_IR", TWLS_IR}
								};

TABLEENTRY OrientationType[MAX_ORIENTATIONTYPE] = 
								{
									{"TWOR_ROT0", TWOR_ROT0},
									{"TWOR_ROT90", TWOR_ROT90},
									{"TWOR_ROT180", TWOR_ROT180},
									{"TWOR_ROT270", TWOR_ROT270},
									{"TWOR_PORTRAIT", TWOR_PORTRAIT},
									{"TWOR_LANDSCAPE", TWOR_LANDSCAPE}
								};

TABLEENTRY PlanarChunkyType[MAX_PLANARCHUNKYTYPE] =
								{
									{"TWPC_CHUNKY", TWPC_CHUNKY},
									{"TWPC_PLANAR", TWPC_PLANAR}
								};

TABLEENTRY PixelFlavorType[MAX_PIXELFLAVORTYPE] =
								{
									{"TWPF_CHOCOLATE", TWPF_CHOCOLATE},
									{"TWPF_VANILLA", TWPF_VANILLA}
								};

TABLEENTRY SetupXferType[MAX_SETUPXFERTYPE] =
								{
									{"TWSX_NATIVE", TWSX_NATIVE},
									{"TWSX_FILE", TWSX_FILE},
									{"TWSX_MEMORY", TWSX_MEMORY}
								};

TABLEENTRY UnitsType[MAX_UNITSTYPE] = 
								{
									{"TWUN_INCHES", TWUN_INCHES},
									{"TWUN_CENTIMETERS", TWUN_CENTIMETERS},
									{"TWUN_PICAS", TWUN_PICAS},
									{"TWUN_POINTS", TWUN_POINTS},
									{"TWUN_TWIPS", TWUN_TWIPS},
									{"TWUN_PIXELS", TWUN_PIXELS}
								};

TABLEENTRY SupportedSizeType[MAX_SUPPORTEDSIZETYPE] = 
								{
									{"TWSS_NONE", TWSS_NONE},
									{"TWSS_A4LETTER", TWSS_A4LETTER},
									{"TWSS_B5LETTER", TWSS_B5LETTER},
									{"TWSS_USLETTER", TWSS_USLETTER},
									{"TWSS_USLEGAL", TWSS_USLEGAL},
									{"TWSS_A5", TWSS_A5},
									{"TWSS_B4", TWSS_B4},
									{"TWSS_B6", TWSS_B6},
									{"TWSS_USLEDGER", TWSS_USLEDGER},
									{"TWSS_USEXECUTIVE", TWSS_USEXECUTIVE},
									{"TWSS_A3", TWSS_A3},
									{"TWSS_B3", TWSS_B3},
									{"TWSS_A6", TWSS_A6},
									{"TWSS_C4", TWSS_C4},
									{"TWSS_C5", TWSS_C5},
									{"TWSS_C6", TWSS_C6}
								};

TABLEENTRY BitDepthReductionType[MAX_BITDEPTHREDUCTIONTYPE] = 
								{
									{"TWBR_THRESHOLD", TWBR_THRESHOLD},
									{"TWBR_HALFTONE", TWBR_HALFTONE},
									{"TWBR_CUSTHALFTONE", TWBR_CUSTHALFTONE},
									{"TWBR_DIFFUSION", TWBR_DIFFUSION}
								}; 

TABLEENTRY BoolType[MAX_BOOLTYPE] = 
								{
									{"FALSE", FALSE},
									{"TRUE", TRUE}
								};

TABLEENTRY DuplexType[MAX_DUPLEXTYPE] = 
								{
									{"TWDX_NONE", TWDX_NONE},
									{"TWDX_1PASSDUPLEX", TWDX_1PASSDUPLEX},
									{"TWDX_2PASSDUPLEX", TWDX_2PASSDUPLEX}
								};

TABLEENTRY JobControlType[MAX_JOBCONTROLTYPE] =
								{
									{"TWJC_NONE", TWJC_NONE},
									{"TWJC_JSIC", TWJC_JSIC},
									{"TWJC_JSIS", TWJC_JSIS},
									{"TWJC_JSXC", TWJC_JSXC},
									{"TWJC_JSXS", TWJC_JSXS}
								};

TABLECAP Caps[MAX_CAP] = 
	{
		{"CAP_AUTHOR", CAP_AUTHOR, NULL, 0, TWTY_STR128},
		{"CAP_AUTOFEED", CAP_AUTOFEED, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_AUTOSCAN", CAP_AUTOSCAN, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_CAPTION", CAP_CAPTION, NULL, 0, TWTY_STR255},
		{"CAP_CLEARPAGE", CAP_CLEARPAGE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_CUSTOMDSDATA", CAP_CUSTOMDSDATA, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_DEVICEONLINE", CAP_DEVICEONLINE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_DUPLEX", CAP_DUPLEX, &DuplexType[0], MAX_DUPLEXTYPE, TWTY_UINT16},
		{"CAP_DUPLEXENABLED", CAP_DUPLEXENABLED, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_ENABLEDSUIONLY", CAP_ENABLEDSUIONLY, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_ENDORSER", CAP_ENDORSER, NULL, 0, TWTY_UINT32},
		{"CAP_EXTENDEDCAPS", CAP_EXTENDEDCAPS, NULL, 0, TWTY_UINT16},
		{"CAP_FEEDERENABLED", CAP_FEEDERENABLED, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_FEEDERLOADED", CAP_FEEDERLOADED, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_FEEDPAGE", CAP_FEEDPAGE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_INDICATORS", CAP_INDICATORS, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_JOBCONTROL", CAP_JOBCONTROL, &JobControlType[0], MAX_JOBCONTROLTYPE, TWTY_UINT16},
		{"CAP_PAPERDETECTABLE", CAP_PAPERDETECTABLE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_REWINDPAGE", CAP_REWINDPAGE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_SUPPORTEDCAPS", CAP_SUPPORTEDCAPS, NULL, 0, TWTY_UINT16},
		{"CAP_THUMBNAILSENABLED", CAP_THUMBNAILSENABLED, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_TIMEDATE", CAP_TIMEDATE, NULL, 0, TWTY_STR32},
		{"CAP_UICONTROLLABLE", CAP_UICONTROLLABLE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"CAP_XFERCOUNT", CAP_XFERCOUNT, NULL, 0, TWTY_INT16},
		{"ICAP_AUTOBRIGHT", ICAP_AUTOBRIGHT, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"ICAP_BITDEPTH", ICAP_BITDEPTH, NULL, 0, TWTY_UINT16},
		{"ICAP_BITDEPTHREDUCTION", ICAP_BITDEPTHREDUCTION, &BitDepthReductionType[0], MAX_BITDEPTHREDUCTIONTYPE, TWTY_UINT16},
		{"ICAP_BITORDER", ICAP_BITORDER, &BitOrderType[0], MAX_BITORDERTYPE, TWTY_UINT16},
		{"ICAP_BITORDERCODES", ICAP_BITORDERCODES, NULL, 0, TWTY_UINT16},
		{"ICAP_BRIGHTNESS", ICAP_BRIGHTNESS, NULL, 0, TWTY_FIX32},
		{"ICAP_CCITTKFACTOR", ICAP_CCITTKFACTOR, NULL, 0, TWTY_UINT16},
		{"ICAP_COMPRESSION", ICAP_COMPRESSION, &CompressionType[0], MAX_COMPRESSIONTYPE, TWTY_UINT16},
		{"ICAP_CONTRAST", ICAP_CONTRAST, NULL, 0, TWTY_FIX32},
		{"ICAP_CUSTHALFTONE", ICAP_CUSTHALFTONE, NULL, 0, TWTY_UINT8},
		{"ICAP_EXPOSURETIME", ICAP_EXPOSURETIME, NULL, 0, TWTY_FIX32},
		{"ICAP_EXTIMAGEINFO", ICAP_EXTIMAGEINFO, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"ICAP_FILTER", ICAP_FILTER, &FilterType[0], MAX_FILTERTYPE, TWTY_UINT16},
		{"ICAP_FLASHUSED", ICAP_FLASHUSED, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"ICAP_FRAMES", ICAP_FRAMES, NULL, 0, TWTY_FRAME},
		{"ICAP_GAMMA", ICAP_GAMMA, NULL, 0, TWTY_FIX32},
		{"ICAP_HALFTONES", ICAP_HALFTONES, NULL, 0, TWTY_STR32},
		{"ICAP_HIGHLIGHT", ICAP_HIGHLIGHT, NULL, 0, TWTY_FIX32},
		{"ICAP_IMAGEDATASET", ICAP_IMAGEDATASET, NULL, 0, TWTY_UINT32},
		{"ICAP_IMAGEFILEFORMAT", ICAP_IMAGEFILEFORMAT, &FormatType[0], MAX_FORMATTYPE, TWTY_UINT16},
		{"ICAP_JPEGPIXELTYPE", ICAP_JPEGPIXELTYPE, NULL, 0, TWTY_UINT16},
		{"ICAP_LAMPSTATE", ICAP_LAMPSTATE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"ICAP_LIGHTPATH", ICAP_LIGHTPATH, &LightPathType[0], MAX_LIGHTPATHTYPE, TWTY_UINT16},
		{"ICAP_LIGHTSOURCE", ICAP_LIGHTSOURCE, &LightSourceType[0], MAX_LIGHTSOURCETYPE, TWTY_UINT16},
		{"ICAP_MAXFRAMES", ICAP_MAXFRAMES, NULL, 0, TWTY_UINT16},
		{"ICAP_MINIMUMHEIGHT", ICAP_MINIMUMHEIGHT, NULL, 0, TWTY_FIX32},
		{"ICAP_MINIMUMWIDTH", ICAP_MINIMUMWIDTH, NULL, 0, TWTY_FIX32},
		{"ICAP_ORIENTATION", ICAP_ORIENTATION, &OrientationType[0], MAX_ORIENTATIONTYPE, TWTY_UINT16},
		{"ICAP_PHYSICALHEIGHT", ICAP_PHYSICALHEIGHT, NULL, 0, TWTY_FIX32},
		{"ICAP_PHYSICALWIDTH", ICAP_PHYSICALWIDTH, NULL, 0, TWTY_FIX32},
		{"ICAP_PIXELFLAVOR", ICAP_PIXELFLAVOR, &PixelFlavorType[0], MAX_PIXELFLAVORTYPE, TWTY_UINT16},
		{"ICAP_PIXELFLAVORCODES", ICAP_PIXELFLAVORCODES, &PixelFlavorType[0], MAX_PIXELFLAVORTYPE, TWTY_UINT16},
		{"ICAP_PIXELTYPE", ICAP_PIXELTYPE, &PixelType[0], MAX_PIXELTYPE, TWTY_UINT16},
		{"ICAP_PLANARCHUNKY", ICAP_PLANARCHUNKY, &PlanarChunkyType[0], MAX_PLANARCHUNKYTYPE, TWTY_UINT16},
		{"ICAP_ROTATION", ICAP_ROTATION, NULL, 0, TWTY_FIX32},
		{"ICAP_SHADOW", ICAP_SHADOW, NULL, 0, TWTY_FIX32},
		{"ICAP_SUPPORTEDSIZES", ICAP_SUPPORTEDSIZES, &SupportedSizeType[0], MAX_SUPPORTEDSIZETYPE, TWTY_UINT16},
		{"ICAP_THRESHOLD", ICAP_THRESHOLD, NULL, 0, TWTY_FIX32},
		{"ICAP_TILES", ICAP_TILES, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"ICAP_TIMEFILL", ICAP_TIMEFILL, NULL, 0, TWTY_UINT16},
		{"ICAP_UNDEFINEDIMAGESIZE", ICAP_UNDEFINEDIMAGESIZE, &BoolType[0], MAX_BOOLTYPE, TWTY_BOOL},
		{"ICAP_UNITS", ICAP_UNITS, &UnitsType[0], MAX_UNITSTYPE, TWTY_UINT16},
		{"ICAP_XFERMECH", ICAP_XFERMECH, &SetupXferType[0], MAX_SETUPXFERTYPE, TWTY_UINT16},
		{"ICAP_XNATIVERESOLUTION", ICAP_XNATIVERESOLUTION, NULL, 0, TWTY_FIX32},
		{"ICAP_XRESOLUTION", ICAP_XRESOLUTION, NULL, 0, TWTY_FIX32},
		{"ICAP_XSCALING", ICAP_XSCALING, NULL, 0, TWTY_FIX32},
		{"ICAP_YNATIVERESOLUTION", ICAP_YNATIVERESOLUTION, NULL, 0, TWTY_FIX32},
		{"ICAP_YRESOLUTION", ICAP_YRESOLUTION, NULL, 0, TWTY_FIX32},
		{"ICAP_YSCALING", ICAP_YSCALING, NULL, 0, TWTY_FIX32}
	};

TABLEENTRY Types[MAX_TYPES] =
								{
									{"TWTY_INT8", TWTY_INT8},
									{"TWTY_INT16", TWTY_INT16},
									{"TWTY_INT32", TWTY_INT32},
									{"TWTY_UINT8", TWTY_UINT8},
									{"TWTY_UINT16", TWTY_UINT16},
									{"TWTY_UINT32", TWTY_UINT32},
									{"TWTY_BOOL", TWTY_BOOL},
									{"TWTY_FIX32", TWTY_FIX32},
									{"TWTY_FRAME", TWTY_FRAME},
									{"TWTY_STR32", TWTY_STR32},
									{"TWTY_STR64", TWTY_STR64},
									{"TWTY_STR128", TWTY_STR128},
									{"TWTY_STR255", TWTY_STR255}
								};

TABLEENTRY TypesRange[MAX_TYPESRANGE] =
								{
									{"TWTY_INT8", TWTY_INT8},
									{"TWTY_INT16", TWTY_INT16},
									{"TWTY_INT32", TWTY_INT32},
									{"TWTY_UINT8", TWTY_UINT8},
									{"TWTY_UINT16", TWTY_UINT16},
									{"TWTY_UINT32", TWTY_UINT32},
									{"TWTY_BOOL", TWTY_BOOL},
									{"TWTY_FIX32", TWTY_FIX32},
								};

TABLEENTRY ReturnCode[MAX_RETURNCODE] =
								{
									{"TWRC_SUCCESS", TWRC_SUCCESS},
									{"TWRC_FAILURE", TWRC_FAILURE},
									{"TWRC_CHECKSTATUS", TWRC_CHECKSTATUS},
									{"TWRC_CANCEL", TWRC_CANCEL},
									{"TWRC_DSEVENT", TWRC_DSEVENT},
									{"TWRC_NOTDSEVENT", TWRC_NOTDSEVENT},
									{"TWRC_XFERDONE", TWRC_XFERDONE},
									{"TWRC_ENDOFLIST", TWRC_ENDOFLIST},
									{"TWRC_INFONOTSUPPORTED", TWRC_INFONOTSUPPORTED},
									{"TWRC_DATANOTAVAILABLE", TWRC_DATANOTAVAILABLE}
								};

TABLEENTRY ConditionCode[MAX_CONDITIONCODE]	=
								{
									{"TWCC_SUCCESS", TWCC_SUCCESS},
									{"TWCC_BUMMER", TWCC_BUMMER},
									{"TWCC_LOWMEMORY", TWCC_LOWMEMORY},
									{"TWCC_NODS", TWCC_NODS},
									{"TWCC_MAXCONNECTIONS", TWCC_MAXCONNECTIONS},
									{"TWCC_OPERATIONERROR", TWCC_OPERATIONERROR},
									{"TWCC_BADCAP", TWCC_BADCAP},
									{"TWCC_BADPROTOCOL", TWCC_BADPROTOCOL},
									{"TWCC_BADVALUE", TWCC_BADVALUE},
									{"TWCC_SEQERROR", TWCC_SEQERROR},
									{"TWCC_BADDEST", TWCC_BADDEST},
									{"TWCC_CAPUNSUPPORTED", TWCC_CAPUNSUPPORTED},
									{"TWCC_CAPBADOPERATION", TWCC_CAPBADOPERATION},
									{"TWCC_CAPSEQERROR", TWCC_CAPSEQERROR}
								};

char *gszOneValueStructure[ONEVALUEFIELDS] =
{
	"ItemType=",
	"Item="
};
char *gszFrameStructure[FRAMEFIELDS] =
{
	"ItemType=",
	"Frame.Left=",
	"Frame.Top=",
	"Frame.Right=",
	"Frame.Bottom="
};

char *gszRangeStructure[RANGEFIELDS] =
{
	"ItemType=",
	"MinValue=",
	"MaxValue=",
	"StepSize=",
	"DefaultValue=",
	"CurrentValue="
};

char *gszEnumerationStructure[ENUMERATIONFIELDS] =
{
	"ItemType=",
	"NumItems=",
	"CurrentIndex=",
	"DefaultIndex=",
	"ItemList="
};

char *gszArrayStructure[ARRAYFIELDS] =
{
	"ItemType=",
	"NumItems=",
	"ItemList="
};


char *gszMessageStructure[MESSAGEFIELDS] =
{
	"ItemType=",
	"Value="
};

char *gszDatCapabilityStructure[DAT_CAPABILITYFIELDS] = 
{
	"Cap=",
	"ConType=",
	"hContainer="
};


char *gszDatCustomDSData[DAT_CUSTOMDSDATAFIELDS] = 
{
	"InfoLength=",
	"hData="
};

char *gszDatCieColorStructure[DAT_CIECOLORFIELDS] = 
{
	"ColorSpace=",
	"LowEndian=",
	"DeviceDependent=",
	"VersionNumber=",
	"StageABC.Decode.StartIn=",
	"StageABC.Decode.BreakIn=",
	"StageABC.Decode.EndIn=",
	"StageABC.Decode.StartOut=",
	"StageABC.Decode.BreakOut=",
	"StageABC.Decode.EndOut=",
	"StageABC.Decode.Gamma=",
	"StageABC.Decode.SampleCount=",
	"StageABC.Mix=",
	"StageLMN.Decode.StartIn=",
	"StageLMN.Decode.BreakIn=",
	"StageLMN.Decode.EndIn=",
	"StageLMN.Decode.StartOut=",
	"StageLMN.Decode.BreakOut=",
	"StageLMN.Decode.EndOut=",
	"StageLMN.Decode.Gamma=",
	"StageLMN.Decode.SampleCount=",
	"StageLMN.Mix=",
	"WhitePoint.X=",
	"WhitePoint.Y=",
	"WhitePoint.Z=",
	"BlackPoint.X=",
	"BlackPoint.Y=",
	"BlackPoint.Z=",
	"WhitePaper.X=",
	"WhitePaper.Y=",
	"WhitePaper.Z=",
	"BlackInk.X=",
	"BlackInk.Y=",
	"BlackInk.Z=",
	"Samples="
};

char *gszDatEventStructure[DAT_EVENTFIELDS] = 
{
	"pEvent=",
	"TWMessage="
};

char *gszDatExtImageInfo[DAT_EXTIMAGEINFOFIELDS] = 
{
	"NumInfos=",
	"Info="
};

char *gszDatGrayResponseStructure[DAT_GRAYRESPONSEFIELDS] = 
{
	"Response="
};

char *gszDatIdentityStructure[DAT_IDENTITYFIELDS] = 
{
	"Id=",
	"Version.MajorNum=",
	"Version.MinorNum=",
	"Version.Language=",
	"Version.Country=",
	"Version.Info=",
	"ProtocolMajor=",
	"ProtocolMinor=",
	"SupportedGroups=",
	"Manufacturer=",
	"ProuctFamily=",
	"ProductName="
};

char *gszDatImageInfoStructure[DAT_IMAGEINFOFIELDS] =
{
	"XResolution=",
	"YResolution=",
	"ImageWidth=",
	"ImageLength=",
	"SamplesPerPixel=",
	"BitsPerSample[0]=",
	"BitsPerSample[1]=",
	"BitsPerSample[2]=",
	"BitsPerSample[3]=",
	"BitsPerSample[4]=",
	"BitsPerSample[5]=",
	"BitsPerSample[6]=",
	"BitsPerSample[7]=",
	"BitsPerPixel=",
	"Planar=",
	"PixelType=",
	"Compression="
};

char *gszDatImageLayoutStructure[DAT_IMAGELAYOUTFIELDS] =
{
	"Frame.Left=",
	"Frame.Top=",
	"Frame.Right=",
	"Frame.Bottom=",
	"DocumentNumber=",
	"PageNumber=",
	"FrameNumber="
};

char *gszDatImageMemXferStructure[DAT_IMAGEMEMXFERFIELDS] =
{
	"Compression=",	
	"BytesPerRow=",	
	"Columns=",	
	"Rows=",	
	"XOffset=",	
	"YOffset=",	
	"BytesWritten=",	
	"Memory.Flags=",	
	"Memory.Length=",	
	"Memory.TheMem(size)="
};

char *gszDatImageNativeXferStructure[DAT_IMAGENATIVEXFERFIELDS] =
{
	"Dib(size)="
};

char *gszDatJPEGCompressionStructure[DAT_JPEGCOMPRESSIONFIELDS] =
{
	"ColorSpace=",
	"SubSampling=",
	"NumComponents=",
	"RestartFrequency=",
	"QuantMap=",
	"QuantTable=",
	"HuffmanMap=",
	"HuffmanTW=",
	"HuffmanAC="
};

char *gszDatPalette8Structure[DAT_PALETTE8FIELDS] =
{
	"NumColors=",
	"PaletteType=",
	"Colors="
};

char *gszDatPendingXfersStructure[DAT_PENDINGXFERSFIELDS] =
{
	"Count=",
	"Reserved="
};

char *gszDatRGBResponseStructure[DAT_RGBRESPONSEFIELDS] =
{
	"Response="
};

char *gszDatSetupFileXferStructure[DAT_SETUPFILEXFERFIELDS] =
{
	"FileName=",
	"Format=",
	"VRefNum="
};

char *gszDatSetupMemXferStructure[DAT_SETUPMEMXFERFIELDS] =
{
	"MinBufSize=",
	"MaxBufSize=",
	"Preferred="
};

char *gszDatStatusStructure[DAT_STATUSFIELDS] =
{
	"conditionCode=",
	"Reserved="
};

char *gszDatUserInterfaceStructure[DAT_USERINTERFACEFIELDS] =
{
	"ShowUI=",
	"ModalUI="
};

char *gszDatXferGroupStructure[DAT_XFERGROUPFIELDS] =
{
	"Groups="
};

TABLEDATSTRUCT DataStructure[MAX_DATASTRUCTURE] = 
{
	{"TWON_ONEVALUE", gszOneValueStructure,ONEVALUEFIELDS},
	{"TWON_ONEVALUE_FRAME", gszFrameStructure, FRAMEFIELDS},
	{"TWON_RANGE", gszRangeStructure, RANGEFIELDS},
	{"TWON_ENUMERATION", gszEnumerationStructure, ENUMERATIONFIELDS},
	{"TWON_ARRAY", gszArrayStructure, ARRAYFIELDS},
	{"MSG_GETCURRENT",gszMessageStructure, MESSAGEFIELDS},
	{"MSG_GETDEFAULT",gszMessageStructure, MESSAGEFIELDS},
	{"MSG_RESET",gszMessageStructure, MESSAGEFIELDS},
	{"MSG_QUERYSUPPORT", gszOneValueStructure,ONEVALUEFIELDS},
	{"DAT_CAPABILITY", gszDatCapabilityStructure, DAT_CAPABILITYFIELDS},
	{"DAT_CUSTOMDSDATA", gszDatCustomDSData, DAT_CUSTOMDSDATAFIELDS},
	{"DAT_CIECOLOR", gszDatCieColorStructure, DAT_CIECOLORFIELDS},
	{"DAT_EVENT", gszDatEventStructure, DAT_EVENTFIELDS},
	{"DAT_EXTIMAGEINFO", gszDatExtImageInfo, DAT_EXTIMAGEINFOFIELDS},
	{"DAT_GRAYRESPONSE", gszDatGrayResponseStructure, DAT_GRAYRESPONSEFIELDS},
	{"DAT_IDENTITY", gszDatIdentityStructure, DAT_IDENTITYFIELDS},
	{"DAT_IMAGEINFO", gszDatImageInfoStructure, DAT_IMAGEINFOFIELDS},
	{"DAT_IMAGELAYOUT", gszDatImageLayoutStructure, DAT_IMAGELAYOUTFIELDS},
	{"DAT_IMAGEMEMXFER", gszDatImageMemXferStructure,DAT_IMAGEMEMXFERFIELDS},
	{"DAT_IMAGENATIVEXFER", gszDatImageNativeXferStructure, DAT_IMAGENATIVEXFERFIELDS},
	{"DAT_JPEGCOMPRESSION", gszDatJPEGCompressionStructure, DAT_JPEGCOMPRESSIONFIELDS},
	{"DAT_PALETTE8", gszDatPalette8Structure, DAT_PALETTE8FIELDS},
	{"DAT_PENDINGXFERS", gszDatPendingXfersStructure, DAT_PENDINGXFERSFIELDS},
	{"DAT_RGBRESPONSE", gszDatRGBResponseStructure, DAT_RGBRESPONSEFIELDS},
	{"DAT_SETUPFILEXFER", gszDatSetupFileXferStructure, DAT_SETUPFILEXFERFIELDS},
	{"DAT_SETUPMEMXFER", gszDatSetupMemXferStructure, DAT_SETUPMEMXFERFIELDS},
	{"DAT_STATUS", gszDatStatusStructure, DAT_STATUSFIELDS},
	{"DAT_USERINTERFACE", gszDatUserInterfaceStructure, DAT_USERINTERFACEFIELDS},
	{"DAT_XFERGROUP", gszDatXferGroupStructure, DAT_XFERGROUPFIELDS}
};