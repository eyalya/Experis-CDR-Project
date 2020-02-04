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
    std::cout << "\033[1;32m\nThank you, come again!\n\033[0m\n";
}

inline void UI::WriteNotFound()
{
    
    std::cout << "\033[1;31mNot found\033[0m\n";
}

/////////////////////////////////////////////////////////////////////

inline void WrongInput()
{
    std::cout << "\033[1;31mwrong input, try again\033[0m\n";
}

inline bool IsInvalidInput()
{
    bool fail = std::cin.fail();
    //bool bad = std::cin.bad();
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<int>::max(), '\n'); 

    // bool fail2 = std::cin.fail(); 
    // bool bad2 = std::cin.bad(); 

    // fail2 = true; 
    // bad2 = true;

    // if (fail2 && bad2 && bad)
    // {
    //     return fail;
    // }

    return fail;
}

inline bool IsValidInput()
{
    return !IsInvalidInput();
}

}//namespace advcpp
#endif //UI_INL