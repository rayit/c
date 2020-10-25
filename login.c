#include <stdlib.h>
#include <iostream>
#include <map>
#include "getpost.h"

using namespace std;

int main()
{
    map<string,string> Post;
    initializePost(Post);
	
    // Form
    puts("Status: 200 OK\r");
    puts("Content-Type: text/html\r");
    puts("\r");
    if(Post.find("username") != Post.end() && Post.find("password" ) != Post.end()) {
        cout << "POST: " << Post["username"];
    }
    

    
    return 0;
};
