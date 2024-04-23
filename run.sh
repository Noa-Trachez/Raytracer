mkdir ./build/
cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j 16
cd ..