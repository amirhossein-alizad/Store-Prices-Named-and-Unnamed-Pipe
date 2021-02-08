#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>
#include<vector>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>

std::vector<std::string> listFile(std::string);
std::string fix_str(char str[]);
char * str_to_charstar(std::string);
std::string charstar_to_str(char *);
std::vector<std::string> break_command_by_space(std::string);
std::string create_msg(std::vector<std::string>, std::string);
std::vector<std::string> break_command_by_hash(std::string);
std::vector<int> break_date(std::string);
std::vector<std::string> delimit(std::string line);
bool date_is_ok(std::vector<int>, std::vector<int>, std::vector<int>);
long long int find_max(std::vector<int>);
long long int find_min(std::vector<int>);
std::vector<std::string> break_address(std::string);
int open_a_file(char[]);
int get_date(std::string);
void execute(int[2], std::vector<std::string>, std::string, char*[]);
std::vector<int> get_products_prices(std::string, int, int, int);
int get_ans(std::vector<int>, std::string);
void pass_to_named_pipe(int, std::string, int);
std::string get_from_named_pipes(std::string, int);
bool isdig(char );
std::vector<int> break_str_and_give_price(std::string);
