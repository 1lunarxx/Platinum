#include "Source/Public/Finders.h"

uintptr_t Finders::FindProcessRequest()
{
	auto ProcessRequestString = Memcury::Scanner::FindStringRef("STAT_FCurlHttpRequest_ProcessRequest");
	if (!ProcessRequestString.IsValid())
	{
		ProcessRequestString = Memcury::Scanner::FindStringRef("Could not set libcurl options for easy handle, processing HTTP request failed. Increase verbosity for additional information.");
	}

	return ProcessRequestString.ScanFor({ 0x48, 0x81, 0xEC }, false).ScanFor({ 0x40 }, false).Get();
}