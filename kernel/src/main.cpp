#include <stdint.h>
#include <video/video.hpp>
#include <debug/VideoSink.hpp>
#include <debug/DebugOutput.hpp>
#include <debug/debug_fragment/StringFragment.hpp>
#include <debug/debug_fragment/IntegerFragment.hpp>

using AgaresOS::Debug::VideoSink;
using AgaresOS::Debug::DebugOutput;
using AgaresOS::Debug::StringFragment;
using AgaresOS::Debug::IntegerFragment;
using AgaresOS::Video;

extern "C" void __cxa_pure_virtual() {
	// fixme add kernel panic
}

extern "C" int kmain(uint32_t memoryMapAddress) {
	(void)memoryMapAddress;

	Video video;
	VideoSink sink(video);
	DebugOutput output(sink);

	video.Clear();
	output << StringFragment("Hello from kernel.\n") << IntegerFragment(1024);
	output << StringFragment("\n0x") << IntegerFragment((uintptr_t)&video);

	while(true) {}
}
