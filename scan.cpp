#include "data.h"
using namespace std;

void terminal(){
cout << "                             __                       __                             " <<
endl << "                            /\\ \\                     /\\ \\                            " <<
endl << " _____      __     __   _ __\\ \\ \\___      __      ___\\ \\ \\/'\\      __   _ __   ____  " <<
endl << "/\\ '__`\\  /'__`\\ /'__`\\/\\`'__\\ \\  _ `\\  /'__`\\   /'___\\ \\ , <    /'__`\\/\\`'__\\/',__\\ " <<
endl << "\\ \\ \\L\\ \\/\\  __//\\  __/\\ \\ \\/ \\ \\ \\ \\ \\/\\ \\L\\.\\_/\\ \\__/\\ \\ \\\\`\\ /\\  __/\\ \\ \\//\\__, `\\" <<
endl << " \\ \\ ,__/\\ \\____\\ \\____\\\\ \\_\\  \\ \\_\\ \\_\\ \\__/.\\_\\ \\____\\\\ \\_\\ \\_\\ \\____\\\\ \\_\\\\/\\____/" <<
endl << "  \\ \\ \\/  \\/____/\\/____/ \\/_/   \\/_/\\/_/\\/__/\\/_/\\/____/ \\/_/\\/_/\\/____/ \\/_/ \\/___/ " <<
endl << "   \\ \\_\\                                                                             " <<
endl << "    \\/_/                                                                             " <<
endl << "Welcome to rpi scanner by peerhackers, type ? for commands." <<
endl;
string project;
string logg;
bool terminate = 0;

//get settings
fstream settings;
settings.open("settings", ios_base::app);
settings >> project;
settings >> logg;
settings.close();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LOOP FOR TERMINAL
while (!terminate){
  string input;
  cout << "rpiscanner:~> ";
  cin >> input;
  if(input == "scan"){
    string interface;
    cin >> interface;
    int scanned = scan(interface,logg,project);
    cout << endl << scanned << " unique networks scanned and added to project " << project << "..."  << endl;
  }
  else if(input == "project"){
    string proj;
    cin >> proj;
    project = proj;
    cout << endl << "Project set." << endl;
  }
  else if(input == "default"){
    string sett;
    string file;
    cin >> sett;
    cin >> file;
    settings.open("settings");
    string fullline = sett+" "+file;
    settings << fullline;
    settings.close();
    cout << endl << "Settings file wrote." << endl;
  }
  else if(input == "log"){
    string file;
    cin >> file;
    logg = file;
  }
  else if(input == "ls"){
    system("ls -al");
    cout << endl;
  }
  else if(input == "cd"){
    string cd;
    cin >> cd;
    string cdline;
    cdline = "cd "+cd;
    system(cdline.c_str());
    cout << endl;


    ///record current file position of wifi_scan_all.c, change working directory to


  }
  else if (input == "?"){
    cout << "Commands are as follows:" <<
    endl << "scan interface" << endl << "   Scans whatever wireless interface you type in place of interface. I.E. wpa0" <<
    endl << "project file" << endl << "   Changes current project file to whatever you type in place of file." <<
    endl << "log file" << endl << "   Changes current log file, to whatever you type in place of file." <<
    endl << "default setting filename" << endl << "   Changes the default(on start of terminal) setting(log, project) to the filename you want (EX: default project default_save.txt)" <<
    endl << "ls" << endl << "   Lists current execution directory to terminal using ls -al." <<
    endl << "exit" << "   Exits the terminal back to bash (or however you launched this)" <<
    endl; //WIP
  }
  else {
    cout << endl << "Invalid command, type ? for help screen." << endl;
  }
 }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}






int main(){
  terminal();
  apscan mydata;
  buildscan();
  cout << "prescan";
  scan("wlp1s0");
  return 0;
}
//split program into single scan for storing and utility to look at convert data
//create a set project part that allows you to choose what to store your collected hotspots in666
