#include "UI.hpp"
#include "query.hpp"
#include "record.hpp"
namespace advcpp{

inline void UI::SubscriberChosen()
{    
    uint msisdn;

    while(FOREVER)
    {
        //TODO: GetMSISDN function
        std::cout << "Enter MSISDN: ";
        std::cin >> msisdn;                

        if (IsInvalidInput())
        {
            std::cout << "Wrong input try again\n";
        }
        break;
    }

    SubscriberRecord subRec;
    if (m_query.GetSubscriber(msisdn, subRec))
    {
        Write(subRec);
        return;        
    }
    WriteNotFound();
}

void UI::Run()
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
/*            
            case OPERATOR:
                OperatorChosen();                
                break;
            
            case ALL_SUBSCRIBERS:
                AllSubscribersChosen();
                break;

            case ALL_OPERATORS:
                AllOperatorsChosen();
                break;
*/            
            case EXIT:
                ExitChosen();
                return;
            
            default:
                assert(false);
        }
    }
}

}// namespace advcpp