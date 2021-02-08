#include "tools.h"

int main(int argc, char *argv[])
{
  char* inadr = new char[256];
  read(0, inadr, 256);
  inadr[strlen(inadr)] = '\0';
  std::string fifo = "/tmp/ans";
  std::string adr = charstar_to_str(inadr);
  std::vector<std::string> info = break_command_by_hash(adr);
  adr = info[0];
  info.erase(info.begin());
  std::string minmax = info[0];
  info.erase(info.begin());
  int product_id = stoi(info[0]);
  info.erase(info.begin());
  std::string start = info[0];
  int start_date = get_date(start);
  info.erase(info.begin());
  std::string end = info[0];
  int end_date = get_date(end);
  info.erase(info.begin());
  std::vector<std::string> broken_adr = break_address(adr);
  std::vector<int> prices = get_products_prices(adr, product_id, start_date, end_date);
  int ans = get_ans(prices, minmax);
  pass_to_named_pipe(ans, fifo, 1);
}
