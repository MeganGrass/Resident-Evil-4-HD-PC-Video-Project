# Resident Evil 4 / バイオハザード4 HD PC Video Project
A project for the latest Steam PC (US) release of Resident Evil 4 (1.0.0RELEASE_DEV.0) that patches the game to use high-quality MP4 video.

Players can also adjust the internal rendering aspect ratio and width/height ([Example](https://twitter.com/MeganPuddin/status/1363337248306044930)).

Additionally, there are a few debug options built-in to help quickly navigate the game and debug the compiled build. Please see the "Config/Debug" section for further details.

This project was originally created for the [Resident Evil 4 HD Project](https://www.re4hd.com/), but was unfortunately unable to be completed in time for final release.

All rights, including the copyrights of game, scenario, music and program are reserved by CAPCOM Co., Ltd.

**Do not distribute this project with the retail game or any high-quality video patches/packages.**

## Build Prerequisites
[Microsoft DirectX 9 SDK](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX)

For this project, I used the [FFmpeg](https://www.ffmpeg.org/) libraries from the [Nvidia Video Codec SDK](https://developer.nvidia.com/nvidia-video-codec-sdk). Custom libraries can be compiled and tested using [
media-autobuild_suite](https://github.com/m-ab-s/media-autobuild_suite).

The following FFmpeg library files are required:

**avcodec.lib**\
**avformat.lib**\
**avutil.lib**\
**swresample.lib**

The following FFmpeg include folders are required:

**libavcodec**\
**libavformat**\
**libavutil**\
**libswresample**\
**libswscale**

In the Nvidia Video Codec SDK, these files and folders can be found in the **Samples\External\FFmpeg** directory.

## Build Instructions

The entire project solution should be placed into the **C:\Bio4HD** directory.

By default, the project will look for FFmpeg headers and libraries in the **C:\Bio4HD\FFmpeg** directory. 
You can adjust the following Visual Studio Project Property Pages to specify custom locations of the FFmpeg headers and libraries:

**Configuration Properties -> C/C++ -> General -> Additional Include Directories**\
**Configuration Properties -> Linker -> Input -> Additional Dependencies**

This project will produce a file named **winmm.dll** that will automatically be placed into the **C:\Program Files (x86)\Steam\steamapps\common\Resident Evil 4\Bin32** directory after compiling the Visual Studio solution.

Note: The "Debug | Win32" profile build will immediately crash the game; please compile the "Release | Win32" profile instead.

## Usage and Implementation
The game will playback MP4 video instead of the standard SFD filetype from CRI Middleware.

MP4 files must be placed into the **C:\Program Files (x86)\Steam\steamapps\common\Resident Evil 4\BIO4\movie** directory and have the same naming convention as their SFD counterparts ("opening_pal.mp4" for example).

I've only tested the following encoded video type, but many other codecs and variations are supported:

> Video: MPEG4 Video (H264) 1920x1080 30fps 15014kbps [V: Alias Data Handler [eng] (h264 main L4.1, yuv420p, 1920x1080, 15014 kb/s)]\
> Audio: AAC 48000Hz stereo 317kbps [A: Alias Data Handler [eng] (aac lc, 48000 Hz, stereo, 317 kb/s)]

## Config/Debug
Configuration options will created upon first-use of this custom dynamic link library and will be located in the **C:\Program Files (x86)\Steam\steamapps\common\Resident Evil 4\Bin32\bio4.ini** file. Detailed descriptions of each option are included in this document and can be manually modified with any basic text editor (Note: some descriptions are outdated).

Additionally, if enabled, the following debug output log files will be placed in the same directory:

**OSReport.log**\
**_vsprintf_s_l.log**\
**snprintf.log**\
**sprintf_s.log**

## Status
- [x] Add support for "New/Load Game" and "Movie Browser"
- [ ] Fix support for "Separate Ways" campaign mode
- [ ] Fix poorly-implemented audio playback code
- [ ] Fix Fullscreen/Window mode errors
- [ ] Add support for Keyboard/Controller input during playback
- [ ] Simple code cleanup

Only Fullscreen playback is supported; the game will crash in Window mode.

Keyboard/Controller input is ignored during playback preventing users from skipping the video.

The game has been tested from start to finish in "New/Load Game" mode and confirmed to be in working status. Additionally, MP4 playback in the "Movie Browser" is also in working status.

"Separate Ways" will immediately crash the game after playing **r500s10.mp4** (the opening video). The game executable uses different threaded code for the "New/Load Game" and "Separate Ways" campaign modes that needs to be properly accessed and patched.

## 2 February 2022
Initial Release (v.0.1.0.0)