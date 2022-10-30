# compile necessary stuffs
csc /optimize /out:baby_complex_net.exe .\baby_complex_net.cs
cl -O2 .\baby_complex_native.cpp /arch:AVX512 /EHsc
python .\baby_complex_modifier.py
python -m compileall .\baby_complex_verifier.py

# move binary files for release
rm -r -Force .\bin

mkdir .\bin
mv -Force .\baby_complex_net.exe .\bin\baby_complex_net.exe
mv -Force .\complex_message .\bin\complex_message
mv -Force .\__pycache__ .\bin\__pycache__

# clean up
rm -Force .\baby_complex_native.exe
rm -Force .\baby_complex_native.obj

# compress binary
Compress-Archive -Force -Path .\bin -DestinationPath .\bin.zip
