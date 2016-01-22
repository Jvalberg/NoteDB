echo "Installing NoteDB Software suite."

echo "==== Installing NoteMastermind... ==== "
cd NoteMastermind
make
cd ..
echo "====           Done.              ===="


echo "==== Installing NoteScribbler... ==== "
cd NoteScribbler
make
cd ..
echo "====           Done.              ===="

echo "==== Installing NoteSeer... ==== "
cd NoteSeer
make
cd ..
echo "====           Done.              ===="
