#include "ISink.hpp"
#include "video/video.hpp"

namespace AgaresOS { namespace Debug {
	class VideoSink : public ISink {
		public:
			VideoSink(Video &video) : video(video) {
			}

			void PutCharacter(char c);
		private:
			Video &video;
	};

	inline void VideoSink::PutCharacter(char c) {
		video.PutChar(c, Video::Color::LightGray, Video::Color::Black);	
	}
}}
