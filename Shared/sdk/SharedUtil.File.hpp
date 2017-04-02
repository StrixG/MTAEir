/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        SharedUtil.File.hpp
*  PURPOSE:
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifdef WIN32
#include "shellapi.h"
#include "shlobj.h"
#else
#include <dirent.h>
#endif

#include <CFileSystemInterface.h>

#ifdef _WIN32
#ifdef MTA_CLIENT

filePath SharedUtil::GetSystemLocalAppDataPath()
{
    char szResult[MAX_PATH] = "";
    SHGetFolderPathA( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szResult );
    return filePath( szResult );
}

filePath SharedUtil::GetSystemCommonAppDataPath()
{
    char szResult[MAX_PATH] = "";
    SHGetFolderPathA( NULL, CSIDL_COMMON_APPDATA, NULL, 0, szResult );
    return filePath( szResult );
}

filePath SharedUtil::GetSystemTempPath()
{
    char szResult[4030] = "";
    GetTempPath( 4000, szResult );
    return filePath( szResult );
}

filePath SharedUtil::GetMTADataPath()
{
    filePath path = GetSystemCommonAppDataPath();
    path += "/MTA San Andreas All/";
    path += GetMajorVersionString();
    path += "/";
    return path;
}

filePath SharedUtil::GetMTATempPath()
{
    filePath path = GetSystemTempPath();
    path += "MTA";
    path += GetMajorVersionString();
    path += "/";
    return path;
}
#endif
#endif

#ifdef _WIN32

filePath SharedUtil::GetCurrentDirectory()
{
    char szCurDir[1024] = "";
    ::GetCurrentDirectoryA( sizeof(szCurDir), szCurDir );
    return filePath( szCurDir );
}

filePath SharedUtil::GetWindowsDirectory()
{
    char szWinDir[MAX_PATH] = "";
    ::GetWindowsDirectoryA( szWinDir, sizeof(szWinDir) );
    return filePath( szWinDir );
}

#endif

void SharedUtil::ExtractFilename ( const SString& in, SString* strPath, SString* strFilename )
{
    if ( !in.Split ( PATH_SEPERATOR, strPath, strFilename, -1 ) )
        if ( strFilename )
            *strFilename = in;
}

bool SharedUtil::ExtractExtention( const SString& in, SString* strMain, SString* strExt )
{
    return in.Split ( ".", strMain, strExt, -1 );
}

SString SharedUtil::ExtractFilename( const SString& in )
{
    SString strFilename;
    ExtractFilename ( in, NULL, &strFilename );
    return strFilename;
}

SString SharedUtil::ExtractPath( const SString& strPathFilename )
{
    SString strPath;
    ExtractFilename ( strPathFilename, &strPath, NULL );
    return strPath;
}

SString SharedUtil::ExtractExtention( const SString& strPathFilename )
{
    SString strExt;
    ExtractExtention ( strPathFilename, NULL, &strExt );
    return strExt;
}

SString SharedUtil::ExtractBeforeExtention( const SString& strPathFilename )
{
    SString strMain;
    ExtractExtention ( strPathFilename, &strMain, NULL );
    return strMain;
}

#ifdef _WIN32
filePath SharedUtil::MakeUniquePath( const filePath& path )
{
    unsigned int n = 0;
    filePath pre, post;
    filePath strPath;

    FileSystem::GetFileNameItem( path, false, &strPath );

    SString ext;

    bool hasExtention = SharedUtil::ExtractExtention( SString( path.convert_ansi() ), NULL, &ext );

    if ( hasExtention )
    {
        pre = strPath;
        post = ".";
        post += ext;
    }
    else
        pre = path;

    filePath strTest = path;

    while ( true )
    {
        std::wstring unicodePath = strTest.convert_unicode();

        bool exists = ( GetFileAttributesW( unicodePath.c_str() ) != INVALID_FILE_ATTRIBUTES );

        if ( !exists )
            break;

        std::string num_str = std::to_string( n++ );
        
        strTest = pre + filePath( L"_" ) + filePath( num_str ) + post;
    }

    return strTest;
}
#endif