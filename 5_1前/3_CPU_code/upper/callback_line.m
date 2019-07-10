function callback(s, BytesAvailable,p)  
      
    global t;
    global x;  
    global m1;
    global m2;
  
    out = fscanf(s);

    data = str2num(out);
      
    %data(1) 标记点位置编号：1~64, data(2) 数据
    if(data(1) == 1)
        m1 = [m1 data(2)];
        t = linspace(1,length(m1),length(m1));
        plot(t,m1,'r');
        hold on
%         set(p, 'XData',t1,'YData',m1(1,:),'Color','red');         
%     else if(data(1) == 2)     
%         m2 = [m2 data(2)];
%         t = linspace(1,length(m2),length(m2));
%         plot(t,m2,'b');
%         hold on
% %         set(p, 'XData',t2,'YData',m2(1,:),'Color','blue'); 
%         end
        
      
    drawnow  
    x = x+1;
    axis([x-200 x+200 0 5]); 
    axis 'auto y'
    
    %数据写入txt文件,也可以放到判断中分开写文件
    fid = fopen('data0513_2.txt','a+');
    fprintf(fid,'%d%10.7f\r\n',data);
    fclose(fid);
    end
end  