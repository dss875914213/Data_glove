clc
clear all

width = 16;
height = 16;
frames = 160;
testframes = 40;
Random_count = 1;

columns = {'Channel_11', 'Channel_12', 'Channel_13', 'Channel_14', ... 
           'Channel_21', 'Channel_22', 'Channel_23', 'Channel_24', ...
           'Channel_31', 'Channel_32', 'Channel_33', 'Channel_34', ...
           'Channel_41', 'Channel_42', 'Channel_43', 'Channel_44'};

trainfront = zeros(height,width,frames);

testfront = zeros(height,width,testframes);

for nn = 1:Random_count
    for i = 1:frames
        frontfilename = ['./Surface_Test_Random', num2str(nn), '/Flat_train_soft/Flat_train_soft', num2str(i), '.csv'];
%         frontfilename = ['./Surface_Test_Random', num2str(nn), '/Round_train/Round_train', num2str(i), '.csv'];
%           frontfilename = ['./Surface_Test_Random', num2str(nn), '/Sawtooth_train/Sawtooth_train', num2str(i), '.csv'];
        Rawtrainfront(:,:,i) = table2array(readtable(frontfilename)) + 1;
    end

    for i = 1:testframes
        frontfilename = ['./Surface_Test_Random', num2str(nn), '/Flat_test_soft/Flat_test_soft', num2str(i), '.csv'];
%         frontfilename = ['./Surface_Test_Random', num2str(nn), '/Round_test/Round_test', num2str(i), '.csv'];
%         frontfilename = ['./Surface_Test_Random', num2str(nn), '/Sawtooth_test/Sawtooth_test', num2str(i), '.csv'];
        Rawtestfront(:,:,i) = table2array(readtable(frontfilename)) + 1;
    end


    % 数据归一化
    for i = 1:frames
        for j = 1:height
            for q = 1:width
                trainfront(j,q,i) = (Rawtrainfront(j,q,i) - min(min(Rawtrainfront(:,:,i)))) ...
                    ./ (max(max(Rawtrainfront(:,:,i))) - min(min(Rawtrainfront(:,:,i))));
            end
        end
    end
    
    % 0均值 1方差归一化
%     for i = 1:frames
%         trainfront(:,:,i) = mapstd(Rawtrainfront(:,:,i));
%     end

    % 写csv文件
    for i = 1:frames
        Wtrainfront = table(trainfront(:,1,i), trainfront(:,2,i), ...
                            trainfront(:,3,i), trainfront(:,4,i), ...
                            trainfront(:,5,i), trainfront(:,6,i), ...
                            trainfront(:,7,i), trainfront(:,8,i), ...
                            trainfront(:,9,i), trainfront(:,10,i), ...
                            trainfront(:,11,i), trainfront(:,12,i), ...
                            trainfront(:,13,i), trainfront(:,14,i), ...
                            trainfront(:,15,i), trainfront(:,16,i), ...
                            'VariableNames', columns);
% 线性归一化写文件
        filenamefront = ['./Surface_Test_Hardness_Data/Flat_test_soft_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Round_train_GYH/Round_train_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Sawtooth_train_GYH/Sawtooth_train_GYH', num2str(i), '.csv'];

% 0均值归一化写文件
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Surface_train_Zero_GYH/Flat_train_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Surface_train_Zero_GYH/Round_train_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Surface_train_Zero_GYH/Sawtooth_train_GYH', num2str(i), '.csv'];
        writetable(Wtrainfront,filenamefront);

    end

    % 线性归一化
    for i = 1:testframes
        for j = 1:height
            for q = 1:width
                testfront(j,q,i) = (Rawtestfront(j,q,i) - min(min(Rawtestfront(:,:,i)))) ...
                    / (max(max(Rawtestfront(:,:,i))) - min(min(Rawtestfront(:,:,i))));
            end
        end
    end
    
    % 0均值 1方差归一化
%     for i = 1:testframes
%         testfront(:,:,i) = mapstd(Rawtestfront(:,:,i));
%     end


    for i = 1:testframes
        Wtestfront = table(testfront(:,1,i), testfront(:,2,i), ...
                            testfront(:,3,i), testfront(:,4,i), ...
                            testfront(:,5,i), testfront(:,6,i), ...
                            testfront(:,7,i), testfront(:,8,i), ...
                            testfront(:,9,i), testfront(:,10,i), ...
                            testfront(:,11,i), testfront(:,12,i), ...
                            testfront(:,13,i), testfront(:,14,i), ...
                            testfront(:,15,i), testfront(:,16,i), ...
                            'VariableNames', columns);
% 线性归一化写文件
        filenamefront = ['./Surface_Test_Hardness_Data/Flat_test_soft_GYH', num2str(i+160), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Round_test_GYH/Round_test_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Sawtooth_test_GYH/Sawtooth_test_GYH', num2str(i), '.csv'];

% 0均值归一化写文件
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Surface_test_Zero_GYH/Flat_test_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Surface_test_Zero_GYH/Round_test_GYH', num2str(i), '.csv'];
%         filenamefront = ['./Surface_Test_Random', num2str(nn), '/Surface_test_Zero_GYH/Sawtooth_test_GYH', num2str(i), '.csv'];
        writetable(Wtestfront,filenamefront);
    end
end





% for i = 1:frames
%     subplot(1,frames,i)
%     imagesc(trainfront(:,:,i));
%     colormap(gray);
% end
% title('Iron Data');


% figure
% for i = 1:testframes
%     subplot(1,testframes,i)
%     imagesc(testfront(:,:,i));
%     colormap(gray);
% end
% title('Wood Data');


