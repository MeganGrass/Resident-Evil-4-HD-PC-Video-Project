#pragma once

extern CHAR* VideoFilename;
extern BOOL UseSofdecVideo;
extern BOOL OptimizeSofdec;
extern BOOL ForceVideoSoftware;

extern BOOL AutoSkipVideos;

extern UINT WindowWidth;
extern UINT WindowHeight;

extern UINT* Sofdec;

UINT initSub0(CHAR* Filename, UINT Flag);
VOID MovieStartWait(VOID);
VOID FinishMovie(VOID);
CHAR IsAliveEvt(int param_1, CHAR* param_2, CHAR* param_3, int* param_4, int param_5);