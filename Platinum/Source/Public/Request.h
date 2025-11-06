#pragma once
#include "framework.h"
#include "Source/Public/Containers.h"
#include "Source/Public/Finders.h"

namespace Request
{
	namespace Originals
	{
		inline static bool (*ProcessRequest)(Containers::FCurlHttpRequest* HttpRequest);
		inline static bool (*EOSProcessRequest)(Containers::FCurlHttpRequest* HttpRequest);
	}

	bool ProcessRequest(Containers::FCurlHttpRequest*);
	bool EOSProcessRequest(Containers::FCurlHttpRequest*);
	void Patch();
}