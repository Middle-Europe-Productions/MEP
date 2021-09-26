#ifndef MEP_COMMAND_LINE_H
#define MEP_COMMAND_LINE_H

namespace MEP
{
	namespace TOOLS
	{
		class CMDSettup
		{
			static bool __liveViewEnabled;
			CMDSettup() = delete;
		public: 
			static bool liveViewEnabled()
			{
				return __liveViewEnabled;
			}
			static void allowLiveView()
			{
				__liveViewEnabled = true;
			}
		};
	}
}

#if MEP::TOOLS::CMDSettup::liveViewEnabled()
#define ALLOW_LIVE_VIEW
#endif

#endif