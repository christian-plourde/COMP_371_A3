x86_64-w64-mingw32-gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.o -c src/glew.c
x86_64-w64-mingw32-gcc -fno-builtin -fno-stack-protector -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a    -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32 -nostdlib
x86_64-w64-mingw32-gcc-ar cr lib/libglew32.a src/glew.o

x86_64-w64-mingw32-gcc -DGLEW_NO_GLU -DGLEW_MX -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
x86_64-w64-mingw32-gcc  -fno-builtin -fno-stack-protector -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o lib/glew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32 -nostdlib
x86_64-w64-mingw32-gcc-ar cr lib/libglew32mx.a src/glew.mx.o