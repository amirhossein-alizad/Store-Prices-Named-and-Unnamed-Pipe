#include "tools.h"

std::vector<std::string> listFile(std::string filename)
{
    DIR *pDIR;
    std::vector<std::string> directory;
    struct dirent *entry;
    std::string str = filename;
    const char* path = str.c_str();
    if( pDIR=opendir(path) )
    {
      while(entry = readdir(pDIR))
      {
        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
        {
          std::string x = path;
          x += "/";
          x += entry->d_name;
          directory.push_back(x);
        }
      }
      closedir(pDIR);
    }
    return directory;
}

std::string fix_str(char str[])
{
  int idx;
  for(int i = 0; i < 256; i++)
    if(str[i] == '.' && i != 0)
    {
      idx = i;
      break;
    }
  std::string str_new;
  for(int i = 0; i < idx + 4; i++)
    str_new += str[i];
  return str_new;
}

char * str_to_charstar(std::string s)
{
  char * p = new char[s.length()];
  int i;
  for (i = 0; i < s.length(); i++)
      p[i] = s[i];
  p[s.length()] ='\0';
  return p;
}

std::string charstar_to_str(char* inadr)
{
  int len = strlen(inadr);
  std::string adr;
  for(int i = 0; i < len; i++)
    adr += inadr[i];
  return adr;
}

std::vector<std::string> break_command_by_space(std::string command)
{
  std::vector<std::string> commands;
  std::string comm;
  for(int i = 0; i < command.size(); i++)
  {
    if(command[i] == ' ')
    {
      commands.push_back(comm);
      comm = "";
      continue;
    }
    comm += command[i];
  }
  if(comm != "")
    commands.push_back(comm);
  return commands;
}

std::string create_msg(std::vector<std::string> requests, std::string state)
{
  std::string in = state;
  in += "#";
  in += requests[0];
  in += "#";
  in += requests[1];
  in += "#";
  in += requests[2];
  in += "#";
  in += requests[3];
  return in;
}

std::vector<std::string> break_command_by_hash(std::string command)
{
  std::vector<std::string> commands;
  std::string comm;
  for(int i = 0; i < command.size(); i++)
  {
    if(command[i] == '#')
    {
      commands.push_back(comm);
      comm = "";
      continue;
    }
    comm += command[i];
  }
  if(comm != "")
    commands.push_back(comm);
  return commands;
}

std::vector<int> break_date(std::string date)
{
  std::vector<int> dates;
  std::string num;
  for(int i = 0; i < date.size(); i++)
  {
    if(date[i] == '/')
    {
      dates.push_back(stoi(num));
      num = "";
      continue;
    }
    num += date[i];
  }
  if(num != "")
    dates.push_back(stoi(num));
  return dates;
}

std::vector<std::string> delimit(std::string line)
{
  std::vector<std::string> v;
  std::string str = "";
  for (int i = 0; i < line.size(); i++)
  {
    if(line[i] != ',')
      str += line[i];
    else
    {
      v.push_back(str);
      str = "";
    }
  }
  if(str != "")
    v.push_back(str);
  return v;
}

bool date_is_ok(std::vector<int> end_date, std::vector<int> start_date, std::vector<int> date)
{
    if((end_date[0] > date[0] && date[0] > start_date[0]) ||
            (end_date[0] == date[0] && end_date[1] > date[1]) ||
            (end_date[0] == date[0] && end_date[1] == date[1] && end_date[2] >= date[2]) ||
            (start_date[0] == date[0] && start_date[1] < date[1]) ||
            (start_date[0] == date[0] && start_date[1] == date[1] && start_date[2] <= date[2])){
              return true;
            }
    return false;
}

long long int find_min(std::vector<int> prices)
{
  long long int min = 1000000000;
  for(int i = 0; i < prices.size(); i++)
  {
    if(prices[i] < min)
      min = prices[i];
  }
  return min;
}

long long int find_max(std::vector<int> prices)
{
  long long int max = 0;
  for(int i = 0; i < prices.size(); i++)
  {
    if(prices[i] > max)
      max = prices[i];
  }
  return max;
}

