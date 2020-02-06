#ifndef UI_HPP
#define UI_HPP
#include <iostream>
#include <cassert>
#include "query.hpp"


namespace advcpp{

typedef unsigned int uint;
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
    UI (Query& a_query);
    //rule 3 = default;

    void Run();   

private:    
    void SubscriberChosen();
    void OperatorChosen();
    void AllSubscribersChosen();
    void AllOperatorsChosen();
    void ExitChosen();

    uint GetMSISDN();
    uint GetOperator();

    template <typename T>
    void Write(T const& a_data);

    void WriteNotFound();

private:
    Query& m_query;
};

/////////////////////////////////////////////////////

inline bool IsInvalidInput();
inline bool IsValidInput();
inline void WrongInput();

}//namespace advcpp
#include "inl/UI.inl"
#endif //UI_HPP