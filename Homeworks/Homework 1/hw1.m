clear
clc

syms n
f = [log2(n) sqrt(n) n n*log2(n) n*n n*n*n 2^n factorial(n)];
t = [1 60 60*60 60*60*60 60*60*60*24 60*60*60*24*30 60*60*60*24*30*365 60*60*60*24*30*365*100];

for i = 1:length(f)
    for j = 1:5
        a = uint64(solve(f(i)==t(j), n, 'Real', true));
        fprintf('%s = %d, n = %d\n', char(f(i)), t(j), a);
    end
end
fprintf('\n');