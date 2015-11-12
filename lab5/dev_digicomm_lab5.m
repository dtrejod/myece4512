% Digital Communications 
% Lab 5
% By: Devin Trejo

%% 
clear; clc; close all;

% --------------------
% - Given parameters - 
% --------------------
% Birthday month April (4)
%
A0 = 0.2; % Amplitude for binary 0
A1 = 1.25; % Amplitude for binary 1
Ac = 12; % Amplitude for carrier
fc = 50E3; rc = fc*2*pi;% Frequency of carrier
rb = 5E3; Tb = 1/rb;% Datarate bits/sec

% ---------------------------------
% - Operator Chossen parameters - 
% ---------------------------------
% Simulation Specific Input
%
Ts = Tb/500; % Sample Time Period (100 Samples per bit time)
fs = 1/Ts; % Sample Frequency
intT = Tb*fs; intF = 1/intT; % Samples in one period

% -------------------------
% - Calculated parameters - 
% -------------------------
% Time Data
%
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = 10000*Tb; % Simulation Stop Time (sec)
t = startTime:Ts:stopTime; % Time vector
samL = length(t);

% Signals for binary 0/1
%
f0 = 1/(2*Tb); r0 = 2*pi*f0;
f1 = 1/(2*Tb); r1 = 2*pi*f1;
Ar = abs(A1-A0);
m0 = A0*sin(r0*t); % Representation of Binary 0
m1 = A1*sin(r1*t); % Representation of Binary 1

% Power in A0/A1
%
P0 = (Ac*A0)^2/2;
P1 = (Ac*A1)^2/2;
PT = (P0*.5+P1*.5)
C = -2.363E4/2;

% Carrier Signal
%
mc = Ac*sin(rc*t);

% FFT properties
%
NFFT = 2^nextpow2(samL*10);
samL = samL;
fstart = 0;
fstop = fc*2;

% Power (variance of noise)
%
% Caluculate Energy in Noise
%
s0 = m0.*mc;
s1 = m1.*mc;
Ed = sum((s1(1:Tb*fs)-s0(1:Tb*fs)).^2) % Intergrate over one bit time

% Probability of Error for each SNR
%
SNR = [inf 12 10 8 6 4 2 0];
i=1;
for SNRi = SNR
    N0(i) = (PT*intT)/db2mag(SNRi);
    Pnois(i) = db2mag(mag2db(PT)-SNRi);
    Perror(i) = qfunc(sqrt(Ed/(2*N0(i))));    
    i = i+1;
end

% Print to terminal results
%
Pnois
PnoisdB = mag2db(Pnois)
N0
N0dB = mag2db(N0)
Perror

% The above cacluates all the noise values. We specify one below:
% N0 = [0 0.7246 0.9122 1.1483 1.4457 1.8200 2.2912 2.8845]e4
%
N0 = 0;

% Plots
%
% figure();
% plot(t,m0,t,m1,t,mc);
% xlim([0 4*Tb]); grid on;
% ylim([-A1 A1]);
% legend('m0','m1');
% xlabel('time (secs)');
% ylabel('Voltage (V)');
% legend('m0','m1','Carrier');
% 
% figure();
% plot(t,s0,t,s1);
% xlim([0 4*Tb]); grid on;
% ylabel('Voltage (V)');
% xlabel('time (secs');
% legend('s0','s1');

% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('lab5', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab5',[],options);

%%
close all; % DON"T CLEAR VARIABLES. Uses values from previous section


