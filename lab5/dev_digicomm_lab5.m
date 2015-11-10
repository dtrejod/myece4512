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
fc = 50E3; % Frequency of carrier
rb = 5E3; % Datarate bits/sec

% ---------------------------------
% - Operator Chossen parameters - 
% ---------------------------------
% Simulation Specific Input
%
Tb = 1/rb; % Bit time
Ts = Tb/100; % Sample Time Period (100 Samples per bit time)
fs = 1/Ts; % Sample Frequency
Threshold = A0^2*Tb;
% Transmit Delay Time
%
delta = round(310E-6*fs);

% -------------------------
% - Calculated parameters - 
% -------------------------
% Time Data
%
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = 1000*Tb; % Simulation Stop Time (sec)
t = startTime:Ts:stopTime; % Time vector

% Signals for binary 0/1
%
f0 = 1/(2*Tb);
f1 = 1/(2*Tb);
m0 = A0*sin(2*pi*f0*t); % Representation of Binary 0
m1 = A1*sin(2*pi*f1*t); % Representation of Binary 1
figure();
plot(t, m0, t, m1);
legend('m0','m1');

% Power in A0/A1
%
P0 = A0^2*Tb
P1 = A1^2*Tb

% Carrier Signal
%
carrier = Ac*sin(2*pi*fc*t);
reference = carrier;

% Noise Power
%
sigma = 0;

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