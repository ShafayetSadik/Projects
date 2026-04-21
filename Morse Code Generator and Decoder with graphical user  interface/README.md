# Morse Code Generator and Decoder

MATLAB project for Morse code encoding, decoding, audio generation, and audio-based signal interpretation.

## Project Files

- `morse112.m` - interactive encoder and decoder script
- `morseDecode.m` - audio-based Morse decoder function
- `EEE4702_PROJECT REPORT_Morse Encoder and Decoder with sound.pdf` - final report

## Features

- Encode text into Morse symbols
- Decode typed Morse strings into text
- Generate Morse audio and save it as `sound4.wav`
- Estimate Morse timing and tone frequency from an audio signal

## Run

For the interactive workflow:

```matlab
run('morse112.m')
```

For audio decoding:

```matlab
[y, Fs] = audioread('sound4.wav');
[msg, toneFreq, ditstat, dahstat] = morseDecode(y, Fs);
```

## Notes

- `morse112.m` is a script-driven workflow.
- `morseDecode.m` uses `butter`, `filtfilt`, and `hilbert`, so the required Signal Processing Toolbox functions must be available in MATLAB.
