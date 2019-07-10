clc
clear all

width = 4;
frames = 16;
begin = 1;
num = 200;
testcount = 40;

kk = 1;
Random_count = 1;

for nn = 1:Random_count
    test_point = sort(randperm(num, testcount));
    for i = begin:num
        filename = ['Flat_train', num2str(i), '.txt'];
%           filename = ['Round_test', num2str(i), '.txt'];
%         filename = ['Sawtooth_test', num2str(i), '.txt'];    

        data = load(filename);

        columns = {'Channel_11', 'Channel_12', 'Channel_13', 'Channel_14', ... 
                   'Channel_21', 'Channel_22', 'Channel_23', 'Channel_24', ...
                   'Channel_31', 'Channel_32', 'Channel_33', 'Channel_34', ...
                   'Channel_41', 'Channel_42', 'Channel_43', 'Channel_44'};

        x = [1:width];
        y = zeros(width, width);

        Ldif = length(data) - frames;
        if Ldif > 0
            if mod(Ldif, 2) == 0
                data(1:floor(Ldif/2)+4,:) = [];
                data(end-floor(Ldif/2)+4+1:end,:) = [];
            else
                data(1:floor(Ldif/2)+4,:) = [];
                data(end-floor(Ldif/2)+4:end,:) = [];
            end
        end

        data2 = table(data(:,1), data(:,2), data(:,3), data(:,4), ...
                      data(:,5), data(:,6), data(:,7), data(:,8), ...
                      data(:,9), data(:,10), data(:,11), data(:,12), ...
                      data(:,13), data(:,14), data(:,15), data(:,16), ...
                      'VariableNames', columns);

        %gifœ‘ æ
        for k = 1:frames
            for ii = 1:width
                y(ii,:) = data(k,ii*4-3:4*ii);
            end
            bar3(x, y);
            zlim([-0.3 0.3])
            m(k) = getframe;
    %         imind = frame2im(m(k));
    %         [imind,cm] = rgb2ind(imind, 256);
    %         if k == 1
    %             imwrite(imind,cm,gif_filename,'gif', 'Loopcount',inf,'DelayTime',0.1);
    %         else
    %             imwrite(imind,cm,gif_filename,'gif','WriteMode','append','DelayTime',0.1);
    %         end
        end
    %     movie(m, 1, 4)

        if kk <= length(test_point) && i == test_point(kk)
            writefilename = ['./Surface_Test_Random', num2str(nn), '/Ball_test_7d/Ball_test_7d', num2str(kk), '.csv'];
%             writefilename = ['./Surface_Test_Random', num2str(nn), '/Sawtooth_test/Sawtooth_test', num2str(kk), '.csv'];
%             writefilename = ['./Surface_Test_Random', num2str(nn), '/Round_test/Round_test', num2str(kk), '.csv'];
            kk = kk+1;
        else
            writefilename = ['./Surface_Test_Random', num2str(nn), '/Ball_train_7d/Ball_train_7d', num2str(i-kk+1), '.csv']; 
%             writefilename = ['./Surface_Test_Random', num2str(nn), '/Sawtooth_train/Sawtooth_train', num2str(i-kk+1), '.csv']; 
%             writefilename = ['./Surface_Test_Random', num2str(nn), '/Round_train/Round_train', num2str(i-kk+1), '.csv']; 
        end

        writetable(data2,writefilename);
    end
    test_point
    kk = 1;
end


