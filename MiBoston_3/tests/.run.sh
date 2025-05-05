touch tests//.timeout
CMD="valgrind --leak-check=full /home/mp/Escritorio/MP/Boston/MiBoston_3/dist/Debug/GNU-Linux/miboston_3  -f ../DataSets/crimes_easy01.crm ../DataSets/crimes_easy01.crm 1> tests//.out13 2>&1"
eval $CMD
rm tests//.timeout
