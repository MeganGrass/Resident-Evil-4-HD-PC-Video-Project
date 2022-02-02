
#include "..\\dllmain.h"
#include <timeapi.h>

// File
CHAR* VideoFilename;
BOOL UseSofdecVideo = FALSE;
BOOL OptimizeSofdec = FALSE;
BOOL ForceVideoSoftware = FALSE;

BOOL AutoSkipVideos = TRUE;

UINT WindowWidth;
UINT WindowHeight;

UINT* Sofdec;

// Hardware Playback
extern VOID OpenVideoAMD(VOID);
extern VOID OpenVideoNvidia(VOID);

// Software Playback
LPDIRECT3DSURFACE9 g_pDirectSurface9;
LPDIRECT3DSURFACE9 g_pBackBuffer;
static HWND g_pPlayWnd = NULL;
static AVFormatContext* g_pAvFmtCtx = NULL;
static AVCodecContext* g_pAvCodecCtx = NULL;
static int g_VideoIndex = -1;
static AVCodec* g_pAvCodec = NULL;
DWORD WINAPI VideoRenderThread(LPVOID p);

VOID OpenVideoSoftware(VOID) {

	// Initialize Direct-X
	pDevice = GetDx9Device();
	g_pPlayWnd = GetDx9Window();
	g_pDirectSurface9 = *pdx9Surface;
	g_pBackBuffer = *pBackBufferSurface;
	pDevice->SetSoftwareVertexProcessing(OFF);
	WindowWidth = GetScreenWidth();
	WindowHeight = GetScreenHeight();
	if (FAILED(pDevice->CreateOffscreenPlainSurface(WindowWidth, WindowHeight, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &g_pDirectSurface9, NULL))) { OSReport("CreateOffscreenPlainSurface error\n"); goto OpenVideoSoftwareComplete; }

	// Initialize FFmpeg
	g_pAvFmtCtx = avformat_alloc_context();
	if (avformat_open_input(&g_pAvFmtCtx, VideoFilename, NULL, NULL) < 0) { OSReport("avformat_open_input error\n"); goto OpenVideoSoftwareComplete; }
	if (avformat_find_stream_info(g_pAvFmtCtx, NULL) < 0) { OSReport("avformat_find_stream_info error\n"); goto OpenVideoSoftwareComplete; }
	for (UINT i = 0; i < g_pAvFmtCtx->nb_streams; i++)
	{
		if (g_pAvFmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) { g_VideoIndex = i; }
	}

	//
	g_pAvCodecCtx = avcodec_alloc_context3(NULL);
	if (avcodec_parameters_to_context(g_pAvCodecCtx, g_pAvFmtCtx->streams[g_VideoIndex]->codecpar) < 0) { OSReport("avcodec_parameters_to_context error\n"); goto OpenVideoSoftwareComplete; }
	g_pAvCodec = avcodec_find_decoder(g_pAvCodecCtx->codec_id);
	if (g_pAvCodec == NULL) { OSReport("avcodec_find_decoder error\n"); goto OpenVideoSoftwareComplete; }
	if (avcodec_open2(g_pAvCodecCtx, g_pAvCodec, NULL) < 0) { OSReport("avcodec_open2 error\n"); goto OpenVideoSoftwareComplete; }

	// A/V Playback
	LPDWORD VideoThreadId = NULL;
	HANDLE VideoThread = CreateThread(NULL, NULL, VideoRenderThread, NULL, NULL, VideoThreadId);
	if (VideoThread != NULL) {
		WaitForSingleObject(VideoThread, INFINITE);
		CloseHandle(VideoThread);
	}

	// Cleanup
	avformat_close_input(&g_pAvFmtCtx);
	avformat_free_context(g_pAvFmtCtx);
	avcodec_free_context(&g_pAvCodecCtx);

	// Complete
	OpenVideoSoftwareComplete:
	if ((*Sofdec & 0x400) == 0) {
		OSReport("Signaling task 0 from Software Video\n");
		TaskSignal(0);
	}
	if ((*Sofdec & 0x200) == 0) {
		OSReport("Exiting from Software Video task\n");
		TaskExit();
	}

}
DWORD WINAPI VideoRenderThread(LPVOID p) {

	//
	INT ret = NULL;
	RECT pRect = { NULL };
	SetRect(&pRect, 0, 0, WindowWidth, WindowHeight);
	D3DLOCKED_RECT d3d_rect = { NULL };

	//
	AVPacket* pkt = av_packet_alloc();
	AVFrame* pFrame = av_frame_alloc();
	AVFrame* pFrameYUV = av_frame_alloc();
	SwsContext* img_convert_ctx = NULL;

	// 
	static DWORD LastFrameTime = 0;
	DWORD FPSLimit = 60;

	while (true) {
		// Keypad exit?
		if ((*&pExecutable[0x00c63020 - EXE_BASE] & 0x2000) != 0 (*&pExecutable[0x00c62f10 - EXE_BASE] & 0x20000000) != 0) {
			*Sofdec = *Sofdec | 0x20;
			break;
		}
		ret = av_read_frame(g_pAvFmtCtx, pkt);
		if (ret == AVERROR_EOF) { break; }
		else if (ret < 0) { break; }
		else
		{
			if (pkt->stream_index == g_VideoIndex)
			{
				if (avcodec_send_packet(g_pAvCodecCtx, pkt) == 0)
				{
					if (avcodec_receive_frame(g_pAvCodecCtx, pFrame) == 0)
					{
						//
						sws_freeContext(img_convert_ctx);
						img_convert_ctx = sws_getContext(
							g_pAvCodecCtx->width, g_pAvCodecCtx->height, g_pAvCodecCtx->pix_fmt,
							WindowWidth, WindowHeight, AV_PIX_FMT_RGB32, SWS_POINT, NULL, NULL, NULL);

						//
						g_pDirectSurface9->LockRect(&d3d_rect, nullptr, D3DLOCK_DISCARD);// D3DLOCK_DISCARD);
						pFrameYUV->data[0] = (uint8_t*)d3d_rect.pBits;
						pFrameYUV->linesize[0] = d3d_rect.Pitch;
						sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, g_pAvCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
						g_pDirectSurface9->UnlockRect();

						//
						pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
						pDevice->BeginScene();
						if (g_pBackBuffer)
						{
							g_pBackBuffer->Release();
							g_pBackBuffer = NULL;
						}
						pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pBackBuffer);
						GetClientRect(g_pPlayWnd, &pRect);
						pDevice->StretchRect(g_pDirectSurface9, NULL, g_pBackBuffer, &pRect, D3DTEXF_NONE);
						pDevice->EndScene();
						pDevice->Present(NULL, NULL, NULL, NULL);

						// VSync
						ADXM_WaitVsync();
						// ADXM_ExecMain();
						DWORD currentTime = timeGetTime();
						if ((currentTime - LastFrameTime) < (1000 / FPSLimit))
						{
							Sleep(currentTime - LastFrameTime);
						}
						LastFrameTime = currentTime;
					}
				}
			}

			// Cleanup
			//av_packet_unref(pkt);
		}
	}

	// Cleanup
	av_frame_free(&pFrame);
	av_frame_free(&pFrameYUV);
	av_packet_free(&pkt);

	//
	//TaskSleep(1);
	_endthreadex(0);
	return 0;
}

