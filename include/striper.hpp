#ifndef STRIPER_HPP
#define STRIPER_HPP
//#include <sstream>
#include <cstddef> //size_t
#include <string>

namespace advcpp{

class IStriper
{
public:
	//virtual IStriper() = default;
	//virtual IStriper(IStriper const& a_other) = default;
	//virtual IStriper& operator=(IStriper const& a_rhs) = default;
	virtual ~IStriper() = 0;

	virtual void Strip(std::string& a_record) = 0;	
};

inline IStriper::~IStriper()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////

class ReplacerDelim : public IStriper
{
public:
	explicit ReplacerDelim(char a_oldDelim, char a_newDelim);
	//virtual ReplacerDelim(ReplacerDelim const& a_other) = default;
	//virtual ReplacerDelim& operator=(ReplacerDelim const& a_rhs) = default;
	//virtual ~ReplacerDelim() = default;

	virtual void Strip(std::string& a_record);

private:
	char m_oldDelim;
	char m_newDelim;
};

////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace advcpp
#endif //STRIPER_HPP

