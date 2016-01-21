BINARY_LOCATION=/home/jocke/dev/NoteDB/NoteWriter

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

if [[ -f /bin/NoteWriter ]]; then
	rm /bin/NoteWriter
fi

ln -s "$BINARY_LOCATION/NoteWriter" "/bin/NoteWriter"
