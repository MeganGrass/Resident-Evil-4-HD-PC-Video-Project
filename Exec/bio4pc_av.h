#pragma once

#include <xaudio2.h>

// File
extern CHAR* VideoFilename;

extern UINT* Sofdec;

// Hook
VOID MovieStartWait(VOID);
VOID FinishMovie(VOID);
UINT PlayMovie(CHAR* Filename, UINT Flag);

#pragma pack(push, 1)
typedef struct tagWaveform {
	CHAR RIFF[4];				// "RIFF"
	UINT Filesize;				// dataSize + sizeof(tagWaveform) - 8
	CHAR WAVEfmt[8];			// "WAVEfmt "
	UINT fmtSize;				// 0x10
	USHORT fmtType;				// 1=PCM
	USHORT fmtChannels;			// 1=Mono, 2=Stereo
	INT fmtSampleRate;			// 
	INT fmtBytesPerSecond;		// (Sample Rate * BitsPerSample * Channels) / 8
	USHORT fmtBlockAlign;		// 2=Mono, 4=Stereo
	USHORT fmtBitsPerSample;	// 
	CHAR DATA[4];				// "data"
	UINT dataSize;				// 
	UCHAR* AudioData;			// 
} Waveform;
#pragma pack(pop)

class Resident_Evil_4_PC_AV {
private:

public:

	// Windows
	HWND hWnd;
	UINT WindowWidth;
	UINT WindowHeight;
	UINT ClientWidth;
	UINT ClientHeight;
	RECT hWndRect;
	RECT ClientRect;

	// Direct-X
	LPDIRECT3D9 pInterface;
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3DSURFACE9 pRenderTarget;
	LPDIRECT3DSURFACE9 pBackBuffer;
	D3DLOCKED_RECT Dx9Rect;

	// FFmpeg
	AVFormatContext* pAvFmtCtx;
	AVPacket* pAVPacket;
	INT iAudio;
	INT iVideo;
	INT iSubTitle;

	// Audio
	AVCodecContext* pAudioCodecCtx;
	AVCodec* pAudioCodec;
	AVFrame* pAudioFrame;
	AVFrame* pAudioFrameOut;
	SwrContext* AudioConvertCtx;
	Waveform* Wave;
	XAUDIO2_BUFFER AudioBuffer;
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;
	IXAudio2SourceVoice* SourceVoice;

	// Video
	AVCodecContext* pVideoCodecCtx;
	AVCodec* pVideoCodec;
	AVFrame* pVideoFrame;
	AVFrame* pVideoYUV;
	SwsContext* VideoConvertCtx;

	// Subtitle
	AVSubtitle* pSubtitle;

	// General
	BOOL IsDx9Initialized;
	BOOL IsAVInitialized;
	BOOL IsMoviePlaying;
	BOOL AutoSkipVideos;
	BOOL UseSofdecVideo;

	// Sofdec
	UINT Flag;

	// Boot
	Resident_Evil_4_PC_AV(VOID) {

		hWnd = nullptr;
		WindowWidth = NULL;
		WindowHeight = NULL;
		ClientWidth = NULL;
		ClientHeight = NULL;
		hWndRect = { NULL };
		ClientRect = { NULL };

		pInterface = nullptr;
		pDevice = nullptr;
		pRenderTarget = nullptr;
		pBackBuffer = nullptr;
		Dx9Rect = { NULL };

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
		Wave = nullptr;
		AudioBuffer = { NULL };
		pXAudio2 = nullptr;
		pMasterVoice = nullptr;
		SourceVoice = nullptr;

		pVideoCodecCtx = nullptr;
		pVideoCodec = nullptr;
		pVideoFrame = nullptr;
		pVideoYUV = nullptr;
		VideoConvertCtx = nullptr;

		pSubtitle = nullptr;

		IsDx9Initialized = FALSE;
		IsAVInitialized = FALSE;
		IsMoviePlaying = FALSE;
		AutoSkipVideos = FALSE;
		UseSofdecVideo = FALSE;

		Flag = NULL;

	}
	virtual ~Resident_Evil_4_PC_AV(VOID) {}

	// Initialize
	BOOL InitDx9(HWND Window, LPDIRECT3DDEVICE9 Device, LPDIRECT3DSURFACE9 TargetSurface, LPDIRECT3DSURFACE9 BackBuffer);
	BOOL OpenFile(CHAR* _Filename, ...);

	// Audio
	BOOL InitAudio(Waveform* Wav);

	// Cleanup
	VOID Shutdown(VOID);

};
