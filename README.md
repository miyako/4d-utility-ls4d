![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm%20|%20win-32%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-utility-ls4d)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-utility-ls4d/total)

4d-utility-ls4d
===============

A small command-line program to monitor 4D Server UDP broadcasts.

Usage
-----

```
ls4d
```

returns list of 4D Server host names , IP address and published names. 
columns are tab delimited, rows are linefeed delimited.
each item is limited to 32 bytes.

by default, listens on port 19813 for 2 seconds each line.

options

```
-p, --port port number of the server (default=19813)
-w, --wait number of seconds to wait for each udp line(default=2)
-h, --help display this information
```

the information is decoded according to the system encoding,
since 4D Server does not broadcast in UTF-8.



