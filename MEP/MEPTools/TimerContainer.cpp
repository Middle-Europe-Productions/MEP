#include<MEPTools/TimerContainer.h>
#include<MEPTools/Log.h>
namespace MEP
{
	DataBase::DataBase(const std::string& name,
		const std::string& path,
		int line,
		double LastTime) :
		__name(name),
		__path(path),
		__line(line),
		__LastTime(LastTime)
	{}
	DataPackage::DataPackage(const std::string& name,
		const std::string& path,
		int line,
		double LastTime) :
		DataBase(name, path, line, LastTime),
		__execNumber(1),
		__TotalTime(LastTime)
	{}
	DataPackage::DataPackage(const DataBase& x) :
		DataBase(x.__name, x.__path, x.__line, x.__LastTime),
		__execNumber(1),
		__TotalTime(x.__LastTime)
	{}
	void DataPackage::update(const DataBase& x)
	{
		__execNumber += 1;
		__TotalTime += x.__LastTime;
		__LastTime = x.__LastTime;
	}
	bool DataPackage::operator==(const DataPackage& x)
	{
		return __line == x.__line and __path == x.__path;
	}
	bool DataPackage::operator==(const DataBase& x)
	{
		return __line == x.__line and __path == x.__path;
	}
	bool DataPackage::operator<(const DataPackage& x)
	{
		return __TotalTime < x.__TotalTime;
	}

	unsigned int __TimerContainer::__Generate_Version_ID = 0;
	__Connection __TimerContainer::__connection = __Connection();
	std::list<DataPackage> __TimerContainer::__local = std::list<DataPackage>();

	void  __TimerContainer::add(const DataBase& in)
	{
		for (auto& x : __local)
		{
			if (x == in)
			{
				x.update(in);
				return;
			}
		}
		__local.push_back(DataPackage(in));
	}
	const std::list<DataPackage>& __TimerContainer::getData()
	{
		return __local;
	}
	void __TimerContainer::reset()
	{
		__local.clear();
	}
	void __TimerContainer::generate()
	{
		__connection.generate();
	}
	__Connection::__Connection() :
		__ID(0)
	{
		try {
			std::filesystem::path path = std::filesystem::current_path();
			path.append("..\\data.db");
			Log(Info) << "Creating database at: " << path;
			connection.Open(path.c_str());
		}
		catch (Exception x)
		{
			Log(Error) << x.Message;
		}
		try {
			Execute(connection, "CREATE TABLE Package ( \
					frameID integer NOT NULL, \
					name text NOT NULL,\
					path text NOT NULL,\
					line integer NOT NULL,\
					execnumber integer NOT NULL,\
					totalTime float NOT NULL,\
					lastTime float NOT NULL, \
					FOREIGN KEY(frameID) REFERENCES Frame (ID))");
		}
		catch (Exception x)
		{
			Execute(connection, "DELETE FROM Package");
		}
		try {
			Execute(connection, "CREATE TABLE Frame ( \
					ID integer UNIQUE PRIMARY KEY)");
		}
		catch (Exception x)
		{
			Execute(connection, "DELETE FROM Frame");
		}
	}

	void __Connection::generate()
	{
		try {
			Statement frame(connection, "insert into Frame values (?)", __ID);
			frame.Execute();
			for (auto& x : __TimerContainer::__local)
			{
				Statement row(connection, "insert into Package values (?, ?, ?, ?, ?, ?, ?)",
					__ID,
					x.__name,
					x.__path,
					x.__line,
					x.__execNumber,
					x.__TotalTime,
					x.__LastTime);
				row.Execute();
			}
			__ID++;
		}
		catch (const Exception& x)
		{
			Log(Error) << x.Message;
		}
	}
}
