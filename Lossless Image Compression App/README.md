# Lossless Image Compression App

MATLAB GUI project for image compression using block-based DCT processing on RGB channels. The application loads an image, applies the compression pipeline, and saves the processed result as a JPEG file.

## Tech Stack

- MATLAB
- GUIDE GUI (`guimain.fig`)
- DCT-based image processing implemented in `guimain.m`

## Project Files

- `guimain.m` - GUI callbacks and compression logic
- `guimain.fig` - GUI layout
- `EEE 4602 Project Report.pdf` - project report

## Workflow

1. Select an input image from the GUI.
2. Review the original image preview and file size.
3. Apply the `8x8` DCT-based low-frequency mask to each RGB channel.
4. Save the processed output as `<original_name>_compressed.jpg`.
5. Review the compressed image and output size in the interface.

## Run

Open the folder in MATLAB and execute:

```matlab
guimain
```

## Notes

- The GUI accepts `.bmp`, `.jpg`, `.png`, and `.tiff` files through `uigetfile`.
- The compression path in `compress_Callback` reads the selected file by name, so running the app from the same working directory as the image file avoids path issues.
