# Morse Code Generator and Decoder

This repository contains a MATLAB course project for encoding and decoding Morse code with audio output. The current repository includes the core MATLAB scripts and the project report PDF.

## Overview

The project provides two main MATLAB components:

- `morse112.m`: an interactive script for:
  - converting plain text into Morse code
  - converting typed Morse code back into text
  - generating and playing Morse audio
  - saving generated Morse audio as `sound4.wav`
- `morseDecode.m`: a reusable MATLAB function that decodes Morse code from an audio signal and estimates the tone frequency used in the recording

## Repository Contents

- `morse112.m` - main interactive encoder/decoder script
- `morseDecode.m` - Morse audio decoding function
- `EEE4702_PROJECT REPORT_Morse Encoder and Decoder with sound.pdf` - project report

## Requirements

- MATLAB
- Signal Processing Toolbox functions used by `morseDecode.m`:
  - `butter`
  - `filtfilt`
  - `hilbert`

## Features

- Encode letters and digits into Morse code
- Decode Morse code symbols back into text
- Play generated Morse sound inside MATLAB
- Export generated Morse audio to a WAV file
- Decode Morse directly from an audio waveform using tone detection
- Return estimated dot and dash timing statistics from recorded Morse audio

## How To Run

### 1. Interactive script

Open MATLAB in this project folder and run:

```matlab
run('morse112.m')
```

You will be prompted to choose:

- `e` for Morse encoding
- `d` for Morse decoding

#### Encoding mode

- Enter plain text when prompted
- The script converts the input to Morse code
- Audio is generated and played automatically
- The generated audio is saved as `sound4.wav`

#### Decoding mode

- Enter Morse code using:
  - spaces between letters
  - `/` between words
- The script prints the decoded text
- Audio for the entered Morse pattern is also played

Example:

```text
Input Morse: .... . .-.. .-.. --- / .-- --- .-. .-.. -..
Output: hello world
```

### 2. Decode Morse from audio

Use `morseDecode.m` when you already have an audio signal:

```matlab
[y, Fs] = audioread('sound4.wav');
[msg, toneFreq, ditstat, dahstat] = morseDecode(y, Fs);
```

Optional tone frequency input:

```matlab
[msg, toneFreq, ditstat, dahstat] = morseDecode(y, Fs, 1000);
```

Returned values:

- `msg` - decoded text message
- `toneFreq` - detected or specified tone frequency
- `ditstat` - dot timing statistics `[mean, std, min, max]`
- `dahstat` - dash timing statistics `[mean, std, min, max]`

## Notes

- `morse112.m` is a command-line MATLAB script, not a standalone desktop application.
- The repository title mentions a graphical user interface, but no dedicated GUI source files are currently present in this repository.
- The script mainly supports alphabetic characters, digits, and limited punctuation.

## Output

When encoding text with `morse112.m`, the project creates:

- `sound4.wav` - generated Morse audio at 13 kHz sample rate

## License

No license file is currently included in this repository.
