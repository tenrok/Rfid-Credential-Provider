//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//
#pragma once

#include <tchar.h>
#include <credentialprovider.h>
#include <windows.h>
#include <strsafe.h>

#include "RfidCredential.h"
#include "helpers.h"

#define MAX_CREDENTIALS 1

RfidCredential* _rgpCredentials[MAX_CREDENTIALS]; // Pointers to the credentials which will be enumerated by 
												  // this Provider.

class RfidProvider : public ICredentialProvider
{
public:
	// IUnknown
	STDMETHOD_(ULONG, AddRef)()
	{
		return _cRef++;
	}

	STDMETHOD_(ULONG, Release)()
	{
		LONG cRef = _cRef--;
		if (!cRef)
		{
			delete this;
		}
		return cRef;
	}

	STDMETHOD(QueryInterface)(REFIID riid, void** ppv)
	{
		HRESULT hr;
		if (IID_IUnknown == riid ||
			IID_ICredentialProvider == riid)
		{
			*ppv = this;
			reinterpret_cast<IUnknown*>(*ppv)->AddRef();
			hr = S_OK;
		}
		else
		{
			*ppv = NULL;
			hr = E_NOINTERFACE;
		}
		return hr;
	}

public:
	IFACEMETHODIMP SetUsageScenario(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, DWORD dwFlags);
	IFACEMETHODIMP SetSerialization(const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs);

	IFACEMETHODIMP Advise(__in ICredentialProviderEvents* pcpe, UINT_PTR upAdviseContext);
	IFACEMETHODIMP UnAdvise();

	IFACEMETHODIMP GetFieldDescriptorCount(__out DWORD* pdwCount);
	IFACEMETHODIMP GetFieldDescriptorAt(DWORD dwIndex, __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** ppcpfd);

	IFACEMETHODIMP GetCredentialCount(
		__out DWORD* pdwCount,
		__out DWORD* pdwDefault,
		__out BOOL* pbAutoLogonWithDefault);
	IFACEMETHODIMP GetCredentialAt(
		DWORD dwIndex,
		__out ICredentialProviderCredential** ppcpc);

	friend HRESULT RfidProvider_CreateInstance(REFIID riid, __deref_out void** ppv);

	// Create/free enumerated credentials.
	HRESULT _EnumerateCredentials();
	void _ReleaseEnumeratedCredentials();
	HRESULT _EnumerateOneCredential(
		__in DWORD dwCredientialIndex,
		__in PWSTR pwzUsername,
		__in PWSTR pwzPassword,
		__in PWSTR pwzDomain
	);

	DWORD _dwNumCreds;

	ICredentialProviderEvents* Pcpe;
	UINT_PTR UpAdviseContext;
protected:
	RfidProvider();
	__override ~RfidProvider();
private:
	LONG _cRef;
};