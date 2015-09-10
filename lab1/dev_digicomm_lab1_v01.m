% Digital Communications 
% Lab 1
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 7; % Amplitude of sine wave (V)
T = 2E-3; % Period of sine wave (ms)
TH = 3.5; % Threshold of sine wave (V)

% Simulation Specific Input
samTime = 2E-6; % Simulation sample period
startTime = 0; % Simulation Start Time (sec)
stopTime = T; % Simulation Stop Time (sec)

% Convert from period to frequency
f0 = 1/T;
fs = 1/samTime;

% Find the discrete time frequency
dis_sigf = f0/fs;

% Calculate discrete time period
samPeriod = ceil(1/dis_sigf);

% We want the simulation to run for one period
samPerSim = samPeriod;

% Simulate the simulink model
options = simset('SrcWorkspace','current');
set_param('Lab1', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('Lab1',[],options);

% Autoscale the all opened scope
set(0, 'showhiddenhandles', 'on')
scope = findobj(0, 'Tag', 'SIMULINK_SIMSCOPE_FIGURE');
for i=1:length(scope)
  % this is the callback of the "autoscale" button:
  simscope('ScopeBar', 'ActionIcon', 'Find', scope(i))
end
set(0, 'showhiddenhandles', 'off')

% Extract Data from Simunlink Simulation
x = mod_sig.Data;
sig = x(2:length(x))';

% Find Fourier Series Complex Components we define a inline function
n = 0:samPerSim-1;
c  = @(k) (1/samPerSim) * sum(sig.*exp(-j*2*pi*k*n/samPerSim) );

% lets solve for "c" for many different values of k by using a loop
kVec = 0:5;
cVec = 0*kVec;
i = 1;
for k = kVec
    cVec(i) = c(k);
    i = i + 1;
end

% Find the Fourier Series Components in Polar Form (degrees)
% polarCVec = '';
for i = 1:length(cVec)
    polarCVec(i) = cellstr(rtp(cVec(i), 'd'));
end

% Print Fourier Series Cofficients to Screen
fprintf('Fourier Series Complex Components:\n');
for i=0:length(cVec)-1
   fprintf(['    - Fourier Series Coefficient k=%d:\n'...
       '        ck = %s / %s \n'], ...
       i, num2str(cVec(i+1)), polarCVec{i+1});
end
fprintf('\n\n');

% Find Fourier Series Complex Components we define a inline function
n = 0:samPerSim-1;
a  = @(k) (2/samPerSim) * sum(sig.*cos(2*pi*k*n/samPerSim));
b  = @(k) (2/samPerSim) * sum(sig.*sin(2*pi*k*n/samPerSim));

a0 = 1/samPerSim * sum(sig);
kVec = 0:5;
aVec = 0*kVec;
bVec = 0*kVec;
i = 1;
for k = kVec
    aVec(i) = a(k);
    bVec(i) = b(k);
    i = i + 1;
end

fprintf('Fourier Series Rect Components:\n');
fprintf(['    - Fourier Series Coefficient k=0:\n'...
       '        a0 = %s\n'], ...
       num2str(a0));
for i=1:length(aVec)
   fprintf(['    - Fourier Series Coefficient k=%d:\n'...
       '        ak = %s / bk = %s \n'], ...
       i, num2str(aVec(i)), num2str(bVec(i)));
end
fprintf('\n\n');

