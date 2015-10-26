# knockedup-webserver
Simple c++ web server to write requester IP to file and then optionally reload primary web server.

The knockedup-webserver includes code from [Civetweb](https://github.com/civetweb/civetweb), which is licensed under the MIT license.

## Overview
KnockedUpWebServer is a simple cross-platform web server that will add a remote requestor's IP to a text file. A common scenario is to add requestor IP to an "allows" include file that is referenced by a primary web server.

This is similar in concept to that of [port knocking](https://en.wikipedia.org/wiki/Port_knocking), but operates at the web server layer instead of at the firewall layer.  This is sometimes referred to as web knocking.  KnockedWebServer is different than existing alternatives because it has no dependencies or special setup requirements. Specifically, it does not require PHP or CGI.

Note that there are very few scenarios where web knocking is appropriate, and if not handled carefully, it can lead to serious vulnerabilities. Generally, IPs should be blocked at the firewall layer. Blocking IPs at the web server layer is appropriate when the IP blocking is only relevant to certain webapps or URLs on the server.  And in those cases, it's almost always better to use BasicAuth or some other form of authentication.  Web server IP blocking should generally be used only as a secondary level of protection with web knocking then provided as a self-service tool for authorized remote end users.


## Configuration
Configurable parameters:

 - **knocksFilePath** - Path to file where requestor IP will be written on a new line. (default: /etc/nginx/knocks.txt")
 - **maxAllowedIps** - max number of lines that will be kept in the knocks text file. FIFO. (default: 50)
 - **format** - "nginx" or "apache" (default: nginx)
 - **port** - port of the KnockedUpWebServer. (default: 12080)

Upon startup, the server will look for a "KnockedUpWebServer.conf" in the current directory. If not found, it will look for "/etc/KnockedUpWebServer.conf". If not found, it will fallback to the defaults.

## Usage
Sample nginx configuration:

```nginx
location /knock {
	proxy_pass http://127.0.0.1:12080/knock;
	proxy_set_header X-Real-IP       $remote_addr;
	proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

	auth_basic "Secure Site";
	auth_basic_user_file /etc/nginx/securesite.htpasswd;
}

location / {
	include /etc/nginx/knocks.txt;
	deny all;
}
```

## Download
Binaries not available, but it will easily compile using GCC on linux (32 and 64). A Code::Blocks project file exists in the repo.