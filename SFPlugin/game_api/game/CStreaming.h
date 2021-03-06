/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        sdk/game/CStreaming.h
*  PURPOSE:     Game streaming interface
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CStreaming_H
#define __CStreaming_H

class CStreaming
{
public:
	void RequestAnimations(int iAnimationLibraryBlock, DWORD dwFlags)
	{
		iAnimationLibraryBlock += 25575;
		RequestModel(iAnimationLibraryBlock, dwFlags);
	}
    virtual void            RequestModel                    ( DWORD dwModelID, DWORD dwFlags ) = 0;
    virtual void            LoadAllRequestedModels          ( BOOL bOnlyPriorityModels = 0, const char* szTag = NULL ) = 0;
    virtual BOOL            HasModelLoaded                  ( DWORD dwModelID ) = 0;
    virtual void            RequestSpecialModel             ( DWORD model, const char * szTexture, DWORD channel ) = 0;
};

#endif
