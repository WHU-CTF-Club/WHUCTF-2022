# generate res file
rc .\bocchi_the_rock.rc

# compile
cl -O2 .\bocchi_the_rock.cpp /arch:AVX512 /EHsc /FC .\imgui\backends\imgui_impl_dx11.cpp .\imgui\backends\imgui_impl_win32.cpp .\imgui\imgui.cpp .\imgui\imgui_demo.cpp .\imgui\imgui_draw.cpp .\imgui\imgui_tables.cpp .\imgui\imgui_widgets.cpp .\crc.cpp /link .\bocchi_the_rock.res

# clean-up
rm -Force .\*.obj
rm -Force .\bocchi_the_rock.res
