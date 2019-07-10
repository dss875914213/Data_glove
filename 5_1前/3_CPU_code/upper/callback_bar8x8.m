function callback(s, BytesAvailable,p)  
    
    global initcap;
    global width;
    global ready;
    global m;
    global x;   
    global h;
    global countinit;
    global countlog;
    global logline
    
    out = fscanf(s);

    data = str2num(out);
    x = [1:width];
%     m = [m;m(end,:)];
    aa = length(find(m(end,:)==0));
    
    %ready = 1 ��ʼ��¼��ͨ������ȡֵ��ȡǰ10�����˲�ȡƽ��
    if aa == 0 && ready ==  0
         for i = 1:width
             initcap(i,:) = initcap(i,:) + m(end,(i-1)*width+1:i*width);
         end
        countinit = countinit+1;
        if countinit == 20
            initcap = initcap./20;
            ready = 1;
        end
    end
    
    
        
    %data(1) ��ǵ�λ�ñ�ţ�1~64, data(2) ����
    m(end,data(1)) = data(2);
    
    y = zeros(width,width);
    
    if ready == 1
        block1 = m(end,1:16);
        block2 = m(end,17:32);
        block3 = m(end,33:48);
        block4 = m(end,49:64);
        
        re_block1 = reshape(block1,4,4)';
        re_block2 = reshape(block2,4,4)';
        re_block3 = reshape(block3,4,4)';
        re_block4 = reshape(block4,4,4)';
        
        y = [re_block1,re_block2;re_block3,re_block4];
        
        for i = 1:width
            y(i,:) = m(end,(i-1)*width+1:i*width);
        end
        dy = (y-initcap)./initcap;
        meansdy = sum(sum(dy)) / 16;
        drawnow
        delete(h);
        
        h = bar3(x,3.*dy);
        
        hold on
        for n=1:numel(h)  
            cdata=get(h(n),'zdata');  
            set(h(n),'cdata',cdata,'facecolor','interp')  
        end       

    %     set(gca,'Xticklabel',{'1','2'});
    %     set(gca,'Yticklabel',{'1','2'});
        zlim([-0.5 0.3]);
    
        %����д��txt�ļ�,ÿ������дһ��
%         fid = fopen('log.txt','a+');
%         fprintf(fid,'%d%10.7f\r\n',data);
%         fclose(fid);
        
        %ÿwidth*width������дһ��
        countlog = countlog + 1;
%         if countlog == width*width
% %             fid = fopen('./Surface_Test/Flat_train/Flat_test200.txt','a+');
% 
% %             fid = fopen('./Surface_Test/Sawtooth_train/Sawtooth_test200.txt','a+');
% 
% %             fid = fopen('./Surface_Test/Round_train/Round_test200.txt','a+');
% 
% %             fid = fopen('./Surface_Test/Flat_train_hard/Flat_test_hard200.txt','a+');
% 
%             fid = fopen('./Surface_Test/Ridge_train_7d/Ridge_test_7d0.txt','a+');
%             
%             fprintf(fid,'%10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f %10.7f\r\n',3.*dy);
%             logline = logline + 1
%             fclose(fid);
%             countlog = 0;
%         end
        
        %ÿwidth*width������дһ�Σ�д��4*4������ʽ
%         countlog = countlog + 1;
%         if countlog == width*width
%             fid = fopen('log.txt','a+');
%             fprintf(fid,'%10.7f%10.7f%10.7f%10.7f\r\n',m(end,1:4));
%             fprintf(fid,'%10.7f%10.7f%10.7f%10.7f\r\n',m(end,5:8));
%             fprintf(fid,'%10.7f%10.7f%10.7f%10.7f\r\n',m(end,9:12));
%             fprintf(fid,'%10.7f%10.7f%10.7f%10.7f\r\n',m(end,13:16));
%             fprintf(fid,'\r\n');
%             fclose(fid);
%             countlog = 0;
%         end
        
    end
end  