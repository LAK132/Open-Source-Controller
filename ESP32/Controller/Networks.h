#include "WiFi.h"
#include <nvs.h>
#include <stdlib.h>

struct NetworkList
{
  const static int maxLen = 100;
  String list[maxLen];
  size_t listLen;

  String& operator[](const size_t index)
  {
    return list[(index < maxLen ? index : maxLen - 1)];
  }
};

class Networks
{
private:
    nvs_handle nvsh;
public:
    Networks(){}
    Networks(nvs_handle nh);
    ~Networks();
    NetworkList scan();
    String getPassword(const String& ssid);
    void savePassword(const String& ssid, const String& pass);
    bool forget(const String& ssid);
};
