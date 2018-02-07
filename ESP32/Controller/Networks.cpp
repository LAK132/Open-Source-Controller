#include "Networks.h"

Networks::Networks(nvs_handle nh)
{
    nvsh = nh;
}

Networks::~Networks()
{
    //nvs_commit(nvsh);
}

NetworkList Networks::scan()
{
    int n = WiFi.scanNetworks();
    NetworkList nl;
    for (nl.listLen = 0; nl.listLen < n && nl.listLen < nl.maxLen; nl.listLen++)
    {
        nl[nl.listLen] = WiFi.SSID(nl.listLen);
    }
    return nl;
}

String Networks::getPassword(const String& ssid)
{
    String name = "s" + ssid;
    char* pass = nullptr; size_t strl;
    if(nvs_get_str(nvsh, name.c_str(), pass, &strl) != ESP_OK) { return ""; };

    if(pass == nullptr)
    {
        pass = (char*)malloc(strl);
        nvs_get_str(nvsh, name.c_str(), pass, &strl);
    }
    if(pass == nullptr || pass == NULL) { return ""; }
    String rtn = String(pass);
    delete[] pass;
    return rtn;
}

void Networks::savePassword(const String& ssid, const String& pass)
{
    String name = "s" + ssid;
    nvs_set_str(nvsh, name.c_str(), pass.c_str());
    nvs_commit(nvsh);
}

bool Networks::forget(const String& ssid)
{
    String name = "s" + ssid;
    nvs_erase_key(nvsh, name.c_str());
    nvs_commit(nvsh);
}
