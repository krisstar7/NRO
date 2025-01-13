% Read the file A_b.txt and perform parallelized Gauss-Seidel
fileName = 'A_b.txt';

% Open and parse the file
fileID = fopen(fileName, 'r');

% Read matrix A
line = fgetl(fileID);

n = sscanf(line, 'A: n=%d');

A = zeros(n, n);

for i = 1:n
    line = fgetl(fileID);
    A(i, :) = sscanf(line, '%f;');
end

line = fgetl(fileID);
line = fgetl(fileID);

b_n = sscanf(line, 'b: n->%d');

b = zeros(n, 1);

for i = 1:n
    b(i) = str2double(fgetl(fileID));
end

fclose(fileID);

T = ones(n, 1)*100;
T_new = T;

%parpool('local');

tic;
for iitt = 1:1000

    %parfor jj = 1:n
    for jj = 1:n
		d = b(jj);

        for ii = 1:n
            if(jj ~= ii)
                d = d- A(jj, ii) * T(ii);
        
            end
            T_new(jj) = d / A(jj, jj);
        end
    end
	T = T_new;
end
timeElapsed = toc;


fprintf('Cas: %.4f \n', timeElapsed);


%delete(gcp('nocreate'));
