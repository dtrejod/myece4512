% Digital Communications 
% Lab 4
% By: Devin Trejo

%% 
clear; clc; close all;

A = 12.0;
Tb = 300E-6;
poleN = 5;
lpfType = 'Chebyshev II';

% Simulation Specific Input
%
Ts = 10E-6; % Sample Time Period
fs = 1/Ts; % Sample Frequency
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = 10E4*Tb; % Simulation Stop Time (sec) - Simulate over one period

% Transmit Delay Time
%
delta = round(310E-6*fs);

% Cutoff frequency of LPF
%
fT = 1.2*1/Tb;
fTrad = (2*pi)*fT;

% Pulse Generator Parameters
%
pulsPeriod = Tb;
pulsWidth = 20;
pulsPhase = Tb/15;

% Noise Power
%
% 18.04
% 28.59
% 36.00
% 45.32
% 71.82
% 113.84

sigma = 113.84;

% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('lab4', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab4',[],options);
