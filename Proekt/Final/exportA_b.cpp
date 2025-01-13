#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <set>
#include <bits/stdc++.h>

using namespace std;

std::string trim( const std::string & s )
{
  auto first = s.find_first_not_of( " \f\n\r\t\v" );
  auto last  = s.find_last_not_of ( " \f\n\r\t\v" );
  return (first == s.npos) ? "" : s.substr( first, last+1 );
}

//Klase za tocke in mreze
struct Point{
    int ID;
    double x;
    double y;
    bool isInner=false;
    // int nAdj;
    // int* idAdj; 
};

struct KE{
    int ID;
    int a;
    int b;
    int c;
    int d;
};

int main() {

    //Matrix A in b
    vector<vector<double>> A;
    vector<double> b;
    vector<double> T;
    double dx = 1.25;
    double dy = 1.25;
    double h = 100;
    double k = 24;
    // matlab primer uporablja ovi
    // double dx = 1;
    // double k = 1;
    const int n = 5754;
    constexpr size_t SIZE = static_cast<size_t>(n);

    //Beremo file
    string filename = "./primer2mreza.txt";

    ifstream infile;
    infile.open(filename);

    string temp;
    getline(infile, temp);

    string temp2;
    //Preberi stevilo tock
    istringstream iss(temp);
    iss >> temp2;
    iss >> temp2;
    
    //Inicijaliziram A, b, T
    vector<double> row;

    for(int j=0; j<n; j++){
        row.push_back(0);
    }

    for (int i=0; i<n; i++){
        T.push_back(100);
        b.push_back(0);
        A.push_back(row);

    }
    
    //Preberi tocke
    vector<Point> points;
    vector<KE> elementi;
    array<unordered_set<int>, SIZE> adjM;

    for(int i = 0; i<n; i++){
        getline(infile, temp);
        replace(temp.begin(), temp.end(), ';', ' ');
        replace(temp.begin(), temp.end(), ',', ' ');  

        string idTemp;
        string xTemp;
        string yTemp;

        istringstream iss(temp);
        iss >> idTemp;
        iss >> xTemp;
        iss >> yTemp;
    
        Point tempP;
        tempP.ID = stoi(idTemp);
        tempP.x = stod(xTemp);
        tempP.y = stod(yTemp);

        points.push_back(tempP);
    }

    getline(infile, temp);
    getline(infile, temp);
    
    //Preberi stevilo mreze
    istringstream issM(temp);
    issM >> temp2;
    issM >> temp2;
    int nMreze = stoi(temp2);

    //Preberi mreza i popolni adjacency matrix
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
         
        replace(temp.begin(), temp.end(), ';', ' ');
        replace(temp.begin(), temp.end(), ',', ' ');  

        string idTemp;
        string id1Temp;
        string id2Temp;
        string id3Temp;
        string id4Temp;

        istringstream iss(temp);
        iss >> idTemp;
        iss >> id1Temp;
        iss >> id2Temp;
        iss >> id3Temp;
        iss >> id4Temp;

        int pid = stoi(idTemp);
        int p1 = stoi(id1Temp);
        int p2 = stoi(id2Temp);
        int p3 = stoi(id3Temp);
        int p4 = stoi(id4Temp);
        
        KE temp;
        temp.ID = pid;
        temp.a = p1;
        temp.b = p2;
        temp.c = p3;
        temp.d = p4;

        elementi.push_back(temp);

        adjM[p1].insert(p2);
        adjM[p1].insert(p4);

        adjM[p2].insert(p1);
        adjM[p2].insert(p3);

        adjM[p3].insert(p2);
        adjM[p3].insert(p4);

        adjM[p4].insert(p1);
        adjM[p4].insert(p3);
    }

    //Proveri dali e inner
    int index = 0;
    for(auto tocka : adjM){
        int counter = 0;
        for(auto elem : tocka){
            counter++;
        }

        if(counter==4){
            points[index].isInner = true;
        }

        index++;
    }

    
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    
    vector<int> T1;
    vector<int> T2;
    vector<int> q3;
    vector<int> T4;
    vector<int> T5ex;

    //Preberi pogoje
    //Pogoj 1
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T1.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);
        getline(infile, temp);

    //Pogoj 2
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T2.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);
        getline(infile, temp);

    //Pogoj 3
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        q3.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);
        getline(infile, temp);

    //Pogoj 4
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T4.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
        getline(infile, temp);

    //Pogoj 5
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T5ex.push_back(id);
    }

    cout<<"T1: "<<T1[0]<<" - "<<T1.back()<<": "<<T1.size()-1<<endl;
    cout<<"T2: "<<T2[0]<<" - "<<T2.back()<<": "<<T2.size()-1<<endl;
    cout<<"q3: "<<q3[0]<<" - "<<q3.back()<<": "<<q3.size()-1<<endl;
    cout<<"T4: "<<T4[0]<<" - "<<T4.back()<<": "<<T4.size()-1<<endl;
    cout<<"T5ex: "<<T5ex[0]<<" - "<<T5ex.back()<<": "<<T5ex.size()-1<<endl;

    //Sestavamo A in b

    int counter=0;
    unordered_set<int> done;
    vector<int> s;
    s.reserve(T1.size()+T2.size()+q3.size()+T4.size()+T5ex.size());
    s.insert(s.end(), T1.begin(), T1.end());
    s.insert(s.end(), T2.begin(), T2.end());
    s.insert(s.end(), q3.begin(), q3.end());
    s.insert(s.end(), T4.begin(), T4.end());
    s.insert(s.end(), T5ex.begin(), T5ex.end());
    set<int> ss(s.begin(), s.end());

    for(int i = 0; i<n; i++){
        if(count(T1.begin(), T1.end(), i) > 0){
            // printf("Bang T1\n");
            A[i][i] = 1;
            b[i] = 400;
        }else if(count(T2.begin(), T2.end(), i) > 0){
            // printf("Bang T2\n");
            A[i][i] = 1;
            b[i] = 100;
        }else if(count(q3.begin(), q3.end(), i) > 0){
            // printf("Bang q3\n");
            for(auto elem : adjM[i]){
                if(points[elem].isInner)
                    A[i][elem] = 2;
                else
                    A[i][elem] = 1;
            }
            A[i][i]=-4;
            b[i] = 0;
        }else if(count(T4.begin(), T4.end(), i) > 0){
            // printf("Bang T4\n");
            A[i][i] = 1;
            b[i] = 600;
        }else if(count(T5ex.begin(), T5ex.end(), i) > 0){
            // printf("Bang T5\n");
            //preveri rob ali notranjem
            if(points[i].isInner){
                //notranjem kot
                for(auto elem : adjM[i]){
                    if(points[elem].isInner)
                        A[i][elem] = 2;
                    else
                        A[i][elem] = 1;
                }
                A[i][i] = -2*(3+(h*dx)/k);

            }else{
                //rob
                for(auto elem : adjM[i]){
                    A[i][elem] = 2;
                }
                A[i][i] = -2*(2+(h*dx)/k);
            }

            b[i] = -2*(h*dx*200)/k;
        }else{
                // printf("Inner\n");
                A[i][i] = -4;
                for(auto elem : adjM[i]){
                    A[i][elem] = 1;
                }
                b[i] = 0;

        }
    
    }

    ofstream File("A_b.txt");
    File<<"A: n="<<n<<"\n";
    for(int i=0; i<n; i++){
        for(int j = 0; j<n; j++){
            File<<A[i][j];
            if(j!=n-1){
                File<<";";
            }
        }
            File<<"\n";
    }
    File<<"\n";
    File<<"b: n->"<<n<<"\n";
    for(int i=0; i<n; i++){
        File<<b[i]<<endl;
    }

    File.close();

    return 0;
}