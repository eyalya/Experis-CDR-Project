#ifndef COMMON_H
#define COMMON_H

namespace advcpp
{

#define NOEXCEPTION throw() 
#define THROW1(x) throw(x) 
#define THROW2(x, y) throw(x, y)
#define THROW3(x, y, z) throw(x, y, z)

class UnCopyable
{
protected:
    UnCopyable() NOEXCEPTION;

private:
    UnCopyable(const UnCopyable & a_unCopyable); // = delete
    UnCopyable & operator= (const UnCopyable & a_unCopyable); // = delete
};

inline UnCopyable::UnCopyable() NOEXCEPTION
{
}

} // namespace advcpp

#endif //  COMMON_H
