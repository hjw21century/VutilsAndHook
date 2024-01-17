#pragma once

#include "Vutils.h"

#include <conio.h>

#include <vu>
#include <algorithm>

using namespace vu;

DEF_SAMPLE(ServiceManager)
{
  if (!vu::is_administrator())
  {
    std::tcout << ts("You are not Administrator") << std::endl;
  }
  else
  {
    std::tstring driver_name = ts("WKE Driver");
    std::tstring driver_display_name = ts("Windows Kernel Explorer Driver");
    std::tstring driver_path = vu::get_current_directory();
    #ifdef _WIN64
    driver_path += ts("WKE64.sys");
    #else // _WIN32
    driver_path += ts("WKE32.sys");
    #endif // _WIN64

    // Create / Start / Stop / Delete

    vu::VUResult ret = vu::VU_OK;

    auto& sm = ServiceManager::instance();

    std::tcout << ts("Press any key to create service ...") << std::endl; _getch();
    ret = sm.install(driver_path, driver_name, driver_display_name);
    if (ret != VU_OK)
    {
      std::tcout << sm.get_last_error_message() << std::endl;
    }

    std::tcout << ts("Press any key to start service ...") << std::endl; _getch();
    ret = sm.start(driver_name);
    if (ret != VU_OK)
    {
      std::tcout << sm.get_last_error_message() << std::endl;
    }

    std::tcout << ts("Press any key to stop service ...") << std::endl; _getch();
    ret = sm.stop(driver_name);
    if (ret != VU_OK)
    {
      std::tcout << sm.get_last_error_message() << std::endl;
    }

    std::tcout << ts("Press any key to delete service ...") << std::endl; _getch();
    ret = sm.uninstall(driver_name);
    if (ret != VU_OK)
    {
      std::tcout << sm.get_last_error_message() << std::endl;
    }

    // Dependents / Dependencies

    std::tstring example = ts("WSearch");

    std::tcout << example << std::endl;

    std::tcout << ts("*Dependents:") << std::endl;

    auto dependents = sm.get_dependents(example);
    for (auto& dependent : dependents)
    {
      std::tcout << ts("  ") << dependent.lpServiceName << ts(" - ") << dependent.lpDisplayName << std::endl;
    }

    std::tcout << ts("*Dependencies:") << std::endl;

    auto dependencies = sm.get_dependencies(example);
    for (auto& dependency : dependencies)
    {
      std::tcout << ts("  ") << dependency.lpServiceName << ts(" - ") << dependency.lpDisplayName << std::endl;
    }

    // List Services

    std::tcout << ts("*Services:") << std::endl;

    auto pService = sm.query(example);
    assert(pService != nullptr);

    auto services = sm.get_services(VU_SERVICE_ALL_TYPES, SERVICE_RUNNING);
    for (auto& e : services)
    {
      std::tcout << ts("  ") << e.lpServiceName << ts(" - ") << e.lpDisplayName << std::endl;
    }
  }

  return vu::VU_OK;
}