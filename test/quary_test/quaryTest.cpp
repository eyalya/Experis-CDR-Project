
#include <iostream>
#include "ds_container.hpp"
#include "quary.hpp"
#include "UI.hpp"

int main()
{
    advcpp::DsContainer ds;    
    advcpp::Quary quary(ds);
    advcpp::UI ui(quary);
    
    ui.Run();
}