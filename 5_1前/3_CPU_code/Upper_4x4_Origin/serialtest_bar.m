clc;  

global width        %’Û¡–Œ¨∂»%
global m;           
global initcap;     
global x;  
global ready;
global h;
global countinit;
global countlog;

global logline;

countlog = 0;

logline = 0;
width = 4;
m = zeros(1,width*width); 
initcap = zeros(width,width);
% initcap = [15.082160 15.371111 12.925615 14.708738;14.172603 15.669765 12.169536 13.669928;12.676823 14.574642 11.417607 12.141841;13.176724 14.050509 10.667524 12.688128];

% initcap = [13.607613 13.659083 12.102834 12.639430;13.953806 13.693933 12.383945 12.540651;13.295347 12.824069 11.608939 11.709102;12.133303 12.337323 11.259050 10.706531];

countinit = 0; 
ready = 0;   
t = [0];

x = -100;
% p = plot(t,m1,'EraseMode','background','MarkerSize',5); 


h = bar3([1:width],zeros(width,width));
grid on;  
  
%%  
  
try  
    s=serial('com5');  
catch  
    error('cant serial');  
end  
set(s,'BaudRate', 115200,'DataBits',8,'StopBits',1,'Parity','none','FlowControl','none');  
s.BytesAvailableFcnMode = 'terminator';  
s.BytesAvailableFcn = {@callback_bar,h};  
  
fopen(s);   
pause;  
fclose(s);  
delete(s);  
clear s  
close all;  
clear all;  