std::vector<std::string> break_address(std::string address)
{
  std::vector<std::string> adr;
  std::string a;
  for(int i = 0; i < address.size(); i++)
  {
    if(address[i] == '/')
    {
      adr.push_back(a);
      a = "";
      continue;
    }
    a += address[i];
  }
  if(a != "")
    adr.push_back(a);
  return adr;
}

int open_a_file(char myfifo[])
{
  mkfifo(myfifo, 0666);
  std::cout<<myfifo<<std::endl;
  std::cout<<"tusham miad"<<std::endl;
  int fd = open(myfifo, O_WRONLY);
  if(fd < 0)
  {
    std::cout<<"RIDI"<<std::endl;
    exit(1);
  }
  std::cout<<"birun nmiad"<<std::endl;
  return fd;
}

int get_date(std::string start)
{
  int start_date = 0;
  for(int i = 0; i < start.size(); i++)
  {
    if(start[i] != '/')
      start_date = start_date * 10 + (start[i] - '0');
  }
  return start_date;
}

void execute(int pip[2], std::vector<std::string> info, std::string shop, char* args[])
{
  close(0);
  dup(pip[0]);
  std::string in = create_msg(info, shop);
  char * msg = str_to_charstar(in);
  write(pip[1], msg, strlen(in.c_str()));
  close(pip[0]);
  if( 0 > execv(args[0], args))
  {
    std::cout<<"exec FAILED"<<std::endl;
    exit(1);
  }
}

std::vector<int> get_products_prices(std::string adr, int product_id, int start_date, int end_date)
{
  std::vector<int> prices;
  std::ifstream fin;
  fin.open(adr);
  int i = 0;
  while(!fin.eof())
  {
    std::string line;
    std::getline(fin, line);
    if(i == 0)
    {
      i++;
      continue;
    }
    std::string test = "";
    int id, price;
    int time = 0;
    std::string p_date;
    for(int j = 0; j < line.size(); j++)
    {
      if(line[j] == ',')
      {
        if(time == 0)
          p_date = test;
        if(time == 1)
          id = stoi(test);
        test = "";
        time++;
      }
      else
        test += line[j];
    }
    if(time == 2)
      price = std::stoi(test);
    int date = get_date(p_date);
    if(id == product_id)
    {
        if(end_date >= date && date >= start_date)
        {
          prices.push_back(price);
        }
    }
  }
  return prices;
}

int get_ans(std::vector<int> prices, std::string minmax)
{
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
  return ans;
}

void pass_to_named_pipe(int ans, std::string fifo, int flag)
{
  if(flag == 1)
  {
    int fd;
    std::string str_ans = std::to_string(ans);
    str_ans += "#";
    fd = open(&fifo[0], O_WRONLY);
    if(fd < 0)
    {
      std::cout<<"open failed"<<std::endl;
      exit(1);
    }
    if(write(fd, &str_ans[0], str_ans.size()) < 0)
    {
      std::cout<<"write failed"<<std::endl;
      exit(1);
    }
    close(fd);
    exit(1);
  }
}
std::string get_from_named_pipes(std::string fifo, int flag)
{
  std::string whole_msg;
  if(flag == 1)
  {
    int fd = open(&fifo[0], O_RDONLY);
    if (fd < 0)std::cout<<"open failed"<<std::endl;
    char * msg = new char[256];
    while(read(fd, msg, 256)>0)
    {
      std::string strmsg = charstar_to_str(msg);
      whole_msg +=strmsg;
      msg = new char[256];
    }
    unlink(&fifo[0]);
    mkfifo(&fifo[0], 0666);
  }
  return whole_msg;
}
bool isdig(char in)
{
  if(in == '0' || in == '1' || in == '2' || in == '3' || in == '4'
      || in =='5' || in == '6' || in == '7' || in == '8' || in == '9' || in == '-')
    return true;
  return false;
}
std::vector<int> break_str_and_give_price(std::string whole_msg)
{
  std::string temp;
  std::vector<int> prices;
  for(int i = 0; i < whole_msg.size(); i++)
  {
    if(isdig(whole_msg[i]))
      temp += whole_msg[i];
    else if(whole_msg[i] == '#')
    {
      if(temp == "-1")
      {
        //do nothing
      }
      else
        prices.push_back(std::stoi(temp));
      temp = "";
    }
    else
      temp = "";
  }
  return prices;
}
