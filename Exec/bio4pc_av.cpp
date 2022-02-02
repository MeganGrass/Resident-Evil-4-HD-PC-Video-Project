
#include "..\\dllmain.h"

// File
CHAR* VideoFilename;

UINT* Sofdec;

// Hardware Playback
extern VOID OpenVideoAMD(VOID);
extern VOID OpenVideoNvidia(VOID);

VOID InitApp(VOID);
VOID MovieStartWait(VOID);
VOID FinishMovie(VOID);

// Plaback
DWORD WINAPI DemuxFunc(LPVOID Parameter) {

	// 
	INT ret = NULL;
	Resident_Evil_4_PC_AV* Movie = (Resident_Evil_4_PC_AV*)Parameter;

	// Flag
	if (!Movie->IsAVInitialized || !Movie->IsDx9Initialized) { _endthreadex(0); return 0; }
	Movie->IsMoviePlaying = TRUE;

	// Vsync
	AVRational time_base = { NULL };
	const static AVRational time_base_q = { 1, AV_TIME_BASE };
	int64_t pts_time = NULL;
	int64_t now_time = NULL;

	// Audio
	if (Movie->iAudio != -1) {
		Movie->SourceVoice->SubmitSourceBuffer(&Movie->AudioBuffer);
		Movie->SourceVoice->Start(0);
	}

	// Render
	int64_t start_time = av_gettime();
	while (true) {

		// Read Frame
		ret = av_read_frame(Movie->pAvFmtCtx, Movie->pAVPacket);
		if (ret == AVERROR_EOF) { break; }
		else if (ret < 0) { break; }

		/* Audio
		if (Movie->pAVPacket->stream_index == Movie->iAudio) {
			if (avcodec_send_packet(Movie->pAudioCodecCtx, Movie->pAVPacket) == 0) {
				if (avcodec_receive_frame(Movie->pAudioCodecCtx, Movie->pAudioFrame) == 0) {

					Movie->pAudioFrameOut->channel_layout = AV_CH_LAYOUT_STEREO;
					Movie->pAudioFrameOut->sample_rate = Movie->pAudioFrame->sample_rate;
					Movie->pAudioFrameOut->format = AV_SAMPLE_FMT_S16;
					swr_convert_frame(Movie->AudioConvertCtx, Movie->pAudioFrameOut, Movie->pAudioFrame);
					data_size = av_samples_get_buffer_size(NULL, Movie->pAudioFrameOut->channels, Movie->pAudioFrameOut->nb_samples, AV_SAMPLE_FMT_S16, 0);
					//memcpy_s(Movie->Wave->AudioData, data_size, Movie->pAudioFrameOut->data[0], data_size);

				}
			}
		}*/

		// Video
		if (Movie->pAVPacket->stream_index == Movie->iVideo) {
			if (avcodec_send_packet(Movie->pVideoCodecCtx, Movie->pAVPacket) == 0) {
				if (avcodec_receive_frame(Movie->pVideoCodecCtx, Movie->pVideoFrame) == 0)
				{
					//
					sws_freeContext(Movie->VideoConvertCtx);
					Movie->VideoConvertCtx = sws_getContext(
						Movie->pVideoCodecCtx->width, Movie->pVideoCodecCtx->height, Movie->pVideoCodecCtx->pix_fmt,
						Movie->pVideoCodecCtx->width, Movie->pVideoCodecCtx->height, AV_PIX_FMT_RGB32, SWS_POINT, NULL, NULL, NULL);

					//
					Movie->pRenderTarget->LockRect(&Movie->Dx9Rect, nullptr, D3DLOCK_DISCARD);
					Movie->pVideoYUV->data[0] = (uint8_t*)Movie->Dx9Rect.pBits;
					Movie->pVideoYUV->linesize[0] = Movie->Dx9Rect.Pitch;
					sws_scale(Movie->VideoConvertCtx,
						(const unsigned char* const*)Movie->pVideoFrame->data, Movie->pVideoFrame->linesize, 0, Movie->pVideoCodecCtx->height,
						Movie->pVideoYUV->data, Movie->pVideoYUV->linesize);
					Movie->pRenderTarget->UnlockRect();

					//
					Movie->pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
					Movie->pDevice->BeginScene();
					if (Movie->pBackBuffer)
					{
						Movie->pBackBuffer->Release();
						Movie->pBackBuffer = NULL;
					}
					Movie->pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &Movie->pBackBuffer);
					Movie->pDevice->StretchRect(Movie->pRenderTarget, NULL, Movie->pBackBuffer, &Movie->ClientRect, D3DTEXF_NONE);
					Movie->pDevice->EndScene();
					Movie->pDevice->Present(NULL, NULL, NULL, NULL);

					// VSync
					time_base = Movie->pAvFmtCtx->streams[Movie->iVideo]->time_base;
					//AVRational time_base_q = { 1,AV_TIME_BASE };
					pts_time = av_rescale_q(Movie->pAVPacket->dts, time_base, time_base_q);
					now_time = av_gettime() - start_time;
					if (pts_time > now_time) { av_usleep(pts_time - now_time); }

				}
			}
		}

		// SubTitle
		if (Movie->pAVPacket->stream_index == Movie->iSubTitle) {/**/}

	}

	// Audio
	if (Movie->iAudio != -1) {
		Movie->SourceVoice->DestroyVoice();
		Movie->pMasterVoice->DestroyVoice();
	}

	// Flag
	Movie->IsMoviePlaying = FALSE;

	// Complete
	_endthreadex(0);
	return 0;

}
VOID PlayVideoSoftware(VOID) {

	// Flag
	if (!Bio4Movie->IsAVInitialized) { return; }

	// Initialize
	InitApp();

	SetBit(StatusFlag, STA_MOVIE_ON, ON);
	//SetBit(SystemFlag, SYS_SET_BLACK, ON);
	SetBit(StatusFlag, STA_MOVIE2_ON, ON);

	// A/V Playback
	HANDLE DemuxThread = NULL;
	DemuxThread = CreateThread(NULL, NULL, DemuxFunc, Bio4Movie, NULL, NULL);
	if (DemuxThread != NULL) {
		WaitForSingleObject(DemuxThread, INFINITE);
		CloseHandle(DemuxThread);
	}

	// Cleanup
	Bio4Movie->Shutdown();

	// Complete
	if ((*Sofdec & 0x400) == 0) {
		FinishMovie();
		OSReport("Signaling task 0\n");
		TaskSignal(0);
	}
	if ((*Sofdec & 0x200) == 0) {
		OSReport("Exiting movie task\n");
		TaskExit();
	}

}
// Hook
VOID InitApp(VOID) {

	//cSofdec_setCamera();	// enabling this crashes game after movie playback

	VOID* pMemclr = (VOID*)&pExecutable[0x00c6cd58 - EXE_BASE];	// *&Sofdec[0x02];
	memclr_asm(pMemclr, 0x170);

	*&Sofdec[0x02] = 0;
	*&Sofdec[0x0C] = 10000000;
	*&Sofdec[0x0D] = Bio4Movie->pVideoCodecCtx->width;
	*&Sofdec[0x0E] = Bio4Movie->pVideoCodecCtx->height;
	*&Sofdec[0x0F] = 4;
	*&Sofdec[0x10] = 2;
	*&Sofdec[0x11] = *&pExecutable[0x00c65cac - EXE_BASE];	// _Dst
	*&Sofdec[0x12] = NULL;							// _Size;
	*&Sofdec[0x13] = 0;
	*&Sofdec[0x20] = 2;
	*&Sofdec[0x4D] = 0x100;
	*&Sofdec[0x5F] = 1;
	*&Sofdec[0x60] = *StopFlag;
	*&Sofdec[0x61] = *DisplayFlag;
	*&Sofdec[0x63] = (UCHAR)*system_vcnt;
	*&Sofdec[0x64] = 1;

	//*Sofdec |= 0x20;	// enabling this causes EVD (after movie playback) be skipped

	//OSReport("Movie Play : %s \n", (CHAR*)((INT)*Sofdec + 0x136));

	if ((*Sofdec & 0x400) == 0) {
		*StopFlag = 0xFFFFFFFF;
		SetBit(SystemFlag, SYS_TRANS_STOP, ON);
		SetBit(SystemFlag, SYS_SCREEN_STOP, ON);
		return;
	}

	// Display
	*DisplayFlag = 0xFFFFFFFF;
	SetBit(DisplayFlag, DPF_COCKPIT, OFF);
	SetBit(DisplayFlag, DPF_ID_SYSTEM, OFF);
	SetBit(DisplayFlag, DPF_ACTBTN, OFF);
	SetBit(DisplayFlag, DPF_MESSAGE, OFF);

	// Stop
	*StopFlag = 0xFFFFFFFF;
	SetBit(StopFlag, SPF_CAMERA, OFF);
	SetBit(StopFlag, SPF_SCE, OFF);
	SetBit(StopFlag, SPF_CINESCO, OFF);
	SetBit(StopFlag, SPF_EVT, OFF);
	SetBit(StopFlag, SPF_ACTBTN, OFF);
	SetBit(StopFlag, SPF_ID_SYSTEM, OFF);

}
VOID MovieStartWait(VOID) {

	OSReport("MovieStartWait() is starting...\n");
	while ((CkBit(StatusFlag, STA_MOVIE2_ON) == 0)) { SceSleep(1); }
	OSReport("MovieStartWait() is complete...\n");

	// Killswitch
	SetBit(StopFlag, SPF_EVT, ON);

	// Flags
	PrintDebugFlags();
	PrintStopFlags();
	PrintStatusFlags();
	PrintSystemFlags();
	PrintConfigFlags();
	PrintExtraFlags();
	PrintDisplayFlags();

}
VOID FinishMovie(VOID) {

	OSReport("FinishMovie() is starting...\n");

	if ((*Sofdec & 0x400) == 0) { SetBit(SystemFlag, SYS_SET_BLACK, ON); }

	*DisplayFlag = *&Sofdec[0x61];
	*StopFlag = *&Sofdec[0x60];

	SetSystemVcnt(*&Sofdec[0x63]);

	SetBit(StatusFlag, STA_MOVIE_ON, OFF);
	SetBit(StatusFlag, STA_MOVIE2_ON, OFF);

	if ((*Sofdec & 0x400) == 0) {
		SetBit(SystemFlag, SYS_TRANS_STOP, OFF);
		if ((*Sofdec & 0x2000) == 0) { SetBit(SystemFlag, SYS_SCREEN_STOP, OFF); }
		//SetBit(SystemFlag, SYS_SCREEN_STOP, OFF);
	}

	if ((*Sofdec >> 8 & 1) == 0) { SetBit(SystemFlag, SYS_SET_BLACK, OFF); }

	*Sofdec = *Sofdec & 0xFFFFFFFE;

	OSReport("FinishMovie() is complete...\n");

}
UINT PlayMovie(CHAR* Filename, UINT Flag) {

	// Global
	if (CkBit(StatusFlag, STA_MOVIE_ON) != 0) { return *pG & 0xFFFFFF00; }

	// Direct-X
	if (!Bio4Movie->InitDx9(GetDx9Window(), GetDx9Device(), *pdx9Surface, *pBackBufferSurface)) {
		OSReport("Bio4Movie->InitDx9() failed...\n");
		return 0;
	}

	// FFmpeg
	//if (!Bio4Movie->OpenFile("%s\\movie\\%s.mp4", ModuleDir, "r200")) {
	if (!Bio4Movie->OpenFile("%s\\movie\\%s.mp4", ModuleDir, File->GetNamebase(Filename))) {
		OSReport("Bio4Movie->OpenFile() failed...\n");
		return 0;
	}
	else {
		OSReport("Open: %s\\movie\\%s.mp4\r\n", ModuleDir, File->GetNamebase(Filename));
	}

	// Flag
	OSReport("PlayMovie : Flag\t%X\n", Flag);
	*Sofdec = (Flag | 1);
	Bio4Movie->Flag = Flag;

	// Skip
	if (Bio4Movie->AutoSkipVideos == TRUE) { *Sofdec = *Sofdec & 0xFFFFFFFE; goto SkipVideoPlaybackEx; }

	// Playback
	if ((Flag & 0x200) == 0) {
		if ((Flag & 0x400) == 0) {
			OSReport("Suspending task 0\n");
			TaskSuspend(0);
		}
		if ((*Sofdec & 0x400) == 0) {
			OSReport("Playing video in task 1\n");
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
				OSReport("Killing task 3\n");
				TaskKill1(3);
			}
			OSReport("Playing video in task 3\n");
			TaskExec(3, PlayVideoSoftware, Sofdec);
		}
	}
	else { PlayVideoSoftware(); }

	// Complete
