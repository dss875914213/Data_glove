clc;  
  
global t;
global x;  
global m1; 
global m2;
  
t = [0];
m1 = [0];
m2 = [0];
x = -100;   
p = plot(t,m1,'EraseMode','background','MarkerSize',5);
axis([x-200 x+200 0 5]);
axis 'auto y' 
grid on;  
  
%%  
  
try  
    s=serial('com3');  
catch  
    error('cant serial');  
end  
set(s,'BaudRate', 115200,'DataBits',8,'StopBits',1,'Parity','none','FlowControl','none');  
s.BytesAvailableFcnMode = 'terminator';  
s.BytesAvailableFcn = {@callback_line,p};  
  
fopen(s);  
  
pause;  
fclose(s);  
delete(s);  
clear s  
close all;  
clear all;  