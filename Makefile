CPP = g++
LD = g++
EIGEN_DIR = eigen3.2.9/
CPPFLAGS = -I/usr/local/include -O3 -std=c++11 -fPIC -I$(EIGEN_DIR) -DEIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET -Wno-deprecated-register
LDFLAGS = -O3 -L/usr/local/lib
INCLUDE = -Iinclude/
LIB = -lpng
TARGET = hw4
OBJS = objs/main.o objs/image.o objs/shape.o objs/sphere.o objs/scene.o objs/checkerboard.o objs/thinlens.o

default: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIB) -o $(TARGET)

objs/main.o: src/main.cpp
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/main.cpp -o objs/main.o

objs/image.o: src/Image.cpp include/Image.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Image.cpp -o objs/image.o

objs/shape.o: src/Shape.cpp include/Shape.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Shape.cpp -o objs/shape.o

objs/sphere.o: src/Sphere.cpp include/Sphere.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Sphere.cpp -o objs/sphere.o

objs/scene.o: src/Scene.cpp include/Scene.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Scene.cpp -o objs/scene.o

objs/checkerboard.o: src/Checkerboard.cpp include/Checkerboard.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Checkerboard.cpp -o objs/checkerboard.o

objs/thinlens.o: src/Thinlens.cpp include/Thinlens.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Thinlens.cpp -o objs/thinlens.o

clean:
	rm -f $(OBJS) hw4
