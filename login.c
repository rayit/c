#include <stdlib.h>
#include <iostream>
#include <map>
#include "getpost.h"
#include <err.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{
    
    if (-1 == pledge("stdio", NULL))
        err(EXIT_FAILURE, NULL);
        
    map<string,string> Post;
    initializePost(Post);
	
    // Form
    puts("Status: 200 OK\r");
    puts("Content-Type: text/html\r");
    puts("\r");
    if(Post.find("username") != Post.end() && Post.find("password" ) != Post.end()) {
        cout << "POST: " << Post["username"];
        cout << "<br /> " << Post["password"];
    }
    
    // query sql
    

    
    return 0;
};
