Compiler = g++

SDL2_LINUX_FLAGS = -lSDL2
SDL2_WINDOWS_FLAGS = -lmingw32 -lSDL2main -lSDL2

target_file_linux = Chess
target_file_windows = Chess.exe

IncludeDirectory = Include
SourceDirectory = Src

SourceFiles = $(wildcard $(SourceDirectory)/*.cpp)

windows:
	$(Compiler) -o $(target_file_windows) $(SourceFiles) $(SDL2_WINDOWS_FLAGS)

linux:
	$(Compiler) -o $(target_file_linux) $(SourceFiles) $(SDL2_LINUX_FLAGS)