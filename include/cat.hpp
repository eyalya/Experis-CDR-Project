#ifndef CAT_H
#define CAT_H
#include <cassert>
#include <iostream>

class Cat
{
public:
	explicit Cat(int a_id=0, int a_age=0);
	
	int ID() const;
	int Age() const;
	void ID(int const& a_ID);
	void Age(int const& a_age);

	std::ostream& Print(std::ostream& a_os) const;

private:
	int 	m_id;
	int		m_age;
};

Cat::Cat(int a_id, int a_age)
: m_id(a_id)
, m_age(a_age)
{
}


inline int Cat::ID() const
{
	return m_id;
}

inline int Cat::Age() const
{
	return m_age;
}

inline void Cat::ID(int const& a_id)
{
	m_id = a_id;
}

inline void Cat::Age(int const& a_age)
{
	m_age = a_age;
}

std::ostream& Cat::Print(std::ostream& a_os) const
{
	a_os << "ID:"<< ID() << ',' << Age() << ';' ;
	return a_os;	
}




//globals
inline bool operator == (Cat const& a_lhs, Cat const& a_rhs)
{
	return (a_lhs.ID() == a_rhs.ID());
}

inline bool operator != (Cat const& a_lhs, Cat const& a_rhs)
{
	return !(a_lhs.ID() == a_rhs.ID());
}

inline bool operator < (Cat const& a_lhs, Cat const& a_rhs)
{
	return (a_lhs.ID() < a_rhs.ID());
}

inline bool operator > (Cat const& a_lhs, Cat const& a_rhs)
{
	return (a_lhs.ID() > a_rhs.ID());
}

std::ostream& operator<<(std::ostream& a_os, Cat const& a_cat)
{
	return a_cat.Print(a_os);
}


	
#endif //CAT_H
