function varargout = guimain(varargin)

gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @guimain_OpeningFcn, ...
                   'gui_OutputFcn',  @guimain_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end

function guimain_OpeningFcn(hObject, eventdata, handles, varargin)

handles.output = hObject;

guidata(hObject, handles);

function varargout = guimain_OutputFcn(hObject, eventdata, handles) 

varargout{1} = handles.output;

function select_Callback(hObject, eventdata, handles)

 global file_name;
    [file_name, path] = uigetfile({'*.bmp;*.jpg;*.png;*.tiff'}, ...
                                   'Select an Image File');
    if isequal(file_name, 0)
        return;
    end
    axes(handles.axes1);
    imshow(fullfile(path, file_name));
    fileinfo = dir(fullfile(path, file_name));
    SIZE = fileinfo.bytes;
    Size = SIZE / 1024;
    set(handles.org, 'String', sprintf('Size: %.2f KB', Size));

function compress_Callback(hObject, eventdata, handles)

 global file_name;
    if isempty(file_name)
        errordlg('Please select an image first', 'Error');
        return;
    end
    I1 = imread(fullfile(file_name));
    
    % Apply compression by masking
    I = I1(:,:,1);
    I = im2double(I);
    T = dctmtx(8);
    B = blkproc(I,[8 8],'P1*x*P2',T,T');
    mask = [1   1   1   1   0   0   0   0
            1   1   1   0   0   0   0   0
            1   1   0   0   0   0   0   0
            1   0   0   0   0   0   0   0
            0   0   0   0   0   0   0   0
            0   0   0   0   0   0   0   0
            0   0   0   0   0   0   0   0
            0   0   0   0   0   0   0   0];
    B2 = blkproc(B,[8 8],'P1.*x',mask);
    I2 = blkproc(B2,[8 8],'P1*x*P2',T',T);

    I = I1(:,:,2);
    I = im2double(I);
    B = blkproc(I,[8 8],'P1*x*P2',T,T');
    B2 = blkproc(B,[8 8],'P1.*x',mask);
    I3 = blkproc(B2,[8 8],'P1*x*P2',T',T);

    I = I1(:,:,3);
    I = im2double(I);
    B = blkproc(I,[8 8],'P1*x*P2',T,T');
    B2 = blkproc(B,[8 8],'P1.*x',mask);
    I4 = blkproc(B2,[8 8],'P1*x*P2',T',T);

    I_compressed = cat(3, I2, I3, I4);
    
    % Save compressed image
    compressed_filename = [file_name, '_compressed.jpg']; % Change file format if needed
    imwrite(I_compressed, compressed_filename, 'jpg');
    
    axes(handles.axes2);
    imshow(I_compressed);
    
    fileinfo = dir(compressed_filename);
    SIZE = fileinfo.bytes;
    Size = SIZE / 1024;
    set(handles.comp, 'String', sprintf('Size: %.2f KB', Size));
