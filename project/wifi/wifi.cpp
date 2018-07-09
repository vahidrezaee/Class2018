#include <iostream>
#include <string>
#include <fstream>
#include<stdlib.h>
using namespace std;
/*class device{
    string name;
    string timein;
    string timeout;
};
*/
#define EMPNUM 4
int device_num =0;
int main()
{
   bool  perents[4] ={false, false , false , false};
   string employee [4]={"HUAWEI_P10_lite" , "Galaxy-A5-2017", "farhad","Vahid"};
    //device *devices=new device[4];
   while(1){
   system("date \"+%H:%M:%S %d/%m/%Y\">/home/pi/project/wifi/time.txt");
     ifstream ftime("time.txt");
     string time;
     std::getline(ftime, time );
     //cout <<time<<endl;
     ftime.close();
///	return 0;    
    system("nmap -sn 192.168.4.* |grep \"report for\"| awk -F ' ' '{print $5}' > /home/pi/project/wifi/wifi.txt");
   // ifstream file("wifi.txt");
   
	 string line;
    int  result;
    //sprintf(line,"cat /home/farhad/vahid/project/wifi/wifi.txt |grep \"+ ")
    string cmd ="cat /home/pi/project/wifi/wifi.txt |grep \"";
    //system("touch /home/farhad/vahid/project/wifi/list.txt");
    for(int i=0;i<EMPNUM;i++){
    line = cmd + employee[i]+"\"";
    cout <<line<<endl;
     result = system(line.data());
    cout <<"result"<<result<<endl;

     if(result == 0 && perents[i]==false )
     {
             line = "sudo sh -c \"echo connected in  = " +time+">> /var/www/html/wifiandsensor/"+employee[i]+".txt\"";
             perents[i]=true;
             system(line.data());
     }
     if(result !=0 && perents[i]==true ){
         line = "sudo sh -c \"echo disconnected in  = " +time+">> /var/www/html/wifiandsensor/"+employee[i]+".txt\"";
         perents[i]=false;
         system(line.data());
     }
      if(result !=0 && perents[i]==false ){
          line = "sudo sh -c \" touch  /var/www/html/wifiandsensor/"+employee[i]+".txt\"";
          system(line.data());
     }
    }


    if(perents[0]==true)
	{
	line="sudo sh -c \"echo  "+employee[0]+ " is Online    >/var/www/html/wifiandsensor/status.txt\" ";
        system(line.data());
	}
    else
	{ 
        line="sudo sh -c \"echo  "+employee[0]+ "  is Offline   >/var/www/html/wifiandsensor/status.txt\" ";
        system(line.data());
        }
   for(int i =1 ;i<EMPNUM ;i++){
    if(perents[i]==true)
      { 
        line="sudo sh -c \"echo  "+employee[i]+ "  is Online  >> /var/www/html/wifiandsensor/status.txt\" ";
        system(line.data());
        }
    else
       { 
        line="sudo sh -c \"echo  "+employee[i]+ "  is Offline  >> /var/www/html/wifiandsensor/status.txt\" ";
        system(line.data());
        }
}
    //file.close();
  // cout <<"result"<< system("cat /home/farhad/vahid/project/wifi/wifi.txt |grep \"vajjgjhid\" ");
   }
return 0;
}

