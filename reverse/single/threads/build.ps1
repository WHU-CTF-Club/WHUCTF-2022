# compile
cl.exe .\threads.cpp /EHsc /FC .\sha256.cpp

# compress
./upx.exe -9 -q -f -o threads_upx.exe ./threads.exe

# cleanup
del ./threads.exe
del ./threads.obj
del ./sha256.obj
move ./threads_upx.exe ./threads.exe
