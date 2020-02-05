#ifndef TEXTREADER_HPP
#define TEXTREADER_HPP
#include <string>
namespace advcpp{

class ITextReader
{
public:
	
	//virtual ITextReader() = default;
	//virtual ITextReader(ITextReader const& a_other) = default;
	//virtual ITextReader& operator=(ITextReader const& a_rhs) = default;
	virtual ~ITextReader() = 0;

	virtual std::string& Read() = 0;
	virtual bool IsDone() const = 0;
};

class StringReader : public ITextReader
{
public:
	
	StringReader(std::string const& a_str);
	//virtual StringReader(StringReader const& a_other) = default;
	//virtual StringReader& operator=(StringReader const& a_rhs) = default;
	//virtual ~StringReader() = default;

	virtual std::string& Read();
	virtual bool IsDone() const;

private:
	std::string m_str;
};

class FileReader : public ITextReader
{
public:

	FileReader(std::string const& a_fileName);
	//FileReader(FileReader const& a_other) = default;
	//virtual FileReader& operator=(FileReader const& a_rhs) = default;
	//virtual ~FileReader() = default;

	virtual std::string& Read();
	virtual bool IsDone() const;

private:
	std::string m_str;
	std::string m_inFileName;
};

class ConsoleReader : public ITextReader
{
public:

	//ConsoleReader() = default;
	//ConsoleReader(ConsoleReader const& a_other) = default;
	//virtual ConsoleReader& operator=(ConsoleReader const& a_rhs) = default;
	//virtual ~ConsoleReader() = default;

	virtual std::string& Read();
	virtual bool IsDone() const;

private:
	std::string m_str;
};


}//namespace advcpp
#endif //TEXTREADER_HPP

