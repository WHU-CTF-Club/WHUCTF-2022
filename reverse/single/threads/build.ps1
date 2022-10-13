# compile
cl .\threads.cpp /EHsc /FC .\sha256.cpp

# compress
./upx.exe -9 -q -f -o threads_upx.exe ./threads.exe

# cleanup
rm ./threads.exe
rm ./threads.obj
rm ./sha256.obj
mv ./threads_upx.exe ./threads.exe
