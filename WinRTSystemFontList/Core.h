#pragma once

#include "pch.h"
#include <collection.h>

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace Flantter
{
	namespace Cascade
	{
		namespace SystemFont
		{
			public ref class Core sealed
			{
			public:
				static IVector<String^>^ GetSystemFontNameCollection(String^ locale);
			};
		}
	}
}