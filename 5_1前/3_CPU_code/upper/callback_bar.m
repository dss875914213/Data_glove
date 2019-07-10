function callback(s, BytesAvailable,p)  
    
    global initcap;
    global width;
    global ready;
    global m;
    global x;   
    global h;
    global countinit;
    global Su;
%     global countlog;
%     global logline
    global flag;
    global add_num;
    add_num=add_num+1;
    ylim_max=0.03;
    

    out = fscanf(s);
%    disp(out)
    data = str2num(out);
    x = 1:width;
%     m = [m;m(end,:)];
    aa = length(find(m(end,:)==0));
    
    %ready = 1 开始记录各通道电容取值，取前10个做滤波取平均
    if aa==0 && ready ==  0
        add_num=0;
         for i = 1:width
             initcap(i,:) = initcap(i,:) + m(end,(i-1)*width+1:i*width);
         end
        countinit = countinit+1;
        if countinit == 3
            initcap = initcap./3;
            ready = 1;
        end
        disp(3-countinit);
        m = zeros(1,width*width); 
    end
          
    %data(1) 标记点位置编号：1~64, data(2) 数据
    m(end,data(1)) = data(2);

    y = zeros(width,width);
    
    if mod(add_num,8)==0 &&ready == 1
        disp(add_num)
        if add_num==64
            add_num=0;
        end
        %归一化处理
        for i = 1:width
            y(i,:) = m(end,(i-1)*width+1:i*width);
        end
        dy = (y-initcap)./10000;
        
        Su = gt(abs(dy),ylim_max);
%         disp('initcap')
%         disp(initcap)
%         disp('y')
%         disp(y)
%         disp('Su')
%         disp(Su);
        if sum(sum(Su))==0
            Su = gt(abs(dy),-0.005);
            if sum(sum(Su))==64
%                 Su = gt(abs(dy),0.005);
%     %             disp(Su)
%                  %disp(dy)
%                 if sum(sum(Su))>0

                    
%                     delete(h);
                    drawnow
                    h = bar3(x,dy);
                    
%                     flag=1;
%                 elseif flag==1
%                     disp(111)
%                      flag=0;
%                      
% %                      delete(h);
%                      dss = zeros(width,width);
%                      h = bar3(x,dss);
%                      drawnow
%                 end
            end
        end
       
        zlim([-ylim_max ylim_max]);
        %m = zeros(1,width*width); 
    end
end  