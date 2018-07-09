#include <stdlib.h>
#include <iostream>
using namespace std;



int main(){
while(1){
int result = system("cat alarm.txt | grep \"1\"");
cout<<result<<endl;
if(result == 0)
system("mplayer -ao alsa:device=hw=2  siren.mp3");
}
return 0;

}
