% Si falla pidiendo el codec:
% The file requires the following codec(s) to be installed on your system:
%   video/x-h264
% Lo solucione corriendo sudo apt-get install gstreamer0.10-*


% salto se utiliza para saltear cuadros de la imagen original. Si salto es 1 entonces no saltea ningún cuadro, si es mayor entonces saltea salto-1

function videoToTextfile(videoFilename, textFilename, salto)
	obj = mmreader(videoFilename);
	video = obj.read();
	nFrames = obj.NumberOfFrames;
	frameRate = obj.FrameRate;
	height = size(video,1);
	width = size(video,2);

	% Escribe la cantidad de cuadros que habrá en el archivo
	dlmwrite(textFilename,length(1:salto:nFrames));
	% Escribe el tamaño del cuadro (alto,ancho)
	dlmwrite(textFilename,[height width],'-append');
	% Escribe el frameRate del video original para después armar la nueva versión de manera acorde
	dlmwrite(textFilename,frameRate,'-append');
	% Transforma cada cuadro en grayscale para trabajar con menor cantidad de datos y los imprime en el archivo
	for f = 1:salto:nFrames
		dlmwrite(textFilename,rgb2gray(video(:,:,:,f)),'-append');
	end