#ifndef _XZ_SYSTEM_HEADFILE
#define _XZ_SYSTEM_HEADFILE 

#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <d3dx9.h>
#include "XzTime.h"
#include "XzInput.h"
#include "XzProfile.h"

const UINT MYMSG_NONE = 0;
const UINT MYMSG_BUTTONDOWN	= WM_USER + 10;
const UINT MYMSG_BUTTONUP = WM_USER + 11;
const UINT MYMSG_BUTTONLEAVE = WM_USER + 12;
const UINT MYMSG_CHANGESCENE = WM_USER + 13;
const UINT MYMSG_MOUSE = 14;
const short MSG_END = 2;

class XzSystem
{
public:
    XzSystem();
    ~XzSystem();

public:
    /*通过常量指针，能读取指针地址的内容 但不可修改
    指针常量保证该指针 指向地址唯一*/

    static XzInput* SysInput;
    static const XzTime* const SysTime;
	static const XzProfile* const SysProfile;

	static std::wstring CU_A2U(const std::string &_str);
	static std::string CU_U2A(const std::wstring &_str);

};
#endif