SkipVideoPlaybackEx:
	return 1;
}
// Initialize
BOOL Resident_Evil_4_PC_AV::InitDx9(HWND Window, LPDIRECT3DDEVICE9 Device, LPDIRECT3DSURFACE9 TargetSurface, LPDIRECT3DSURFACE9 BackBuffer) {

	// Flag
	if (IsDx9Initialized) { return TRUE; }
	IsDx9Initialized = FALSE;

	// Window
	if (IsWindow(Window)) { hWnd = Window; }
	else { return FALSE; }

	// Dimension
	GetWindowRect(hWnd, &hWndRect);
	WindowWidth = hWndRect.right;
	WindowHeight = hWndRect.bottom;
	GetClientRect(hWnd, &ClientRect);
	ClientWidth = ClientRect.right;
	ClientHeight = ClientRect.bottom;

	// Direct-X
	HRESULT hr = D3D_OK;
	if (FAILED(hr = Device->TestCooperativeLevel())) { return FALSE; }
	else {
		pDevice = Device;
		if (FAILED(hr = pDevice->GetDirect3D(&pInterface))) { return FALSE; }
		pRenderTarget = TargetSurface;
		if (FAILED(pDevice->CreateOffscreenPlainSurface(ClientWidth, ClientHeight, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &pRenderTarget, NULL))) { return FALSE; }
		pBackBuffer = BackBuffer;
	}

	// Complete
	return IsDx9Initialized = TRUE;

}
BOOL Resident_Evil_4_PC_AV::OpenFile(CHAR* _Filename, ...) {

	// Flag
	IsAVInitialized = FALSE;
	if (!IsDx9Initialized) { return FALSE; }

	// Format
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _Filename);
	INT _StrLen = (_vscprintf(_Filename, _ArgList) + 1);
	CHAR* Filename = new CHAR[_StrLen];
	RtlSecureZeroMemory(Filename, _StrLen);
	vsprintf_s(Filename, _StrLen, _Filename, _ArgList);
	__crt_va_end(_ArgList);

	// Open
	pAvFmtCtx = avformat_alloc_context();
	if (avformat_open_input(&pAvFmtCtx, Filename, NULL, NULL) < 0) {
		OSReport("AVERROR: Unable to open %s\n", Filename);
		delete[] Filename;
		Shutdown();
		return FALSE;
	}
	delete[] Filename;

	// Info
	if (avformat_find_stream_info(pAvFmtCtx, NULL) < 0) {
		OSReport("AVERROR: Unable to parse media file information\n");
		Shutdown();
		return FALSE;
	}
	for (UINT i = 0; i < pAvFmtCtx->nb_streams; i++)
	{
		if (pAvFmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) { iAudio = i; }
		if (pAvFmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) { iVideo = i; }
		if (pAvFmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE) { iSubTitle = i; }
	}

	// Error
	if (iAudio == -1 && iVideo == -1) {
		OSReport("AVERROR: Media file doesn't contain either audio or video\n");
		Shutdown();
		return FALSE;
	}
	if (iVideo == -1) {
		OSReport("AVERROR: Media file doesn't contain video\n");
		Shutdown();
		return FALSE;
	}

	// General
	pAVPacket = av_packet_alloc();

	// Audio
	if (iAudio != -1) {

		// Context
		pAudioCodecCtx = avcodec_alloc_context3(NULL);
		if (avcodec_parameters_to_context(pAudioCodecCtx, pAvFmtCtx->streams[iAudio]->codecpar) < 0) {
			OSReport("AVERROR: Unable to contexualize audio parameters\n");
			Shutdown();
			return FALSE;
		}

		// Codec
		pAudioCodec = avcodec_find_decoder(pAudioCodecCtx->codec_id);
		if (pAudioCodec == NULL) {
			OSReport("AVERROR: Unsupported audio codec\n");
			Shutdown();
			return FALSE;
		}
		if (avcodec_open2(pAudioCodecCtx, pAudioCodec, NULL) < 0) {
			OSReport("AVERROR: Unable to initialize audio codec\n");
			Shutdown();
			return FALSE;
		}

		// Conversion
		AudioConvertCtx = swr_alloc();
		av_opt_set_int(AudioConvertCtx, "in_channel_count", pAudioCodecCtx->channels, 0);
		av_opt_set_int(AudioConvertCtx, "out_channel_count", pAudioCodecCtx->channels, 0);
		av_opt_set_int(AudioConvertCtx, "in_channel_layout", pAudioCodecCtx->channel_layout, 0);
		av_opt_set_int(AudioConvertCtx, "out_channel_layout", AV_CH_LAYOUT_STEREO, 0);
		av_opt_set_int(AudioConvertCtx, "in_sample_rate", pAudioCodecCtx->sample_rate, 0);
		av_opt_set_int(AudioConvertCtx, "out_sample_rate", pAudioCodecCtx->sample_rate, 0);
		av_opt_set_sample_fmt(AudioConvertCtx, "in_sample_fmt", pAudioCodecCtx->sample_fmt, 0);
		av_opt_set_sample_fmt(AudioConvertCtx, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);
		swr_init(AudioConvertCtx);

		// Buffer
		pAudioFrame = av_frame_alloc();
		pAudioFrameOut = av_frame_alloc();

		// Data Size
		Wave = new Waveform;
		RtlSecureZeroMemory(Wave, sizeof(Waveform));
		while (true) {

			// Read Frame
			int ret = av_read_frame(pAvFmtCtx, pAVPacket);
			if (ret == AVERROR_EOF) { break; }
			else if (ret < 0) { break; }

			// Audio
			if (pAVPacket->stream_index == iAudio) {
				if (avcodec_send_packet(pAudioCodecCtx, pAVPacket) == 0) {
					if (avcodec_receive_frame(pAudioCodecCtx, pAudioFrame) == 0) {

						pAudioFrameOut->channel_layout = AV_CH_LAYOUT_STEREO;
						pAudioFrameOut->sample_rate = pAudioFrame->sample_rate;
						pAudioFrameOut->format = AV_SAMPLE_FMT_S16;
						swr_convert_frame(AudioConvertCtx, pAudioFrameOut, pAudioFrame);
						Wave->dataSize += av_samples_get_buffer_size(NULL, pAudioFrameOut->channels, pAudioFrameOut->nb_samples, AV_SAMPLE_FMT_S16, 0);

					}
				}
			}
		}

		// Data Header
		memcpy_s(&Wave->RIFF[0], 4, "RIFF", 4);
		Wave->Filesize = (Wave->dataSize + sizeof(tagWaveform)) - 8;
		memcpy_s(&Wave->WAVEfmt[0], 8, "WAVEfmt ", 8);
		Wave->fmtSize = 16;
		Wave->fmtType = 1;
		Wave->fmtChannels = 2;
		Wave->fmtSampleRate = pAudioCodecCtx->sample_rate;
		Wave->fmtBytesPerSecond = ((pAudioCodecCtx->sample_rate * 16 * pAudioCodecCtx->channels) / 8);
		Wave->fmtBlockAlign = 4;
		Wave->fmtBitsPerSample = 16;
		memcpy_s(&Wave->DATA[0], 4, "data", 4);
		Wave->AudioData = new UCHAR[Wave->dataSize];
		RtlSecureZeroMemory(Wave->AudioData, Wave->dataSize);

		// Data Buffer
		av_seek_frame(pAvFmtCtx, -1, 0, AVSEEK_FLAG_FRAME);
		UINT data_size = NULL;
		UINT Ptr = NULL;
		while (true) {

			// Read Frame
			int ret = av_read_frame(pAvFmtCtx, pAVPacket);
			if (ret == AVERROR_EOF) { break; }
			else if (ret < 0) { break; }

			// Audio
			if (pAVPacket->stream_index == iAudio) {
				if (avcodec_send_packet(pAudioCodecCtx, pAVPacket) == 0) {
					if (avcodec_receive_frame(pAudioCodecCtx, pAudioFrame) == 0) {

						pAudioFrameOut->channel_layout = AV_CH_LAYOUT_STEREO;
						pAudioFrameOut->sample_rate = pAudioFrame->sample_rate;
						pAudioFrameOut->format = AV_SAMPLE_FMT_S16;
						swr_convert_frame(AudioConvertCtx, pAudioFrameOut, pAudioFrame);
						data_size = av_samples_get_buffer_size(NULL, pAudioFrameOut->channels, pAudioFrameOut->nb_samples, AV_SAMPLE_FMT_S16, 0);
						memcpy_s(&Wave->AudioData[Ptr], data_size, pAudioFrameOut->data[0], data_size);
						Ptr += data_size;

					}
				}
			}
		}
		if (!InitAudio(Wave)) {
			OSReport("XAudio2: Unable to initialize audio buffer\n");
			Shutdown();
			return FALSE;
		}

		// Rewind
		av_seek_frame(pAvFmtCtx, -1, 0, AVSEEK_FLAG_FRAME);

		// Debug
		//_iobuf* _AudioFile = File->Open(CREATE_FILE, "%s\\file.wav", ModuleDir);
		//File->Write(_AudioFile, 0x00, Wave, sizeof(tagWaveform) - 4);
		//File->Write(_AudioFile, sizeof(tagWaveform) - 4, Wave->AudioData, Wave->dataSize);
		//fclose(_AudioFile);

	}

	// Video
	if (iVideo != -1) {

		// Context
		pVideoCodecCtx = avcodec_alloc_context3(NULL);
		if (avcodec_parameters_to_context(pVideoCodecCtx, pAvFmtCtx->streams[iVideo]->codecpar) < 0) {
			OSReport("AVERROR: Unable to contexualize video parameters\n");
			Shutdown();
			return FALSE;
		}

		// Codec
		pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
		if (pVideoCodec == NULL) {
			OSReport("AVERROR: Unsupported video codec\n");
			Shutdown();
			return FALSE;
		}
		if (avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0) {
			OSReport("AVERROR: Unable to initialize video codec\n");
			Shutdown();
			return FALSE;
		}

		// Buffer
		pVideoFrame = av_frame_alloc();
		pVideoYUV = av_frame_alloc();
	}

	// Subtitle
	if (iSubTitle != -1) {
		pSubtitle = new AVSubtitle;
		//memset(pSubtitle, 0, sizeof(AVSubtitle));
	}

	// Complete
	return IsAVInitialized = TRUE;

}
// Audio
BOOL Resident_Evil_4_PC_AV::InitAudio(Waveform* Wav) {

	HRESULT hr;
	WAVEFORMATEX WaveFormat = { 0 };
	AudioBuffer = { 0 };

	// Error
	if (Wav == nullptr) { return FALSE; }

	// Source Format
	WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	WaveFormat.wBitsPerSample = Wav->fmtBitsPerSample;
	WaveFormat.nSamplesPerSec = Wav->fmtSampleRate;
	WaveFormat.nChannels = Wav->fmtChannels;
	WaveFormat.nBlockAlign = (WaveFormat.nChannels * WaveFormat.wBitsPerSample) / 8;
	WaveFormat.nAvgBytesPerSec = WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign;
	WaveFormat.cbSize = sizeof(WaveFormat);

	// Buffer Format
	AudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	AudioBuffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	AudioBuffer.AudioBytes = Wav->dataSize;
	AudioBuffer.pAudioData = Wav->AudioData;
	AudioBuffer.pContext = NULL;

	//if (FAILED(hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED))) { return FALSE; }
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, 0))) { return FALSE; }
	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice, Wav->fmtChannels, Wav->fmtSampleRate))) { return FALSE; }
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&SourceVoice, (WAVEFORMATEX*)&WaveFormat))) { return FALSE; }

	// Complete
	return TRUE;
}
// Shutdown
VOID Resident_Evil_4_PC_AV::Shutdown(VOID) {
	if (pXAudio2 != nullptr) {
		pXAudio2->Release();
		pXAudio2 = nullptr;
		pMasterVoice = nullptr;
		SourceVoice = nullptr;
	}
	if (iAudio != -1) {
		avcodec_free_context(&pAudioCodecCtx);
		av_frame_free(&pAudioFrame);
		av_frame_free(&pAudioFrameOut);
		swr_free(&AudioConvertCtx);
	}
	if (iVideo != -1) {
		avcodec_free_context(&pVideoCodecCtx);
		av_frame_free(&pVideoFrame);
		av_frame_free(&pVideoYUV);
		sws_freeContext(VideoConvertCtx);
	}
	if (iSubTitle != -1) {
		avsubtitle_free(pSubtitle);
	}
	if (pAVPacket != nullptr) {
		av_packet_free(&pAVPacket);
	}
	if (pAvFmtCtx != nullptr) {
		avformat_close_input(&pAvFmtCtx);
		avformat_free_context(pAvFmtCtx);
	}

	pAvFmtCtx = nullptr;
	pAVPacket = nullptr;
	iAudio = -1;
	iVideo = -1;
	iSubTitle = -1;

	pAudioCodecCtx = nullptr;
	pAudioCodec = nullptr;
	pAudioFrame = nullptr;
	pAudioFrameOut = nullptr;
	AudioConvertCtx = nullptr;
	if (Wave != nullptr) {
		delete Wave;
		Wave = nullptr;
	}
	AudioBuffer = { NULL };

	pVideoCodecCtx = nullptr;
	pVideoCodec = nullptr;
	pVideoFrame = nullptr;
	pVideoYUV = nullptr;
	VideoConvertCtx = nullptr;

	pSubtitle = nullptr;

	IsAVInitialized = FALSE;
	IsMoviePlaying = FALSE;
}