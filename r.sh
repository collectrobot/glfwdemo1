mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug ## -DOpenGL_GL_PREFERENCE=LEGACY

make
cd ..
./build/demo2
