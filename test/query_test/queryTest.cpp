
#include <iostream>
#include "ds_container.hpp"
#include "UI.hpp"

int main()
{
    advcpp::DsContainer ds;
    advcpp::Query query(ds);
    advcpp::UI ui(query);

    ui.Run();
}