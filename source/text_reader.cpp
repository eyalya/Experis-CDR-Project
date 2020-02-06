#include <string>
#include <iostream>
#include <cassert>
#include "text_reader.hpp"

namespace advcpp{

ITextReader::~ITextReader()
{
}

FileReader::FileReader(const char* a_fileName)
: m_ifs(a_fileName, std::ios::in)
{
}

std::string& FileReader::Read()
{
	assert(m_ifs.is_open());
	assert(m_ifs.good()); //FIXME: is needed???
    assert(!m_ifs.eof());

  	getline(m_ifs,m_line);
    m_line += '\n'; //FIXME: is needed???	
	return m_line;
}

bool FileReader::IsDone() const
{
	return m_ifs.eof();
}

/*
StringReader::StringReader(std::string const& a_str)
: m_str(a_str)
{	
}

std::string& StringReader::Read()
{
	return m_str;
}

bool StringReader::IsDone() const
{
	return true; //TODO: review if needed
}
*/

/*
std::string& ConsoleReader::Read()
{
	std::cout << "\tEnter text: ";
	getline(std::cin, m_str);
	
	return m_str;
}
bool ConsoleReader::IsDone() const
{
	return true; //TODO: review if needed
}
*/

}//namespace cpp
