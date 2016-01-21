BINARY_LOCATION=/home/jocke/dev/NoteDB/NoteScribbler

# Generate the appropriate files and directories
if [[ ! -d /tmp/NoteDB ]]; then
	mkdir /tmp/NoteDB
fi

if [[ ! -f /tmp/NoteDB/note-blob.dat ]]; then
	touch /tmp/NoteDB/note-blob.dat 
fi

if [[ ! -d ~/.notedb ]]; then
	mkdir ~/.notedb
fi

if [[ ! -d ~/.notedb/blobs ]]; then
	mkdir ~/.notedb/blobs
fi

if [[ -L /bin/NoteScribbler ]]; then
	rm /bin/NoteScribbler
fi

ln -s "$BINARY_LOCATION/NoteScribbler" "/bin/NoteScribbler"
