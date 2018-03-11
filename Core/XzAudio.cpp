#include "XzAudio.h"

XzAudio::XzAudio()
{

}
XzAudio::~XzAudio()
{

}
HRESULT XzAudio::Initialize(HWND hWnd)
{
	return ::BASS_Init(-1,44100,0,0,0);
}
INT XzAudio::LoadFile(std::string sName,DWORD flags)
{
	HRESULT tmp = BASS_StreamCreateFile(false,sName.c_str(),0,0,flags);
	//sName.pop_back();sName.pop_back();sName.pop_back();sName.pop_back();
	//m_mapMusic.insert();
	return 0;
}
BOOL XzAudio::ChannelPlay(std::string sName, BOOL restart)
{
	return false;
}
BOOL XzAudio::ChannelStop(std::string sName)
{
	return false;
}
BOOL XzAudio::ChannelPause(std::string sName)
{
	return false;
}
BOOL XzAudio::SetVolume(FLOAT volume)
{
	return false;
}
QWORD XzAudio::GetChannelLength(std::string sName,DWORD mode)
{
	return 0;
}
QWORD XzAudio::GetChannelPosition(std::string sName,DWORD mode)
{
	return 0;
}
double XzAudio::ChannelBytes2Seconds(std::string sName,QWORD position)
{
	return 0;
}
QWORD XzAudio::Seconds2ChannelBytes(std::string sName,double position)
{
	return 0;
}
BOOL XzAudio::SetChannelPosition(std::string sName,QWORD position,DWORD mode)
{
	return 0;
}
VOID XzAudio::Release()
{
	::BASS_Free();
}