#ifndef PARSER_HPP
#define PARSER_HPP
#include <cstddef> //size_t
#include <string>
#include <vector>

namespace advcpp{

class IParser
{
public:
	//virtual IParser() = default;
	//virtual IParser(IParser const& a_other) = default;
	//virtual IParser& operator=(IParser const& a_rhs) = default;
	virtual ~IParser() = 0;

	virtual size_t Parse(std::string const& a_record, std::vector<std::string>& a_fields) = 0;
	
};

inline IParser::~IParser()
{
}


class RecordParseByDelim : public IParser
{
public:
	explicit RecordParseByDelim(char a_delim);
	//virtual RecordParseByDelim(RecordParseByDelim const& a_other) = default;
	//virtual RecordParseByDelim& operator=(RecordParseByDelim const& a_rhs) = default;
	//virtual ~RecordParseByDelim() = default;

	virtual size_t Parse(std::string const& a_record, std::vector<std::string>& a_fields);


private:
	char m_delim;
};

inline RecordParseByDelim::RecordParseByDelim(char a_delim)
: m_delim(a_delim)
{	
}


} //namespace advcpp
#endif //PARSER_HPP

