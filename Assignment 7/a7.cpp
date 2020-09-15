#include<iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void read_csv()
    {
        string tcp = "TCP";
        string udp = "UDP";
        string arp = "ARP";
        string tlsv = "TLSv1.2";

        int tcpcount = 0,udpcount = 0,arpcount = 0,tlsvcount = 0;
        int rows;

        ifstream fin("a7.csv",ios::in);
    
        string line = "";
        int row = 0;
        while(getline(fin,line)){
            row++;
            if(line.find(tcp) != std::string::npos){
                    tcpcount++;
                }
                else if(line.find(udp) != std::string::npos){
                    udpcount++;
                }
                else if(line.find(arp) != std::string::npos){
                    arpcount++;
                }
                else if(line.find(tlsv) != std::string::npos){
                    tlsvcount++;
                }
           
        }
        // string l;
        
        // while(fin >> temp){
        //     getline(fin,l);
        //     row++;
        // }
        
    
        int tpacket = row-1;
        fin.close();
        cout<<"Total packets: "<<tpacket<<endl;
        cout<<"TCP packets: "<<tcpcount<<endl;
        cout<<"UDP packets: "<<udpcount<<endl;
        cout<<"ARP packets: "<<arpcount<<endl;
        cout<<"TLSV packets: "<<tlsvcount<<endl;
        cout<<"IP packets: "<<tpacket-arpcount<<endl;

        
    }

int main(){
    read_csv();
    return 0;
    
}