VOID InitWork(VOID) {
	//snprintf((CHAR*)*&Sofdec[0x64], 0x20, VideoFilename);
	memcpy_s(&Sofdec[0x64], 0x20, VideoFilename, 0x20);
	*&Sofdec[0x60] = *&pG[0x5C];
	if ((*Sofdec & 0x400) == 0) {
		*&pG[0x5C] = 0xffffffff;
	}
	*&Sofdec[0x61] = *&pG[0x16];
	if ((*Sofdec & 0x400) == 0) {
		*&pG[0x15] = *&pG[0x15] | 0x100000;
	}
}
VOID InitApp(VOID) {

	CHAR* pcVar2 = nullptr;
	UINT uVar4 = NULL;
	UINT puVar3 = NULL;
	ULONG* Dvd = (ULONG*)&pExecutable[0x00c53118 - EXE_BASE];
	ULONG* cMes = (ULONG*)&pExecutable[0x00c17830 - EXE_BASE];

	VOID* pMemclr = (VOID*)&pExecutable[0x00c62fd0 - EXE_BASE];

	memclr_asm(pMemclr, 200);
	*&pExecutable[0x00c6cd38 - EXE_BASE] = 1;
	//pMemclr = (VOID*)*&Sofdec[0x02];
	memclr_asm(&Sofdec[0x02], 0x170);
	*&Sofdec[0x02] = 0;
	*&Sofdec[0x4D] = 0x100;

	if ((*Sofdec & 0x400) == 0) {
		if (*&pSys[8] == 0x06) {
			uVar4 = 0x377;
			pcVar2 = "etc/movie_cht.das";
		}
		else if(*&pSys[8] == 0x0A) {
			uVar4 = 0x37b;
			pcVar2 = "etc/movie_chs.das";
		}
		else {
			uVar4 = 0x37f;
			pcVar2 = "etc/movie.das";
		}
		uVar4 = DvdReadN(pcVar2, 0, 0, 0, 0, 0x8005, "bio4\\bio4pc_video.cpp", uVar4);
		cDvd_ReadCheck(&Dvd, uVar4, 0x00, 0x00, *&Sofdec);
		*&Sofdec[0x6F] = *Sofdec;
		puVar3 = 0xa000006;
		FUN_00958bb0(&puVar3, 0);
		/*UCHAR cVar1 = *&pSys[8];
		OSReport("MessageControl_setupFont...\n");
		if (((cVar1 == 0x00) || (cVar1 == 0x06)) || (cVar1 == 0x0A)) {
			//MessageControl_setupFont(&cMes, 0x1c, 0x1c, (INT*)*&Sofdec[0x6F], 2);
			MessageControl_setupFont(*&cMes, 0x1c, 0x1c, (INT*)*&Sofdec[0x74], 2);
		}
		OSReport("MessageControl_setLayout...\n");
		*&pExecutable[0x00c71594 - EXE_BASE] = *&Sofdec[0x73];
		*&pExecutable[0x00c715a8 - EXE_BASE] = 0;
		MessageControl_setLayout(*&cMes, 0, 0);*/
	}

	*&Sofdec[0x0D] = NULL;	// Width
	*&Sofdec[0x0E] = NULL;	// Height

	if ((*Sofdec & 0x400) == 0) {
		*&pG[0x15] = *&pG[0x15] | 0x400;
		return;
	}

	*&pG[0x16] = 0xffffffff;
	*&pG[0x16] = *&pG[0x16] & 0xfffeffff;
	*&pG[0x16] = *&pG[0x16] & 0xffffdfff;
	*&pG[0x16] = *&pG[0x16] & 0xffffefff;
	*&pG[0x16] = *&pG[0x16] & 0xfffff7ff;
	*&pG[0x5C] = 0xffffffff;
	*&pG[0x5C] = *&pG[0x5C] & 0xbfffffff;
	*&pG[0x5C] = *&pG[0x5C] & 0xff7fffff;
	*&pG[0x5C] = *&pG[0x5C] & 0xffffbfff;
	*&pG[0x5C] = *&pG[0x5C] & 0xfffffbff;
	*&pG[0x5C] = *&pG[0x5C] & 0xfffffeff;
	*&pG[0x5C] = *&pG[0x5C] & 0xffffffbf;

}
VOID StartApp(VOID) {
	memset(&Sofdec[0x0B], 0, 0x54);
	*&Sofdec[0x13] = 0;
	*&Sofdec[0x0C] = 10000000;
	*&Sofdec[0x0F] = 4;
	*&Sofdec[0x0D] = *&Sofdec[0x5E];				// Width
	*&Sofdec[0x0E] = *(SHORT*)&Sofdec[0x5E] + 2;	// Height
	*&Sofdec[0x10] = 2;
	*&Sofdec[0x12] = NULL;							// _Size;
	*&Sofdec[0x11] = *&pExecutable[0x00c65cac - EXE_BASE];	// _Dst
}
VOID InitSync(VOID) {

	int iVar1;

	if (Screen->Width != 512.0) {
		systemVISetBlack(1);
	}

	*&Sofdec[0x5F] = 1;

	iVar1 = GetSystemVcnt();
	*(UCHAR*)&Sofdec[0x63] = (UCHAR)iVar1;

	*&Sofdec[0x64] = 0;
	if (Screen->Width != 512.0) {
		*(UCHAR*)&Sofdec[0x64] = 1;
		//ScreenReSize(0x200, 0x1c0);
	}

	//cSofdec::clrTexMem((MwsfdCrePrm*)&DAT_00c6cce0);

	*&pExecutable[0x00c6cd44 - EXE_BASE] = 1;

	//OSReport("Movie Play : %s \n", *&Sofdec[0x4D]);

}
CHAR* ParseFilename(CHAR* Filename) {

	CHAR* Namebase = File->GetNamebase(Filename);
	return File->Get("%s\\movie\\%s.mp4", ModuleDir, Namebase);

}
UINT initSub0(CHAR* Filename, UINT Flag) {

	INT TaskLevel = NULL;
	//VideoFilename = File->Get("%s", Filename);
	OSReport("Attempting Video Software Playback...\n");
	VideoFilename = ParseFilename(Filename);
	OSReport("Video: %s\n", VideoFilename);

	// Global
	if ((*&pG[0x1407] & 0x10000000) != 0) { return *pG & 0xffffff00; }

	// Flag
	*Sofdec = (Flag | 1);

	// Initialize
	//InitWork();
	*&Sofdec[0x60] = *&pG[0x5C];
	*&Sofdec[0x61] = *&pG[0x16];
	//InitApp();
	StartApp();
	*&pG[0x1407] |= 0x10000000;
	InitSync();

	// 
	*&pG[0x1407] = *&pG[0x1407] | 0x4000000;

	if (AutoSkipVideos == TRUE) {
		goto SkipVideoPlayback;
	}

	// Playback
	if ((Flag & 0x200) == 0) {
		if ((Flag & 0x400) == 0) {
			OSReport("Suspend task was demanded..!\n");
			TaskSuspend(0);
		}
		if ((*Sofdec & 0x400) == 0) {
			TaskLevel = 1;
			OSReport("Executing video in task level %d\n", TaskLevel);
			TaskExec(TaskLevel, OpenVideoSoftware, Sofdec);
		}
		else {
			TaskLevel = 3;
			OSReport("Executing video in task level %d\n", TaskLevel);
			UINT uVar1 = TaskStatus(TaskLevel);
			if ((CHAR)uVar1 != '\0') {
				*&pExecutable[0x00c6cd48 - EXE_BASE] = 0;
				*&pExecutable[0x00c58f88 - EXE_BASE] = 0;
				*&pExecutable[0x00c58fb0 - EXE_BASE] = 0;
				*&pExecutable[0x00c58fd8 - EXE_BASE] = 0;
				*&pExecutable[0x00c59000 - EXE_BASE] = 0;
				TaskKill1(TaskLevel);
				OSReport("Had to kill task level %d first...\n", TaskLevel);
			}
			TaskExec(TaskLevel, OpenVideoSoftware, Sofdec);
		}
	}
	else {
		OSReport("Executing video without TaskExec\n");
		OpenVideoSoftware();
	}

	// Software
	ForceVideoSoftware = TRUE;
	if (ForceVideoSoftware == TRUE) { OSReport("...Software Playback Complete!\n"); }
	else {

		// Vendor ID
		D3DADAPTER_IDENTIFIER9 AdapterId;
		LPDIRECT3D9 pD3D = GetDx9Interface();
		pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, NULL, &AdapterId);

		// Hardware
		switch (AdapterId.VendorId)
		{
		case 0x10DE:	// Nvidia
			OSReport("Attempting Video Hardware Playback via Nvidia...\r\n");
			TaskExec(TaskLevel, OpenVideoNvidia, NULL);
			break;
		case 0x1002:	// AMD
		case 0x1022:
			OSReport("Attempting Video Hardware Playback via AMD...\r\n");
			TaskExec(TaskLevel, OpenVideoAMD, NULL);
			break;
		case 0x163C:	// Intel
		case 0x8086:
		case 0x8087:
			OSReport("Attempting Video Hardware Playback via Intel...\r\n");
			TaskExec(TaskLevel, OpenVideoSoftware, NULL);
			break;
		default:
			OSReport("Attempting Video Software Playback...\r\n");
			OSReport("Unknown Graphics Vendor ID: %04X\r\n", AdapterId.VendorId);
			TaskExec(TaskLevel, OpenVideoSoftware, NULL);
		}
	}

	// Complete
	SkipVideoPlayback:
	if ((*Sofdec & 0x400) == 0) {
		*&pG[0x15] = *&pG[0x15] & 0xfffffbff;
		*&Sofdec[0x20] = 0x02;
	}
	if ((*Sofdec & 0x400) == 0) {
		FinishMovie();
	}
	*&pG[0x1407] = *&pG[0x1407] & 0xfbffffff;

	/**&pG[0x54] = *&pG[0x54] | 0x400;
	*&pG[0x5028] = *&pG[0x5028] | 0x1000;
	*&pG[0x5028] = *&pG[0x5028] & 0xfffffbff;
	*&pG[0x5024] = *&pG[0x5024] & 0xfff7ffff;
	*&pG[0x5024] = *&pG[0x5024] & 0xfffeffff;*/

	/* 
	if (((*Sofdec & 0x400) == 0) &&
		(*&pG[0x54] = *&pG[0x54] & 0xffefffff, (*Sofdec & 0x2000) == 0)) {
		*&pG[0x54] = *&pG[0x54] & 0xfffffbff;
	}
	if ((*Sofdec >> 8 & 1) == 0) {
		systemVISetBlack(0);
	}*/

	// Complete
	return 1;
}
VOID MovieStartWait(VOID) {
	OSReport("...made it to MovieStartWait()\n");
	__asm {ret}
}
VOID FinishMovie(VOID) {

	UCHAR cVar1;
	int iVar2;

	ULONG* cMes = (ULONG*)&pExecutable[0x00c17830 - EXE_BASE];

	if ((*&pG[0x1407] & 0x10000000) != 0) {
		OSReport("...made it to FinishMovie()\n");

		if ((*Sofdec & 0x400) == 0) {
			systemVISetBlack(1);
		}

		if (*(UCHAR*)(Sofdec + 100) != 0x00) {
			//ScreenReSize(0x280, 0x1c0);
		}

		*&pG[0x16] = *&Sofdec[0x61];
		*&pG[0x5C] = *&Sofdec[0x60];

		//SetSystemVcnt((int)*(char*)((int)Sofdec + 0x18d));
		//SetSystemVcnt(Bio4Config.Vcount);
		*system_vcnt = Bio4Config.Vcount;

		// *&pG[0x1407] &= ~0x10000000
		*&pG[0x1407] = *&pG[0x1407] & 0xefffffff;

		/*if ((*Sofdec & 0x400) == 0) {

			cVar1 = *&pSys[8];
			if (((cVar1 == 0x00) || (cVar1 == 0x06)) || (cVar1 == 0x0A)) {
				MessageControl_setupFont(&cMes, 0x1c, 0x1c, (INT*)&pG[0x0F], 2);
			}

			iVar2 = 0;
			do {
				MessageControl_Delete(&cMes, iVar2);
				iVar2 = iVar2 + 1;
			} while (iVar2 < 0x10);

			if (*&Sofdec[0x6f] != 0x00) {
				//Mem_free(*&Sofdec[0x6f]);
			}

			if (((*Sofdec & 0x400) == 0) &&
				(*&pG[0x15] = *&pG[0x15] & 0xffefffff, (*Sofdec & 0x2000) == 0)) {
				*&pG[0x15] = *&pG[0x15] & 0xfffffbff;
			}
		}*/

		if ((*Sofdec >> 8 & 1) == 0) {
			systemVISetBlack(0);
		}

		// *Sofdec &= ~1;
		*Sofdec = *Sofdec & 0xfffffffe;
		OSReport("Done with FinishMovie()..!\n");
	}

}

