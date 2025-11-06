#pragma once
#include "framework.h"
#include "Source/Public/Containers.h"

namespace Request
{
	namespace Originals
	{
		inline static bool (*ProcessRequest)(Containers::FCurlHttpRequest* HttpRequest);
	}

	bool ProcessRequest(Containers::FCurlHttpRequest*);
	void Patch();
}