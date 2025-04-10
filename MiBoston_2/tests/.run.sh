touch tests//.timeout
CMD="valgrind --leak-check=full /home/mp/Escritorio/MP/Boston/MiBoston_2/dist/Debug/GNU-Linux/miboston_2  data/input09.b2in  tests/output/output.crm 1> tests//.out11 2>&1"
eval $CMD
rm tests//.timeout
