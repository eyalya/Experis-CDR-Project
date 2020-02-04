
#include <iostream>
enum Choice
{
    SUBSCRIBER = 1,
    OPERATOR,
    ALL_SUBSCRIBERS,
    ALL_OPERATORS,
    EXIT
};

void GetSubscriber()
{
    std::cout << "subscriber chosen\n";
}
void GetOperator()
{
    std::cout << "operator chosen\n";
}
void GetAllSubscribers()
{
    std::cout << "all subscribers chosen\n";
}
void GetAllOperators()
{
    std::cout << "all operators chosen\n";
}
void ShutDown()
{
    std::cout << "exit chosen\n";
}
void WrongInput()
{
    std::cout << "wrong input chosen\n";
}

int Manu()
{
    bool go = true;

    while(go)
    {
        std::cout <<    "--------------------------\n" <<
                        "Welcome to CDR Application\n" <<
                        "--------------------------\n" <<
                        "1.........Get subscriber data\n" <<
                        "2.........Get operator data\n" <<
                        "3.........Get all subscribers data\n" <<
                        "4.........Get operators data\n" <<
                        "5.........Exit\n" <<
                        "--------------------------\n" <<
                        "Enter your choice:\n";

        int choice;
        std::cin >> choice;
        std::cout << "\n";

        switch (choice)
        {
            case SUBSCRIBER:
                GetSubscriber();
                break;
            
            case OPERATOR:
                GetOperator();
                break;
            
            case ALL_SUBSCRIBERS:
                GetAllSubscribers();
                break;

            case ALL_OPERATORS:
                GetAllOperators();
                break;
            
            case EXIT:
                ShutDown();
                std::cout << "\nThank you, come again!\n";
                go = false;
                break;
            
            default:
                WrongInput(); 
        }       
    }
    return 0;
}

int main()
{
    Manu();
}