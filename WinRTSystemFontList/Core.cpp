
#include "Core.h"
#include <collection.h>
#include <dwrite.h>

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

IVector<String^>^ Flantter::Cascade::SystemFont::Core::GetSystemFontNameCollection(String^ locale)
{
	Vector<String^>^ systemFontNameCollection = ref new Vector<String^>();

	IDWriteFontCollection* pFontCollection = NULL;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteFontFamily* pFontFamily = NULL;
	IDWriteLocalizedStrings* pFamilyNames = NULL;
	UINT32 familyCount = 0;
	UINT32 index = 0;
	UINT32 length = 0;
	BOOL exists = false;
	HRESULT hr;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (!SUCCEEDED(hr))
		throw ref new NotImplementedException(ref new String(L"Failed to create \"IDWriteFactory\"."));

	hr = pDWriteFactory->GetSystemFontCollection(&pFontCollection);
	if (!SUCCEEDED(hr))
		throw ref new NotImplementedException(ref new String(L"Failed to get \"IDWriteFontCollection\"."));

	familyCount = pFontCollection->GetFontFamilyCount();
	if (!SUCCEEDED(hr))
		throw ref new NotImplementedException(ref new String(L"Failed to get \"FontFamilyCount\"."));
	
	for (UINT32 i = 0; i < familyCount; ++i)
	{
		hr = pFontCollection->GetFontFamily(i, &pFontFamily);
		if (!SUCCEEDED(hr))
			throw ref new NotImplementedException(ref new String(L"Failed to get \"FontFamily\"."));

		hr = pFontFamily->GetFamilyNames(&pFamilyNames);
		if (!SUCCEEDED(hr))
			throw ref new NotImplementedException(ref new String(L"Failed to get \"FamilyNames\"."));

		hr = pFamilyNames->FindLocaleName(locale->Begin(), &index, &exists);
		if (SUCCEEDED(hr) && !exists)
			hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
		if (!SUCCEEDED(hr))
			throw ref new NotImplementedException(ref new String(L"Failed to get \"LocaleName\"."));
		if (!exists)
			continue;

		hr = pFamilyNames->GetStringLength(index, &length);
		if (!SUCCEEDED(hr))
			throw ref new NotImplementedException(ref new String(L"Failed to get \"StringLength\"."));

		wchar_t* name = new (std::nothrow)wchar_t[length + 1];
		if (name == NULL)
			throw ref new NotImplementedException(ref new String(L"Out of memory."));

		hr = pFamilyNames->GetString(index, name, length + 1);
		if (!SUCCEEDED(hr))
			throw ref new NotImplementedException(ref new String(L"Failed to get \"String\"."));

		systemFontNameCollection->Append(ref new String(name));
	}

	return systemFontNameCollection;
 }