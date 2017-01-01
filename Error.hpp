#ifndef ERROR_HPP___
#define ERROR_HPP___

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

class Error : public std::exception
{
private:
	static std::fstream error_log;
	std::string m_msg;
public:
	explicit Error(const char* message);
	explicit Error(const std::string& message);
	const char* what() const override;
	virtual ~Error() = default;
};

#endif
