% Digital Communications 
% Lab 2
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 1; % Amplitude of sine wave (V)
N1 = 0.1E-3; % Time legnth of Ramp1
N2 = 0.2E-3; % Time legnth of constant
N3 = 0.25E-3;% Time legnth of Ramp2
T = 1.5E-3;  % Period of waveform (secs)

% Simulation Specific Input
Ts = 1E-6;
fs = 1/Ts;
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = T; % Simulation Stop Time (sec)

% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------

% ---------------------------
% - Simulate Simulink Model -
% ---------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('lab2', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab2',[],options);

% Extract Data from Simunlink Simulation. The simulation spits out one
% extra sample so we truncate it by one. We also define the signal in terms
% of only one period
x = sig.Data';
sigP = x; % Signal over one period

% Print scope and spectrum analyzer to figures
figure();
plot(sig);
grid on
xlabel('time (secs)');
ylabel('Amplitude (V)');
legend('Original Signal');

% ------------------------------------
% - Find Fourier Series Coefficients -
% ------------------------------------

% Find number of samples in one period.
N = length(x);

% Find Fourier Series Complex Components. We define a inline function
n = 0:N-1;
c  = @(k) (1/N) * sum(sigP.*exp(-j*2*pi*k*n/N));

% Lets solve for "c" for many different values of k by using a loop
kVec = -5:5;
X = 0*kVec;
i = 1;
for k = kVec
    X(i) = c(k);
    i = i + 1;
end

% -------------------
% - Calculate Power -
% -------------------

% Calculate Power two different ways
Pav = 1/N*sum(x.^2); % Assume RL = 1 ohm
PavdBm = pow2db(Pav) + 30; % Power calculated using Parsevals (in dBm)

Pav2 = sum(abs(X).^2);
Pav2dBm = pow2db(Pav) + 30;

% Print to console the findings
fprintf(['Power in signal = %0.2f Watts / %0.2f dBm \n'...
    'Power in signal as specified using Parserval''s theorem = '...
    '%0.2f Watts / %0.2f dBm\n'], ...
    Pav, PavdBm, Pav2, Pav2dBm);

