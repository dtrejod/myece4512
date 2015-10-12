% Digital Communications 
% Lab 3
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
%
T = 9E-3;
T1 = 2.7E-3;
A1 = 3.3;
T2 = 3.6E-3;
A2 = 1.6;
T3 = T - (T1 + T2);
A3 = 0;

% Simulation Specific Input
%
Ts = 1E-6; % Sample Time Period
fs = 1/Ts; % Sample Frequency
Tvisible = 1; % Periods to show

% FFT Frequency Resolution Scalar
%
fftres = 15;

% Display Max Frequency
%
maxf = 1E3;

% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% Start End Time
%
startTime = 0;
stopTime = T*Tvisible;
Tz = mean([T1 T2]);

% Construct signal
%
A1x = repelem(A1, int64(T1*fs));
A2x = repelem(A2, int64(T2*fs));
A3x = repelem(A3, int64(T3*fs));
A = [A1x A2x A3x];
A = repmat(A, 1, Tvisible);
samL = length(A);
t = linspace(0,stopTime, samL);
sig = timeseries(A, t, 'Name', 'Pulse Input Signal');

% Create seperated Pulses
%

sigDC = mean(A);
A1L = length(A1x);
A1sig = repmat([A1x zeros(1, samL/Tvisible-A1L)], 1, Tvisible);
A2L = length(A2x);
A2sig = repmat([zeros(1, A1L) ...
    A2x zeros(1, samL/Tvisible-(A2L+A1L))], 1, Tvisible);
sig1 = timeseries(A1sig, t, 'Name', 'Pulse1');
sig2 = timeseries(A2sig, t, 'Name', 'Pulse1');

% Plot signal
%
figure();
plot(t, A);
hold on;
plot([startTime stopTime], [1 1].*sigDC, '--');
legend('Actual Signal', 'DC Component');
grid on;
xlabel('Time (secs)');
ylabel('Volts (V)');

% Plot smaller signals
%
figure()
plot(t,A1sig);
hold on;
plot(t,A2sig);
grid on;
xlabel('Time (secs)');
ylabel('Volts (V)');

legend('Pulse1', 'Pulse2');

% Run Simulink Simulation with given workspace parameters
%
options = simset('SrcWorkspace','current');
set_param('lab3', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab3',[],options);

% Plot Frequency Spectra
%
figure();
[FTMAsig , f] = devFFTMagdbm(A, fs, fftres);
hold on
Tavg = mean([T1 Tz]);
xlim([0 maxf]);
grid on;
limits = axis();
legend('Actual Fourier Transform');

% Plot Fourier Transform of Seperate Pulses
%
figure();
[FTMA1sig, ~] = devFFTMagdbm(A1sig, fs, fftres);
hold on;
grid on;
[FTMA2sig, ~] = devFFTMagdbm(A2sig, fs, fftres);
axis(limits);
plot([1/T1 1/T1], ylim, '--');
plot([1/T2 1/T2], ylim, '--');
plot([2/T1 2/T1], ylim, '--');
plot([2/T2 2/T2], ylim, '--');
legend('Pulse 1', 'Pulse 2', '1/T1', '1/T2', '2/T1', '2/T2');

% Find zeros of Fourier Transform
%
FTMAsigInv = 1.01*max(FTMAsig) - FTMAsig;
[~,MinIdxFTMAsig] = findpeaks(FTMAsigInv);

A1sigInv = 1.01*max(FTMA1sig) - FTMA1sig;
[~,MinIdxA1sig] = findpeaks(A1sigInv);

A2sigInv = 1.01*max(FTMA2sig) - FTMA2sig;
[~,MinIdxA2sig] = findpeaks(A2sigInv);


% Print four nulls in signal
%
fMinSig = f(MinIdxFTMAsig(1:4));
fMinSig1 = f(MinIdxA1sig(1:4));
fMinSig2 = f(MinIdxA2sig(1:4));

disp('Actual Signal');
tableLegend = {'Null_Location_freq'; 'Amplitude'};
Presults = table(fMinSig',FTMAsig(MinIdxFTMAsig(1:4))', ...
    'VariableNames', tableLegend);   
disp(Presults);

disp('Pulse1');
Presults = table(fMinSig1',FTMA1sig(MinIdxA1sig(1:4))', ...
    'VariableNames', tableLegend);   
disp(Presults);

disp('Pulse2');
Presults = table(fMinSig2', FTMA2sig(MinIdxA2sig(1:4))', ...
    'VariableNames', tableLegend);   
disp(Presults);