#pragma once

#include SYSTEM

#include <stdio.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <fstream>
#include <process.h>

#include <D3D9.h>

extern "C"
{
#include <libavutil/opt.h>
#include <libavutil/time.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

#include "WinMM\\winmm.h"

#include "Exec\\Bio4_Flag.h"
#include "Dll\\inject.h"
#include "Exec\\bio4pc_print.h"
#include "Exec\\bio4pc_func.h"
#include "Exec\\bio4pc_exe.h"
#include "Exec\\bio4pc_hwnd.h"
#include "Exec\\bio4pc_dx9.h"
#include "Exec\\bio4pc_screen.h"
//#include "Exec\\bio4pc_video.h"
#include "Exec\\bio4pc_debug.h"
#include "Exec\\bio4pc_config.h"
#include "Exec\\bio4pc_av.h"

//#include "7z\\7zCrc.h"

extern System_File ISystem_File, * File;
extern System_Text ISystem_Text, * Text;
extern Resident_Evil_4_PC_AV IResident_Evil_4_PC_AV, * Bio4Movie;

extern CHAR* ModuleDir;
