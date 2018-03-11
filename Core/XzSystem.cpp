#include "XzSystem.h"

XzSystem::XzSystem()
{
}

XzSystem::~XzSystem()
{
}

XzInput* XzSystem::SysInput = XzInput::GetSingleton();
const XzTime* const XzSystem::SysTime = XzTime::GetSingleton();
const XzProfile* const XzSystem::SysProfile = XzProfile::GetSingleton();

std::wstring XzSystem::CU_A2U(const std::string &_str)
{
	INT iSize = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, NULL, 0);
	std::wstring tempStr;
	tempStr.resize(iSize);
	MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, &tempStr[0], iSize);
	return tempStr.c_str();
}
std::string XzSystem::CU_U2A(const std::wstring &_str) 
{ 
	INT iSize= WideCharToMultiByte(CP_ACP,0,_str.c_str(),wcslen(_str.c_str()),NULL,0,NULL,NULL); 
	std::string tempStr;
	tempStr.resize(iSize);
	WideCharToMultiByte(CP_ACP,0,_str.c_str(),wcslen(_str.c_str()),&tempStr[0],iSize,NULL,NULL); 
	return tempStr.c_str(); 
} 