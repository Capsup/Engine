#pragma once

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <strsafe.h>
#include <string.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#define Err( text ) tools::ErrorExit( text );
#define ErrCT( text ) tools::ErrorExit( text, true );


namespace tools
{

	inline void ErrorExit(LPTSTR lpszFunction, bool CT = false) 
	{ 
		// Retrieve the system error message for the last-error code

		if( CT )
		{
			FatalAppExit( NULL, lpszFunction );
		}

		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError(); 

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );

		// Display the error message and exit the process

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
			(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
		StringCchPrintf((LPTSTR)lpDisplayBuf, 
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("%s failed with error %d: %s"), 
			lpszFunction, dw, lpMsgBuf); 
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw); 
	}

	inline long GetFileLength( char* path )
	{
		FILE *file;
		fopen_s( &file, path, "r" );
		if( !file )
			Err( TEXT("fopen") );
		fseek( file, 0, SEEK_END );
		long len = ftell( file ) - 15;
		fclose( file );
		return( len );
	}

	inline int ContainsX( char* sourcestring, ... )
	{

	}

	inline bool IsExtSupported( char* ext )
	{
		const char* extensions = (char*) glGetString( GL_EXTENSIONS );
		//const GLubyte* extensions = glGetString(GL_EXTENSIONS);
		return( strstr( extensions, ext ) != NULL ? true : false );
		//if( strchr( ext, extensions ) )
		//	return true;

	}

	inline void dump( char* root, int length )
	{
		for ( int i = 0; i < length; i++ )
		{
			printf( "%X\t", root[i] );
			//std::cout << (int)root[i] << "\t";
			if ( (i+1) % 8 == 0 && i > 0 )
				std::cout << "\n";
		}
		std::cout << std::endl;
	}

	inline LPCWSTR CharToError( char* text )
	{
		int len = strlen( text ) + 1;
		wchar_t *wText = new wchar_t[len];
		if ( wText == 0 )
			return false;
		memset( wText, 0, len );
		::MultiByteToWideChar( CP_ACP, NULL, text, -1, wText, len );

		return wText;

		delete []wText;

	}

	inline LPCWSTR DCharToError( char* text, char* text2 )
	{
		char* c3 = ( char* ) malloc( strlen( text ) + strlen( text2 ) + 1 );
		strcpy( c3, text );
		strcat( c3, text2 );

		return CharToError( c3 );
	}
	inline std::wstring StringToWString(const std::string& s)
	{
		std::wstring temp(s.length(),L' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp; 
	}


	inline std::string WStringToString(const std::wstring& s)
	{
		std::string temp(s.length(), ' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp; 
	}
}