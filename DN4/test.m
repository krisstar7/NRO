% Open the file for reading
filename = 'datoteka_A_b.txt';
fileID = fopen(filename, 'r');

% Initialize matrices
A = zeros(256, 256); % 256x256 matrix
b = zeros(256, 1);   % 256x1 column vector
fgetl(fileID);
% Read matrix A
for i = 1:256
    line = fgetl(fileID);               % Read a line
    values = str2double(split(line, ';')); % Split the line by semicolon and convert to numbers
    A(i, :) = values';                 % Assign the row to A
end

fgetl(fileID);
fgetl(fileID);
% Read vector b
for i = 1:256
    line = fgetl(fileID);              % Read a line
    b(i) = str2double(line);           % Convert to number and assign to b
end

% Close the file
fclose(fileID);

% Gauss-Seidel parameters
n = size(A, 1);         % Number of rows in A
x = zeros(n, 1);        % Initial guess (zeros)
max_iter = 2000;        % Maximum number of iterations
tol = 1e-10;            % Convergence tolerance

T = linsolve(A, b);
