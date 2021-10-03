#ifndef MEP_TIMER_CONTAINER_H
#define MEP_TIMER_CONTAINER_H
#include<string>
#include<iostream>
#include<filesystem>
#include<list>
#include<MEPTools/Log.h>
#include<MEPTools/TSQueue.h>
#include<thread>
#include<SFML/Network.hpp>
#include<Windows.h>
namespace MEP
{

	struct DataBase
	{
		std::string __name;
		std::string __path;
		const int __line;
		double __LastTime;
		DataBase(const std::string& name,
			const std::string& path,
			int line,
			double LastTime):
			__name(name),
			__path(path),
			__line(line),
			__LastTime(LastTime)
		{}
	};

	struct DataTask : public DataBase
	{
		const char* TypeChar[4] = { "Add", "Generate", "Reset", "Shutdown" };
	public:
		enum class Type
		{
			Add = 0,
			Generate = 1,
			Reset = 2,
			Shutdown = 3
		};
		void init(std::string& input)
		{
			input += "{";
		}
		void close(std::string& input)
		{
			input += "}";
		}
		void addAttribute(std::string& input, const std::string& name, const std::string& content)
		{
			input += "\"" + name + "\":\"" + content + "\"";
		}
		void finishLine(std::string& input)
		{
			input += ", ";
		}
	private:
		const Type __type;
	public:
		DataTask(Type taskType, const std::string& name = "", const std::string& path = "", int line = 0, double lastTime = 0.f):
			DataBase(name, path, line, lastTime),
			__type(taskType)
		{}
		std::string jsonify()
		{
			std::string local;
			init(local);
			addAttribute(local, "type", TypeChar[static_cast<int>(__type)]);
			if (__type == Type::Add)
			{
				finishLine(local);
				addAttribute(local, "name", __name);
				finishLine(local);
				addAttribute(local, "path", __path);
				finishLine(local);
				addAttribute(local, "line", std::to_string(__line));
				finishLine(local);
				addAttribute(local, "lastTime", std::to_string(__LastTime));
			}
			close(local);
			return local;
		}
	};
	class __TimerContainer
	{
		std::thread __taskManager;
		MEP::LFQueuev2<DataTask> __tasks;
		bool __status;
		bool __forceStop;
		void process()
		{
			while (__status)
			{
				Log(Error) << "Process";
				auto task = __tasks.pop();
				if (task != nullptr)
				{
					std::cout << task->jsonify() << "\n";
				}
			}
			while (auto task = __tasks.pop())
			{
				if(task)
					std::cout << task->jsonify() << "\n";
			}
		}
	public:
		__TimerContainer() :
			__taskManager(&__TimerContainer::process, this),
			__status(true),
			__forceStop(false)
		{
		}
		~__TimerContainer()
		{
			__status = false;
			__taskManager.join();
		}
		void add(const DataTask& task)
		{
			__tasks.push(task);
		}
		void generate()
		{
			__tasks.push(DataTask(DataTask(DataTask::Type::Generate)));
		}
		void reset()
		{
			__tasks.push(DataTask(DataTask(DataTask::Type::Reset)));
		}
	};
	namespace MEPTools
	{
		static __TimerContainer TCPtimer;
	}
}

#endif