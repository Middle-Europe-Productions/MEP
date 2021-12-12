#ifndef MEP_TIMER_CONTAINER_H
#define MEP_TIMER_CONTAINER_H

#ifndef MEP_LIVE_VIEW_PORT
#define MEP_LIVE_VIEW_PORT 54000
#endif

#include<string>
#include<iostream>
#include<filesystem>
#include<list>
#include<MEPTools/Log.h>
#include<MEPTools/TSQueue.h>
#include<thread>
#include<MEPTools/LightTCPClient.h>
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
		Type type() const
		{
			return __type;
		}
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
		MEP::TSQueue<DataTask> __tasks;
		TCP_Client __client;
		int __port;
		bool __status;
		bool __forceStop;
		std::thread __taskManager;
		void process()
		{
			Log(Debug) << __LINE__;
			bool tryReconnect = true;
			bool tryPop = true;
			while (__status == true)
			{
				Log(Debug) << __LINE__;
				if (!__client.IsConnected())
				{
					__client.MEPconnect();
				}
				while (auto task = __tasks.wait_and_pop())
				{
					Log(Debug) << task->jsonify();
					if (!__status)
					{
						tryReconnect = false; // when we shutdown the server it is not going to force sending a messages
					}
					if (task->type() == DataTask::Type::Shutdown)
					{
						tryReconnect = false; // Do not try to reconnect when we want to shut down the system.
						tryPop = false; //we do not want to try to pop any other message
						__status = false;
						__client.shutdown();
					}
					std::string message = task->jsonify();
					if (__client.MEPsend(message) == false)
					{
						if(!__client.IsConnected() and tryReconnect)
							__client.MEPconnect();
					}
					Log(10) << "Messaage send! Content: " << message;
					if (!tryPop)
					{
						return;
					}
				}
			}
			Log(Info) << "process done";
		}
		__TimerContainer() :
			__port(MEP_LIVE_VIEW_PORT),
			__status(true),
			__forceStop(false),
			__taskManager(&__TimerContainer::process, this)
		{
			Log(Info) << "Enabling MEP live debugging tool";
		}
		static __TimerContainer& get()
		{
			static __TimerContainer master;
			return master;
		}
	public:
		~__TimerContainer()
		{
			Log(Error) << "Closing server";
			__client.stopReconnecting();
			add(DataTask(DataTask::Type::Shutdown));
			__taskManager.join();
			Log(Error) << "done";
		}
		static void add(const DataTask& task)
		{
#if defined(MEP_ALLOW_LIVE_VIEW)
			get().__tasks.push(task);
#else
			Log(Warning) << "You are trying to enable MEP Live Tools without MEP_ALLOW_LIVE_VIEW tag.";
#endif
		}
		static void generate()
		{
#if defined(MEP_ALLOW_LIVE_VIEW)
			get().__tasks.push(DataTask(DataTask(DataTask::Type::Generate)));
#else
			Log(Warning) << "You are trying to enable MEP Live Tools without MEP_ALLOW_LIVE_VIEW tag.";
#endif	
		}
		static void reset()
		{
#if defined(MEP_ALLOW_LIVE_VIEW)
			get().__tasks.push(DataTask(DataTask(DataTask::Type::Reset)));
#else
			Log(Warning) << "You are trying to enable MEP Live Tools without MEP_ALLOW_LIVE_VIEW tag.";
#endif	
		}
	};
}

#endif