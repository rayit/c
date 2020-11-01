# c
## OpenBSD c and sqlite3

Goal is to make an easy website which uses c++ as backend. \
- Create DB 
- Login 
- Show data

Dependencies: 
doas

doas pkg_add git
doas rcctl enable httpd

\etc\httpd.conf
```
#[ MACROS ]
ext_ip = "127.0.0.1"
# ext_ip = "*"      # open to the outside network
# ext_ip = "egress" # open to only the primary IP address of the network interface

# [ GLOBAL CONFIGURATION ]
# none

# [ SERVERS ]
server "default" {
    listen on $ext_ip port 80
    root "/htdocs/"

    location "/cgi-bin/*" {
	fastcgi
	root "/"
    }
}

# [ TYPES ]
types {
    include "/usr/share/misc/mime.types"
}
```

Ispiration and tutorials:
https://learnbchs.org/
http://zetcode.com/db/sqlitec/
