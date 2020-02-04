#ifndef UI_HPP
#define UI_HPP
#include <iostream>
#include <cassert>
#include "quary.hpp"
#include <iostream>

namespace advcpp{

static const bool FOREVER = true;

enum Choice
{
    SUBSCRIBER = 1,
    OPERATOR,
    ALL_SUBSCRIBERS,
    ALL_OPERATORS,
    EXIT
};

class UI
{
public:
    explicit UI(Quary& a_quary);
    //rule 3 = default;

    void Run();

private:    
    void SubscriberChosen();
    void OperatorChosen();
    void AllSubscribersChosen();
    void AllOperatorsChosen();
    void ExitChosen();    

private:
    Quary& m_quary;
};

///////////////////////////////////////////////////////////////

inline UI::UI(Quary& a_quary) 
: m_quary(a_quary)
{
}

inline void UI::SubscriberChosen()
{    
    uint msisdn;
    while(FOREVER)
    {
        std::cout << "Enter MSISDN: ";
        std::cin >> msisdn;
        std::cout << "\n";

        if (IsInvalidInput)
        {
            std::cout << "Wrong input try again\n";
        }       
    }
    m_quary.GetSubscriber(msisdn);
}

inline void UI::ExitChosen()
{
    std::cout << "\nThank you, come again!\n";
}

inline bool IsInvalidInput()
{
    return std::cin.fail();    
}

inline void WrongInput()
{
    std::cout << "\033[1;31mwrong input, try again\033[0m\n";
}
/*
bool UI::GetMSISDN(uint& a_msisdn)
{
    std::cout << "Enter subscriber's MSISDN\n";
    uint msisdn;
    std::cin >> msisdn;
    return msisdn;
}

uint UI::GetMCC()
{

}

void UI::ShutDown()
{
    std::cout <<    "exit chosen\n" <<
                    "Shuting down...";
}

*/



inline void UI::Run()
{    
    std::cout <<        "\n--------------------------\n" <<
                        "Welcome to CDR Application\n" <<
                        "--------------------------\n\n";

    while(FOREVER)
    {
        std::cout <<    "\n--------------------------\n" <<
                        "1.........Get subscriber data\n" <<
                        "2.........Get operator data\n" <<
                        "3.........Get all subscribers data\n" <<
                        "4.........Get operators data\n" <<
                        "5.........Exit\n" <<
                        "--------------------------\n" <<
                        "Enter your choice:\n";

        uint choice;
        std::cin >> choice;
        std::cout << "\n";

        if (IsInvalidInput())
        {
            WrongInput();
            continue;
        }
        
        switch (choice)
        {
            case SUBSCRIBER:
                SubscriberChosen();
                break;
            
            case OPERATOR:
                OperatorChosen();                
                break;
            
            case ALL_SUBSCRIBERS:
                AllSubscribersChosen();
                break;

            case ALL_OPERATORS:
                AllOperatorsChosen();
                break;
            
            case EXIT:
                ExitChosen();
                return;
            
            default:
                assert(false);
        }
    }
}


}//namespace advcpp
#endif //UI_HPP