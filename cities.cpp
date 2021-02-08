#include "tools.h"

int main(int argc, char *argv[])
{
  char* inadr = new char[256];
  read(0, inadr, 256);
  inadr[strlen(inadr)] = '\0';
  std::string adr = charstar_to_str(inadr);
  std::vector<std::string> info = break_command_by_hash(adr);
  std::vector<std::string> fifo_arr;
  adr = info[0];
  std::string fifo_get = "/tmp/city";
  std::string fifo_send = "/tmp/state";
  info.erase(info.begin());
  std::string minmax = info[0];
  std::vector<std::string> shops = listFile(adr);
  int pip[shops.size()][2];
  std::vector<std::string> broken_adr = break_address(adr);
  for(int i = 0; i < shops.size(); i++)
  {
    char *args[] = {str_to_charstar("./Shops.out"), NULL};
    int pid = fork();
    pipe(pip[i]);
    if(pid == 0)
      execute(pip[i], info, shops[i], args);
  }
  std::string whole_msg = get_from_named_pipes(fifo_get, 0);
  pass_to_named_pipe(0, fifo_send, 0);
  exit(1);
}
