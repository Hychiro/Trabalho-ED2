#ifndef NOB_H
#define NOB_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class NoB
{

public:
    NoB(){};
    ~NoB(){};
    char review_id[90];
    void setReviewId(char a[]){
        for (int i = 0; i < 90; i++)
        {
            review_id[i]=a[i];
        } 
    };
};


#endif // NOVP_HS