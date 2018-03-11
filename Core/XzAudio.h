#ifndef XZ_AUDIO_HEADFILE
#define XZ_AUDIO_HEADFILE

#include <map>
#include <bass.h>
#include <string>

class XzAudio
{
private:
	std::map<std::string ,HSTREAM> m_mapMusic;
public:
	XzAudio();
	~XzAudio();
	HRESULT Initialize(HWND hWnd);
	INT LoadFile(std::string sName,DWORD flags);
	BOOL ChannelPlay(std::string sName, BOOL restart);
	BOOL ChannelStop(std::string sName);
	BOOL ChannelPause(std::string sName);
	BOOL SetVolume(FLOAT volume);

	QWORD GetChannelLength(std::string sName,DWORD mode);
	QWORD GetChannelPosition(std::string sName,DWORD mode);
	double ChannelBytes2Seconds(std::string sName,QWORD position);
	QWORD Seconds2ChannelBytes(std::string sName,double position);
	BOOL SetChannelPosition(std::string sName,QWORD position,DWORD mode);
	VOID Release();
};
#endif