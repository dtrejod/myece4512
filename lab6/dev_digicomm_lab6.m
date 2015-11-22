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
Ac = 5; % Amplitude for carrier
fc = 20E3; rc = fc*2*pi;% Frequency of carrier
rb = 1E3; Tb = 1/rb;% Datarate bits/sec
ph1 = 50*pi/180;
ph0 = -25*pi/180;

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
s0 = Ac*sin(rc*t+ph0); % Representation of Binary 0
s1 = Ac*sin(rc*t+ph1); % Representation of Binary 1

% Power in A0/A1
%
P0 = (Ac)^2/2;
P1 = (Ac)^2/2;
PT = (P0*.5+P1*.5)
C = -2.363E4/2;

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
% N0 = [0 1.5699 1.9764 2.4882 3.1324 3.9435 4.9646 6.2500]e3
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
% SNR plot
%
figure(); semilogy(SNR,Perror); grid on;
xlabel('Signal to Noise Ratio (dB)');
ylabel('Bit Error Rate');
hold on;
semilogy([inf 10 8 6 4 2 0],[0 4.05E-6 2.06E-4 2.41E-3 ...
    1.25E-2 3.75E-2 7.93E-2]);
legend('Non-Ideal BPSK','Ideal BPSK')
% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('dev_lab6', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('dev_lab6',[],options);

%%
close all; % DON"T CLEAR VARIABLES. Uses values from previous section


