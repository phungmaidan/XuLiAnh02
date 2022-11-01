# XuLiAnh02
Chương trình xử lí ảnh sử dụng OpenCV viết bằng ngôn ngữ C++. Chương trình được thực thi bởi command line.
	Chương trình được viết có các chức năng sau:
		- Làm trơn ảnh bằng các phương pháp:
			+ Trung bình.
			+ Trung vị.
			+ Gaussian.
		- Phát hiện biên cạnh bằng các phương pháp:
			+ Sobel.
			+ Prewitt.
			+ Laplace.

Hướng dẫn sử dụng:
nhập Command Line để thực hiện:


Làm trơn ảnh (Trung bình cộng).

<Program.exe> -avg <kx> <ky> <InputFilePath> <OutputFilePath>

• Program.exe: the name of executable file

• InputFilePath: the path name of the input file

• OutputFilePath: the path name of the output file

• -avg: the command name

• kx: horizontal kernel size

• ky: vertical kernel size


Làm trơn ảnh (Trung vị).

<Program.exe> -med <kx> <ky> <InputFilePath> <OutputFilePath>

• Program.exe: the name of executable file

• InputFilePath: the path name of the input file

• OutputFilePath: the path name of the output file

• -med: the command name

• kx: horizontal kernel size

• ky: vertical kernel size


Làm trơn ảnh (Gauss).

<Program.exe> -gau <kx> <ky> <InputFilePath> <OutputFilePath>

• Program.exe: the name of executable file

• InputFilePath: the path name of the input file

• OutputFilePath: the path name of the output file

• -gau: the command name

• kx: horizontal kernel size

• ky: vertical kernel size


Phát hiện biên cạnh (Sobel).
<Program.exe> -sobel <InputFilePath> <OutputFilePath>

• Program.exe: the name of executable file

• InputFilePath: the path name of the input file

• OutputFilePath: the path name of the output file

• -sobel: the command name


Đảo ngược ảnh theo chiều ngang.

<Program.exe> -lap <InputFilePath> <OutputFilePath>

• Program.exe: the name of executable file

• InputFilePath: the path name of the input file

• OutputFilePath: the path name of the output file

• -lap: the command name





