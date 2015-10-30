% Si falla pidiendo el codec:
% The file requires the following codec(s) to be installed on your system:
%   video/x-h264
% Lo solucione corriendo sudo apt-get install gstreamer0.10-*


function textfileToVideo(textFilename, videoFilename)
	nFrames = dlmread(textFilename,',',[0 0 0 0]);
	size = dlmread(textFilename,',',[1,0,1,1]);
	height = size(1);
	width = size(2);
	frameRate = dlmread(textFilename,',',[2 0 2 0]);

	writerObj = VideoWriter(videoFilename);
	writerObj.FrameRate = frameRate;
	open(writerObj);
	% Lee cada una de las matrices correspondientes a los cuadros y las guarda en una matriz
	for f = 1:nFrames
		filaInicio = 3+(f-1)*height;
		colInicio = 0;
		filaFin = 3+f*height-1;
		colFin = width-1;
		vid(:,:,1,f) = dlmread(textFilename,',',[filaInicio colInicio filaFin colFin]);
	end
	% Imprime la matriz con todos los cuadros en el video
	writeVideo(writerObj,double(vid/255));
	close(writerObj);