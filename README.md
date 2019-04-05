Purpose
======

  This project is built to send data as quickly as possible through multi-threads.

How to use
------
### 1. Build
Execute script build.sh from project. It will create a.out by default.
### 2. Execution
Program will receive parameters as appointed sequence, e.g.<br/>   a.out 127.0.0.1 8888 2 'hello world'</b><br/>
a.out: the executable program<br/>
127.0.0.1: target host<br/>
8888: target port number<br/> 
hello world: message you want to send to host. Use ' if you want to send Ctrl letters such as <b>'$hello world;ok!'</b><br/> 

Work around
------
### 1. Keep selfish thread data
### 2. Terminate a thread gracefully if err occurs