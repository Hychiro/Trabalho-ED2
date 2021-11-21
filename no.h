
#ifndef NO_H
#define NO_H
#include <iostream>
#include <string>

using namespace std;

class No
{
private:
    int iD;

public:
    No(){};
    ~No(){};
    char review_id[90];
    char review_text[3000];
    char upvotes[10];
    char app_version[30];
    char date[30];
    char hour[30];
    int getId() { return iD; };
    void setId(int i) { iD = i; };
};

#endif // NO_H