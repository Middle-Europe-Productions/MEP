#ifndef MEP_TIMER_CONTAINER_H
#define MEP_TIMER_CONTAINER_H
#include<string>
#include<iostream>
#include<filesystem>
#include<list>
#include<MEPTools/SQLite.hpp>
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
			double LastTime);
	};
	struct DataPackage: public DataBase
	{
		int __execNumber;
		double __TotalTime;
		DataPackage() = delete;
		DataPackage(const std::string& name,
			const std::string& path,
			int line,
			double LastTime);
		DataPackage(const DataBase& x);
		void update(const DataBase& x);
		bool operator==(const DataPackage& x);
		bool operator==(const DataBase& x);
		bool operator<(const DataPackage& x);
	};

	class __TimerContainer;
	class __Connection
	{
		int __ID;
		Connection connection;
	public:
		__Connection();
		void generate();
	};
	class __TimerContainer
	{
		friend __Connection;
		static unsigned int __Generate_Version_ID;	
		static __Connection __connection;
		static std::list<DataPackage> __local;
	public:
		static void add(const DataBase& in);
		static void reset();
		static void generate();
		static const std::list<DataPackage>& getData();
	};
}

#endif