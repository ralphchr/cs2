#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int binToDec(string binary){
    int decimal = 0;

    for (char bit : binary){
        decimal = decimal * 2 + (bit - '0');
    }

    return decimal;
}

string binToIP(string binary){
    string ipAdd = "";

    for (int i = 0; i < 4; i++){
        string octet = binary.substr(i * 8, 8);

        ipAdd += to_string(binToDec(octet));

        if (i != 4)
            ipAdd += ".";

    }

    return ipAdd;
}

int binToSeq(string binary){
    int seq = binToDec(binary);

    if (binary[0] == '1')
        seq -= 65536;

    return seq;
}

string binToData(string binary){
    string data = "";

    for (int i = 0; i < binary.length(); i += 8){
        string chr = binary.substr(i, 8);

        int ascii = binToDec(chr);

        data += char(ascii);
    }

    return data;
}

int xcheckSum(string x){
    x.replace(80, 16, "0000000000000000");

    int sum = 0, value = 0;

    for (int i = 0; i < x.length(); i += 16){
        string part = x.substr(i, 16);
        value = binToDec(part);

        sum += value;

        if (sum > 65535)
            sum = (sum % 65536) + 1;
    }

    sum = 65535 - sum;

    return sum;

}

bool packetChecker(string x){
    int origcs = binToDec(x.substr(80, 16));

    int cs = xcheckSum(x);

    if (origcs == cs)
        return true;
    else
        return false;
}

class Packets{
    public:
        string srcadd;
        string desadd;
        int seq;
        int checksum;
        int length;
        string data;

        Packets(){
            srcadd = "";
            desadd = "";
            seq = 0;
            length = 0;
            data = "";
        }

        Packets(string binary){
            srcadd = binToIP(binary.substr(0, 32));
            desadd = binToIP(binary.substr(32, 32));
            seq = binToSeq(binary.substr(64, 16));
            length = binToDec(binary.substr(96, 16));
            data = binToData(binary.substr(112, length));
        }
};

bool comparepackets(Packets a, Packets b){
    return a.seq < b.seq;
}

int main(){
    string fileinput;

    cin >> fileinput;
    ifstream file(fileinput);

    vector<Packets> packets;

    string binary;

    while (getline(file, binary)){
        if (binary.empty())
            continue;

        if (!packetChecker(binary))
            continue;

        packets.push_back(Packets(binary));
    }

    file.close();

    vector<vector<Packets>> poems;

    for (int i = 0; i < packets.size(); i++){
        int poemindex = -1;

        for (int j = 0; j < poems.size(); j++){
            if (poems[j][0].srcadd == packets[i].srcadd && poems[j][0].desadd == packets[i].desadd){
                poemindex = j;
                break;
            }
        }

        if (poemindex == -1){
            vector<Packets> newp;

            newp.push_back(packets[i]);
            poems.push_back(newp);
        }
        else
            poems[poemindex].push_back(packets[i]);


    }

    for (int i = 0; i < poems.size(); i++){
        sort(poems[i].begin(), poems[i].end(), comparepackets);

        int titleindex = -1;

        for (int j = 0; j < poems[i].size(); j++){
            if (poems[i][j].seq == 0){
                titleindex = j;
                break;
            }
        }

        if (titleindex == -1)
            continue;


        cout << poems[i][titleindex].data << "\n";
        cout << poems[i][titleindex].srcadd << " /" << poems[i][titleindex].desadd << "\n";


        for (int j = 0; j < poems[i].size(); j++){
            if (poems[i][j].seq > 0)
                cout << poems[i][j].data << endl;
        }

        cout << "--------------------------------------------------------------------------------" << "\n";
    }
}