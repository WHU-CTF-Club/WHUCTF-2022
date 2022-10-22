rm -Force .\baby_smoke.exe

# Get encrypted flag rtf file
python .\baby_smoke_flag.py

# Generate res file
rc.exe .\baby_smoke.rc

# Compile the exe file
# cl.exe -Ox -EHsc .\baby_smoke.cpp /link .\baby_smoke.res
cl.exe -EHsc .\baby_smoke.cpp /link .\baby_smoke.res

# Clean up
rm -Force .\baby_smoke.obj
rm -Force .\baby_smoke.res
rm -Force .\flag.rtf.enc
