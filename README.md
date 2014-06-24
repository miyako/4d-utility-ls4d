4d-utility-ls4d
===============

A small command-line program to monitor 4D Server UDP broadcasts.

System Requirements:

* Windows 32/64 bits
* Mac OS X 10.5 or later, 32/64 bits Intel Universal Binary

Usage
-----

ls4d

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



