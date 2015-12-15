clear; clc; close all;
% Simulation parameters
%
% --------------------
% - Given parameters - 
% --------------------
%
Ac = 5; % Amplitude for carrier
fc = 20E3; rc = fc*2*pi;% Frequency of carrier
Tb = 250E-6; rb = 1/Tb;% Datarate bits/sec

% ---------------------------------
% - Operator Chossen parameters - 
% ---------------------------------
% Simulation Specific Input
%
Ts = Tb/500; % Sample Time Period (100 Samples per bit time)
fs = 1/Ts; % Sample Frequency
intT = Tb*fs; intF = 1/intT; % Samples in one period
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = Tb; % Simulation Stop Time (sec)
t = startTime:Ts:stopTime; % Time vector
samL = length(t);

% Quadratre
%
Q = Ac*sin(rc*t);

% In phase
%
I = Ac*cos(rc*t);

% Bit squence
%
zeroQ = 0;
zeroI = 0;
oneQ = 3;
oneI = 1;
twoQ = 3;
twoI = -1;
threeQ = -3;
threeI = 0;

% Plot constelation plot
%
plot(zeroI, zeroQ, '*');
hold on
plot(oneI, oneQ, '*');
plot(twoI, twoQ, '*');
plot(threeI, threeQ, '*');
axis([-3 3 -5 5]);
xlabel('In-Phase (I)');
ylabel('Quadrature (Q)');
title('4-QAM Constellation Plot');
legend('00','01','10','11');
plot([0 0], ylim, '--k', 'LineWidth',1.5); % Axis x-axis
plot(xlim, [0 0], '--k', 'LineWidth',1.5); % Axis y-axis
grid on;

% Create signals
%
symZero = zeroQ*Q + zeroI*I;
symOne = oneQ*Q + oneI*I;
symTwo = twoQ*Q + twoI*I;
symThree = threeQ*Q + threeI*I;

% Find energy in 4-QAM for each symbol
%
Pzero = sum(symZero.^2)/(Tb*fs)
Pone = sum(symOne.^2)/(Tb*fs)
Ptwo = sum(symTwo.^2)/(Tb*fs)
Pthree = sum(symThree.^2)/(Tb*fs)

% Plot all three
figure();
plot(t, symZero, t, symOne, t, symTwo, t, symThree);
grid on;
xlabel('time (secs)');
ylabel('Amplitude');
title('4 QAM');
legend('00','01','10','11');


%% SNR Calculation
clear; clc;

% Max energy of Rx signal
%
ETx = 250;
% Probability of Error for each SNR
%
SNR = [inf 12 10 8 6 4 2 0];
i=1;
for SNRi = SNR
    N0(i) = (ETx)/db2mag(SNRi);
    Perror(i) = qfunc(sqrt(ETx/(2*N0(i))));   
    i = i+1;
end
% Convert N0 to dB
%
N0dB = mag2db(N0);

% Print out to console
%
disp(N0)
disp(N0dB)