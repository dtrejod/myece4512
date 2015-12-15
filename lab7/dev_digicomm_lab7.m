% Digital Communications 
% Lab 7
% By: Devin Trejo

%% 
clear; clc; close all;

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

% -------------------------
% - Calculated parameters - 
% -------------------------
% Time Data
%
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = 10000*Tb; % Simulation Stop Time (sec)
t = startTime:Ts:stopTime; % Time vector
samL = length(t);

% FFT properties
%
NFFT = 2^nextpow2(samL*10);
samL = samL;
fstart = 0;
fstop = fc*2;

% Specify SNR: N0 below:
% N0 = [0 62.7972 79.0569 99.5268 125.2968 157.7393 198.5821 250.0000]
%SNR = [inf 12 10 8 6 4 2 0];
N0 = 62.7972/2;

% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('dev_lab7', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('dev_lab7',[],options);
