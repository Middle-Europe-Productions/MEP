#include<MEPGraphics/ResourceException.h>
namespace MEP
{
	ResourceException::ResourceException(const std::string& name, const std::string& msg, const ExceptionType& type) :
		exceptionType(type),
		ResourceName(name),
		Message(msg)
	{}

	ResourceException::ResourceException(const char* name, const char* msg, const ExceptionType& type) :
		exceptionType(type),
		ResourceName(name),
		Message(msg)
	{}

	std::ostream& operator<<(std::ostream& out, const ResourceException& x) {
		out << "ResourceException ResourceName: " << x.ResourceName << ", Message: " << x.Message << std::endl;
		return out;
	}
}