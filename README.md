# c
## OpenBSD c and sqlite3

Goal is to make an easy website which uses c as backend. \
- Create DB
- Login 
	1. login  
		Endpoint
	2. check username and pw
		using: [https://man.openbsd.org/crypt_checkpass.3#crypt_newhash]
    3. generate JWT token 
		Had to install libjwt
		git clone https://github.com/benmcollins/libjwt.git
		cd libjwt
		cmake .
		doas cmake install
		
		
		#include <jwt.h>
		
		# ssh-keygen -t rsa -b 4096 -m PEM -f jwtRS256.key
		# Don't add passphrase
		# openssl rsa -in jwtRS256.key -pubout -outform PEM -out jwtRS256.key.pub
		
		openssl genrsa -out private.pem 2048
		
		# extract public
		openssl rsa -in private.pem -outform PEM -pubout -out public.pem

		
- Login failure log.. (add fail in log)
		
- Look into PLEDGE

- Show data

Dependencies: 
OpenBSD
httpd
doas

```sh
doas pkg_add git
doas rcctl enable httpd
```

/etc/httpd.conf
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
