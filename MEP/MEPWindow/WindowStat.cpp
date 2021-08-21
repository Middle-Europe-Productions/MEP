#include<MEPWindow/WindowStat.h>

namespace MEP
{
	void WindowStats::updateStatistics(sf::Time dt) {
		mStatisticsUpdateTime += dt;
		mStatisticsNumFrames += 1;
		if (mStatisticsUpdateTime >= sf::seconds(1.0f))
		{
			mStatisticsUpdateTime -= sf::seconds(1.0f);
			mStatisticsNumFrames = 0;
		}
	}

	unsigned int WindowStats::getFrameRate() const {
		return mStatisticsNumFrames;
	}

	sf::Time& WindowStats::getGlobalTime() {
		return globalTime;
	}
}