UINT PlayMovie(CHAR* Filename, UINT Flag) {

	// Direct-X
	if (!Bio4Movie->InitDx9(GetDx9Window(), GetDx9Device(), *pdx9Surface, *pBackBufferSurface)) {
		OSReport("Bio4Movie->InitDx9() failed...\n");
		return 0;
	}

	// FFmpeg
	if (!Bio4Movie->OpenFile("%s\\movie\\%s.mp4", ModuleDir, File->GetNamebase(Filename))) {
		OSReport("Bio4Movie->OpenFile() failed...\n");
		return 0;
	}

	// Global
	if ((*&pG[0x1407] & 0x10000000) != 0) { return *pG & 0xffffff00; }

	// Flag
	*Sofdec = (Flag | 1);

	// Initialize
	//InitWork();
	*&Sofdec[0x60] = *&pG[0x5C];
	*&Sofdec[0x61] = *&pG[0x16];
	//InitApp();
	StartApp();
	*&pG[0x1407] |= 0x10000000;
	InitSync();

	// 
	*&pG[0x1407] = *&pG[0x1407] | 0x4000000;

	if (AutoSkipVideos == TRUE) {
		goto SkipVideoPlaybackEx;
	}

	// Playback
	if ((Flag & 0x200) == 0) {
		if ((Flag & 0x400) == 0) {
			OSReport("Suspending task 0\n");
			TaskSuspend(0);
		}
		if ((*Sofdec & 0x400) == 0) {
			OSReport("Playing video in thread 1\n");
			TaskExec(1, PlayVideoSoftware, Sofdec);
		}
		else {
			UINT uVar1 = TaskStatus(3);
			if ((CHAR)uVar1 != '\0') {
				*&pExecutable[0x00c6cd48 - EXE_BASE] = 0;
				*&pExecutable[0x00c58f88 - EXE_BASE] = 0;
				*&pExecutable[0x00c58fb0 - EXE_BASE] = 0;
				*&pExecutable[0x00c58fd8 - EXE_BASE] = 0;
				*&pExecutable[0x00c59000 - EXE_BASE] = 0;
				TaskKill1(3);
			}
			OSReport("Playing video in thread 3\n");
			TaskExec(3, PlayVideoSoftware, Sofdec);
		}
	}
	else { PlayVideoSoftware(); }

	// Complete
SkipVideoPlaybackEx:
	if ((*Sofdec & 0x400) == 0) {
		*&pG[0x15] = *&pG[0x15] & 0xfffffbff;
		*&Sofdec[0x20] = 0x02;
	}
	if ((*Sofdec & 0x400) == 0) {
		FinishMovie();
	}
	*&pG[0x1407] = *&pG[0x1407] & 0xfbffffff;

	// Complete
	return 1;
}

CHAR IsAliveEvt(int param_1, CHAR* param_2, CHAR* param_3, int* param_4, int param_5) {

	return 0;
}

