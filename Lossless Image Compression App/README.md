# Lossless Image Compression App

This project is a MATLAB GUI application for loading an image, applying block-based DCT compression, and previewing the original and compressed outputs side by side.

Despite the project name, the current implementation is **lossy**, not lossless. The code keeps a subset of low-frequency DCT coefficients and saves the result as a `.jpg` image.

## Project Overview

The application is built with MATLAB GUIDE and uses:

- `guimain.fig` for the GUI layout
- `guimain.m` for the GUI logic and compression routine

Main workflow:

1. Select an image file from the GUI.
2. Display the original image and its size.
3. Apply 8x8 DCT-based coefficient masking to each RGB channel.
4. Reconstruct the image and save it as a compressed JPEG.
5. Display the compressed image and its saved file size.

## Features

- File picker for image selection
- Preview of the original image
- Preview of the compressed image
- Original and compressed file size display
- DCT-based compression applied separately to R, G, and B channels

## Supported Input Formats

The GUI file picker allows:

- `.bmp`
- `.jpg`
- `.png`
- `.tiff`

## Requirements

- MATLAB
- GUIDE support
- Image Processing Toolbox or compatible MATLAB functions for image I/O and block processing

The code uses functions such as:

- `uigetfile`
- `imshow`
- `imread`
- `imwrite`
- `dctmtx`
- `blkproc`

Note: `blkproc` is an older MATLAB function. In newer MATLAB releases, similar behavior is commonly handled with `blockproc`.

## How To Run

1. Open the project folder in MATLAB.
2. Make sure `guimain.m` and `guimain.fig` are both on the MATLAB path or in the current working directory.
3. Run:

```matlab
guimain
```

You can also open `guimain.fig` directly in MATLAB and launch the GUI from there.

## How It Works

The compression logic:

1. Reads the selected image.
2. Splits the image into the three RGB channels.
3. Converts each channel to double precision.
4. Applies an 8x8 DCT transform block by block.
5. Multiplies each DCT block by a fixed mask that preserves mostly low-frequency terms.
6. Reconstructs the channel with the inverse DCT.
7. Recombines the channels and writes the result as a JPEG image.

The mask used in the code keeps only part of the upper-left area of each 8x8 DCT block, which reduces detail and file size.

## Project Files

- [guimain.m](guimain.m) - GUI callbacks and compression logic
- [guimain.fig](guimain.fig) - MATLAB GUIDE GUI layout
- [EEE 4602 Project Report.pdf](EEE%204602%20Project%20Report.pdf) - project report

## Output

The compressed image is saved in the current working directory using the pattern:

```text
<original_file_name>_compressed.jpg
```

Example:

```text
image.png_compressed.jpg
```

## Current Limitations

- The implementation is lossy even though the project title says "Lossless Image Compression App".
- The output format is always JPEG.
- The compression mask is fixed and not configurable from the GUI.
- The code uses older MATLAB GUI/toolbox patterns such as GUIDE and `blkproc`.
- The current script stores only the selected file name globally, which may cause file path issues when the image is outside the current MATLAB folder.

## Possible Improvements

- Rename the project to reflect lossy compression
- Replace `blkproc` with `blockproc`
- Save the selected file path along with the file name
- Let users adjust compression strength from the GUI
- Show compression ratio and quality metrics such as PSNR or SSIM
- Support grayscale images explicitly

## Summary

This is a simple academic MATLAB GUI project demonstrating image compression with block DCT masking. It is useful as a learning project for GUI-based image processing in MATLAB, but it should be documented and extended carefully if it is intended for production or research use.
