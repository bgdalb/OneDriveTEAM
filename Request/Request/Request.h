#pragma once
#include<cstdint>

#ifdef REQUEST_EXPORTS
#define REQUEST_API _declspec(dllexport)
#else
#define REQUEST_API _declspec(dllimport)
#endif


enum class REQUEST_API Requests : uint8_t {
	LOGINATTEMPT,
	REGISTERATTEMPT,
	SENDPATH,
	CHANGEPATH,
	REMOVEFILE,
	NEWFILE,
	MODIFYFILE,
	DOWNLOADFILES,
	RESETUSER,
	MOVETOTRASH,
	VIEWTRASHBIN,
	RESTOREFILE,
	CHECKSTATE,
	VIEWTRASH,
	PERMANENTLYREMOVEFILE,
    ASKIFSYNCED
};

class REQUEST_API foo
{
	void foo1() {};
};