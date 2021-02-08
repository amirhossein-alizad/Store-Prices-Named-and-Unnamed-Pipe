#include "tools.h"

int main(int argc, char *argv[])
{
  char* inadr = new char[256];
  read(0, inadr, 256);
  inadr[strlen(inadr)] = '\0';
  std::string fifo_get = "/tmp/state";
  std::string fifo_send = "/tmp/ans";
  std::string adr = charstar_to_str(inadr);
  std::vector<std::string> info = break_command_by_hash(adr);
  adr = info[0];
  info.erase(info.begin());
  std::vector<std::string> cities = listFile(adr);
  std::vector<std::string> broken_adr = break_address(adr);
  int pip[cities.size()][2];
  for(int i = 0; i < cities.size(); i++)
  {
    char *args[] = {str_to_charstar("./Cities.out"), NULL};
    int pid = fork();
    pipe(pip[i]);
    if(pid == 0)
      execute(pip[i], info, cities[i], args);
  }
  waitpid(-1, NULL, 0);
  std::string whole_msg = get_from_named_pipes(fifo_get, 0);
  pass_to_named_pipe(0, fifo_send, 0);
  exit(1);
}
