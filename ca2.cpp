// // #include <unistd.h>
// // #include <iostream>
// // #include <fstream>
// // #include <vector>
// //
// // std::vector<std::string> delimit(std::string line)
// // {
// //   std::vector<std::string> v;
// //   std::string str = "";
// //   for (int i = 0; i < line.size(); i++)
// //   {
// //     if(line[i] != ',')
// //       str += line[i];
// //     else
// //     {
// //       v.push_back(str);
// //       str = "";
// //     }
// //   }
// //   v.push_back(str);
// //   return v;
// // }
// // int main()
// // {
// //   std::string path = "./assets/Fars/Shiraz/ShirazShop.csv", line;
// //   std::ifstream fin;
// //   std::vector<std::vector<std::string>> vin;
// //
// //     // Open an existing file
// //   fin.open(path);
// //   int i = 0;
// //   while(fin.good())
// //   {
// //     std::getline(fin, line);
// //     if(!i)
// //     {
// //       i++;
// //       continue;
// //     }
// //     std::vector<std::string> v = delimit(line);
// //     vin.push_back(v);
// //   }
// //   for(int i = 0; i < vin.size(); i++)
// //   {
// //     for(int j = 0; j < vin[i].size(); j++)
// //     {
// //       std::cout<<vin[i][j]<<"\t";
// //     }
// //     std::cout<<std::endl;
// //   }
// // }
// #include<stdio.h>
// #include<cstdlib>
// #include<iostream>
// #include<string.h>
// #include<fstream>
// #include<dirent.h>
// #include<vector>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include<sys/wait.h>
//
//
// std::vector<std::string> listFile(std::string);
// std::vector<std::string> csv_finder(std::string);
// std::string fix_str(char str[]);
//
// int main(int argc, char* argv[])
// {
//     std::vector<std::string> states = listFile(argv[1]);
//     int index;
//     int flag = 0;
//     int pid;
//     int pip[states.size()][2];
//     for(int i = 0; i < states.size(); i++)
//     {
//       // std::cout<<states[i]<<std::endl;
//       pipe(pip[i]);
//       pid = fork();
//       index = i;
//       if(pid == 0)
//       {
//         flag = 1;
//         break;
//       }
//       else
//         write(pip[i][1], states[i].c_str(), strlen(states[i]));
//     }
//     if(flag == 1)
//     {
//       char * inadr = new char[256];
//       sleep(index + 1);
//       std::cout<<"in child pid: "<< getpid()<<" index : "<<index<<std::endl;
//       std::cout<<"reading address from parent..."<<std::endl;
//       read(pip[index][0], inadr, 256);
//       inadr[strlen(inadr)] = '\0';
//       // std::string str = fix_str(inadr);
//       std::cout<<"addr : "<< (inadr) << std::endl;
//       exit(1);
//     }
//     else
//     {
//     //   for(int i = 0; i < csv_addresses.size(); i++)
//     //   {
//         // wait(NULL);
//         sleep(20);
//     //     char *  inadr = new char[256];
//     //     std::cout<<"reading from child with index : "<<i<<std::endl;
//     //     read(pip[i][0], inadr, 256);
//     //     std::cout<<fix_str(inadr)<<std::endl;
//     //     delete[] inadr;
//     //   }
//     }
//     return 0;
// }
//
// std::vector<std::string> listFile(std::string filename)
// {
//         DIR *pDIR;
//         std::vector<std::string> aliz;
//         struct dirent *entry;
//         std::string str = /*"./" + */filename;
//         const char* path = str.c_str();
//         if( pDIR=opendir(path) )
//         {
//                 while(entry = readdir(pDIR))
//                 {
//                         if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
//                         {
//                           std::string x = path;
//                           x += "/";
//                           x += entry->d_name;
//                           aliz.push_back(x);
//                         }
//
//                 }
//                 closedir(pDIR);
//         }
//         return aliz;
// }
//
// // std::vector<std::string> csv_finder(std::string filename)
// // {
// //   std::vector<std::string> ls = listFile(filename);
// //   std::vector<std::string> csv_addresses;
// //   for(int i = 0; i < ls.size(); i++)
// //   {
// //     std::string path = filename;
// //     path += "/";
// //     path += ls[i];
// //     std::vector<std::string> ls2 = listFile(path);
// //     for(int j = 0; j < ls2.size(); j++)
// //     {
// //       std::string path2 = path;
// //       path2 += "/";
// //       path2 += ls2[j];
// //       std::vector<std::string> csv = listFile(path2);
// //       for(int k = 0; k < csv.size(); k++)
// //         csv_addresses.push_back(path2 + "/" + csv[k]);
// //     }
// //   }
// //   return csv_addresses;
// // }
// std::string fix_str(char str[])
// {
//   int idx;
//   for(int i = 0; i < 256; i++)
//     if(str[i] == '.' && i != 0)
//     {
//       idx = i;
//       break;
//     }
//   std::string str_new;
//   for(int i = 0; i < idx + 4; i++)
//     str_new += str[i];
//   return str_new;
// }
// 		// int pid, pip[2];
// 		// char instring[20];
// 		// pipe(pip);
//     // // std::cout<<"HI"<<std::endl;
//     //
//     //
// 		// pid = fork();
// 		// if (pid == 0)           /* child : sends message to parent*/
// 		// {
//     //   // std::cout<<pip[0]<<std::endl;
//     //   // std::cout<<pip[1]<<std::endl;
//     //   // std::cout<<pi...............[[[[[[[[[[[[[[[[[[[[[[[[[[[[//2211//.[0[[p[2].<<std::endl;
// 		// 	/* send 7 characters in the st111111111111111111r.ing, including end-of-string */
// 		// 	write(pip[1], "Hi Mom!", 8);
//     //   // std::cout<<"child sleeping"<<std::endl;
//     //   sleep(0.1);
//     //   read(pip[0], instring, 14);
//     //   std::cout<<instring<<std::endl;
//     //   exit(1);
// 		// }
// 		// else			/* parent : receives message from child */
// 		// {
// 		// 	/* read from the pipe */
// 		// 	read(pip[0], instring, 8);
//     //   write(pip[1], "hello darling", 14);
//     //
//     //   std::cout<<instring<<std::endl;
//     //   sleep(0.2);
//     //   // wait(1);
//     //
// 		// }
// // }
