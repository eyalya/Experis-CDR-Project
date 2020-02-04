#ifndef UI_INL
#define UI_INL
#include "limits" //numeric_limits
namespace advcpp{

inline UI::UI(Query& a_query)
: m_query(a_query)
{    
}

template <typename T>
void UI::Write(T const& a_data)
{
    std::cout << a_data;
}

inline void UI::ExitChosen()
{
    std::cout << "\nThank you, come again!\n";
}

inline void UI::WriteNotFound()
{
    std::cout << "Not found\n";
}

/////////////////////////////////////////////////////////////////////

inline void WrongInput()
{
    std::cout << "\033[1;31mwrong input, try again\033[0m\n";
}

inline bool IsInvalidInput()
{
    bool res = std::cin.fail();
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');   
    return res;
}

}//namespace advcpp
#endif //UI_INL