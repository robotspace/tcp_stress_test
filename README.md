Purpose
======

  This project is built to send data as quickly as possible through multi-threads.

How to use
------
### 1. Build
Execute script build.sh from project. It will create a.out by default.
### 2. Execution
Program will receive parameters as appointed sequence, e.g.<br/>
<b>a.out 127.0.0.1 8888 2 'hello world'</b><br/>
<b>a.out</b>: the executable program<br/>
<b>127.0.0.1</b>: target host<br/>
<b>8888</b>: target port number<br/> 
<b>2</b>: threads number that you want to create<br/>
<b>hello world</b>: message you want to send to host. Use ' if you want to send Ctrl letters such as <b>'$hello world;ok!'</b><br/> 

Work around
------
### 1. Keep selfish thread data
### 2. Terminate a thread gracefully if err occurs
