#include <cstdlib>// For several general-purpose functions
#include <fstream> // For file handling
#include <iomanip> // For formatted output
#include <cstring>
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
#include <locale>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
using namespace std;
int filenumber = 0;
class apscan{
  string mac;
  //int mac[6]; //fuck that
  string wfinterface;
  string ssid;
  int dBm;
  int ms;
  bool assoc;
  time_t timescanned;
public:
  string getmac(){
    return mac;
  }
  apscan(){

  }
  apscan(string a, string wfinter, string ap, int db, int m, bool asoc){
    mac = a;
    ssid = ap;
    dBm = db;
    ms = m;
    assoc = asoc;
  }
  void setfreq(int x){
    dBm = x;
  }
  void setmac(string a){
    mac = a;
  }
  void settimenow(){
    time(&timescanned);
  }
  void setms(int x){
    ms = x;
  }
  void setasoc(bool x){
    assoc = x;
  }
  void setssid(string x){
    ssid = x;
  }
  void write(string a){
    ofstream file;
    file.open(a, ios_base::app);
    stringstream date;
    date << timescanned;
    string appendstring = mac + " " + ssid + " " + to_string(dBm) + " " + to_string(ms) + " " + to_string(assoc) + " " + date.str() + "\n";
    file << appendstring;
    file.close();
    cout << "wrote";
  }
};



inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}



     /* Remember the effective and real UIDs. */
     static uid_t euid, ruid;
     /* Restore the effective UID to its original value. */
     void do_setuid (void)
     {
    int status;
     #ifdef _POSIX_SAVED_IDS
       status = seteuid (euid);
     #else
       status = setreuid (ruid, euid);
     #endif
       if (status < 0) {
         fprintf (stderr, "Couldn't set uid.\n");
         exit (status);
         }
     }
     /* Set the effective UID to the real UID. */
     void undo_setuid (void)
     {
       int status;
     #ifdef _POSIX_SAVED_IDS
       status = seteuid (ruid);
     #else
       status = setreuid (euid, ruid);
       int status;
     #endif
       if (status < 0) {
         fprintf (stderr, "Couldn't set uid.\n");
         exit (status);
         }
     }
     /* Main program. */
     void buildscan(){
       //system("make all");
     }


//////////////////////////////////////////////////////////////////////
int scan(string second = "wpa0", string scanname = "last_scan.txt", string project = "default_project.txt")
     {
       cout << "scanstart";



       /* Remember the real and effective user IDs.  */
       //ostringstream oss;
       //oss << "sudo ./wifi-scan-all" << " wlp1s0";
       ruid = getuid ();
       euid = geteuid ();
       fstream createfile;
       createfile.open(scanname.c_str());
       createfile.close();
       string deletecommand = "sudo rm " + scanname;
       system(deletecommand.c_str());//kill last log (wont need it)
       cout << "-2";
        cout << "-1";
       string first = "sudo ./wifi-scan-all ";
       string third = " >> ";
       cout << "0";
       string input = first;
       cout << "1";
       input.append(second); //scan() gets second as parameter runs "sudo ./wifi-scan-all >interface< >> scan.txt"
       input.append(third);
       input.append(scanname);
       //input = "sudo ./wifi-scan-all wlp1s0 >> last_scan.txt";//debug line
       cout << "2";
       undo_setuid ();//are these even necessary?
       do_setuid ();//?




//TOO BIG :: fixed?
        cout << "prescan";
       system(input.c_str());//make new scan
       string s;
       int scanned = 0;
       ifstream in;
       in.close();
       fstream stored;
       stored.open(scanname);
       cout << scanned;
       string line;
       cout << "\n";
       cout << "prefor";
       for (scanned = 0; getline(stored, s); scanned++); //counts lines of scan
       stored.close();
       stored.open(scanname);


cout << "between fors\n";
for(int i = 0; i < scanned;i++){
       string store;
       apscan objstore;
       stored >> store;
       objstore.setmac(store);
       stored >> store;
       bool wasssid = false;
       string fullssid;
       cout << "prewhile\n";
       for (int i = 0; i<17;i++){//trying to replace broken while
         if(!isInteger(store)){
           if (wasssid) fullssid = fullssid + " ";
           fullssid = fullssid+store;
           cout << store << endl;
           stored >> store;
           wasssid = true;
         }
         if(isInteger(store)){
           i = 17;
         }
       }
       /*
       while (!isInteger(store)){
         if (wasssid) fullssid = fullssid + " ";
         fullssid = fullssid+store;
         stored >> store;
         wasssid = true;
       }
       */
       cout << "post\n";
       if (wasssid){
         objstore.setssid(fullssid);
       }
       else{ //if the int is negative. Its a frequency? (I think)
         objstore.setssid("hidden");
       }
       objstore.setfreq(stoi(store));
       stored >> store;
       objstore.setms(stoi(store));
       stored >> store;
       if(store == "associated") objstore.setasoc(1);
       if(store == "unassociated") objstore.setasoc(0);
       objstore.settimenow();
       objstore.write(project);
    }
       cout << "a\n";
       stored.close();
       return scanned;
       /* Do the game and record the score.  */
     }
