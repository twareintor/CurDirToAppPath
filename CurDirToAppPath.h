#pragma once

#include <windows.h>	// for CurDir and AppPath

#include <cstdio>		// for wprintf() - #DEBUG19823

/** 
* this simple class does just set the current directory 
* to the path where the application is because many of the resources
* (runtime) used in this program contains relative path
* (see "media" directory attached to the program)
* when destroyed, sets the current directory again to the 
* path it was before starting the program: e.g. after loading 
* all resources, before the gameplay starts
*
*/

class CApplicationPath
{
	LPWSTR m_wszInitialWorkingDir;

public:
	CApplicationPath(): m_wszInitialWorkingDir(nullptr)
	{
		m_wszInitialWorkingDir = (LPWSTR)GlobalAlloc(GPTR, MAX_PATH);
		if(!m_wszInitialWorkingDir) return;
		GetCurrentDirectoryW(MAX_PATH, m_wszInitialWorkingDir);
		SetCurDirToAppPath();
	}
	
	~CApplicationPath()
	{
		ResetCurDir();
		GlobalFree(m_wszInitialWorkingDir);
	}

	void SetCurDirToAppPath()
	{
		/* ******* setting the working directory to application path */
		LPWSTR wszAppPath = (LPWSTR)GlobalAlloc(GPTR, MAX_PATH);
		GetModuleFileNameW(NULL, wszAppPath, MAX_PATH);
		LPWSTR wEnd = wcsrchr(wszAppPath, L'\\'); 
		*wEnd = L'\0';
		SetCurrentDirectoryW(wszAppPath);
		GlobalFree(wszAppPath);
		wprintf(L"Working in: \"%ls\" directory\n", wszAppPath);
		/* ******* */
	}

	void ResetCurDir()
	{
		if(!m_wszInitialWorkingDir) return;
		SetCurrentDirectoryW(m_wszInitialWorkingDir);
	}

};

