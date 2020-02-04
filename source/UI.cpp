#include "UI.hpp"
#include "query.hpp"
#include "record.hpp"
namespace advcpp{

void UI::SubscriberChosen()
{    
    uint msisdn;

    while(FOREVER)
    {
        //TODO: GetMSISDN function
        std::cout << "\033[1;32mEnter MSISDN: \n\033[0m";
        std::cin >> msisdn;                

        if (IsValidInput())
        {
            break;
        }
        WrongInput();
    }

    SubscriberRecord subRec;
    if (m_query.GetSubscriber(msisdn, subRec))
    {
        Write(subRec);
        return;        
    }
    WriteNotFound();
}

void UI::OperatorChosen()
{     
    std::cout << "\033[1;33mOperator chosen\n\033[0m";
}

void UI::AllSubscribersChosen()
{    
    std::cout << "\033[1;33mAll subscribers chosen\n\033[0m";
}
 
void UI::AllOperatorsChosen()
{    
    std::cout << "\033[1;33mAll operator chosen\n\033[0m";
}

void UI::Run()
{    
    std::cout <<        "\033[1;36m-------------------------------------\n\033[0m" <<
                        "\033[1;32m      Welcome to CDR Application\n\033[0m";

    while(FOREVER)
    {
        std::cout <<    "\033[1;36m-------------------------------------\n\033[0m" <<
                        "\033[1;36m1.........Get subscriber data\n\033[0m" <<
                        "\033[1;36m2.........Get operator data\n\033[0m" <<
                        "\033[1;36m3.........Get all subscribers data\n\033[0m" <<
                        "\033[1;36m4.........Get operators data\n\033[0m" <<
                        "\033[1;36m5.........Exit\n\033[0m" <<
                        "\033[1;36m-------------------------------------\n\033[0m";



        std::cout << "\033[1;32mEnter your choice: \n\033[0m";
        uint choice;
        std::cin >> choice;

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
                WrongInput();
                break;
        }
    }
}

}// namespace advcpp