
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
    string review_id;
    string review_text;
    string upvotes;
    string app_version;
    string date;
    string hour;
    int getId() { return iD; };
    void setId(int i) { iD = i; };
};

#endif // NO_H