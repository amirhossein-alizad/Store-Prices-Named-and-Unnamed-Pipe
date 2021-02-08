#include "tools.h"

int main(int argc, char* argv[])
{
    std::ifstream fin;
    fin.open(argv[1]);
    std::vector<std::string> requests;
    std::string req;
    std::vector<int> children;
    std::vector<std::string> fifo_arr;
    std::string fifo = "/tmp/ans";
    unlink(&fifo[0]);
    int mk = mkfifo(&fifo[0], 0666);
    while(getline(fin, req))
    {
      requests = break_command_by_space(req);
      std::string minmax = requests[0];
      std::vector<std::string> states = listFile(argv[2]);
      int pip[states.size()][2];
      for(int i = 0; i < states.size(); i++)
      {
        char *args[] = {str_to_charstar("./States.out"), NULL};
        int pid = fork();
        pipe(pip[i]);
        if(pid == 0)
          execute(pip[i], requests, states[i], args);
        sleep(1);
      }
      waitpid(-1, NULL, 0);
      std::string whole_msg = get_from_named_pipes(fifo, 1);
      std::vector<int> prices = break_str_and_give_price(whole_msg);
      int ans;
      if(prices.size() == 0)
        ans = -1;
      else
      {
        if(minmax == "MAX")
          ans = find_max(prices);
        else
          ans = find_min(prices);
      }
      std::cout<<ans<<std::endl;
    }
    return 0;
}
