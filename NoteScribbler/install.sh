# !/bin/bash
# requires sudo

BINARY_LOCATION=/home/jocke/dev/NoteDB/NoteScribbler

# Generate the appropriate files and directories
if [ ! -d /tmp/NoteDB ]; then
	sudo -u user mkdir /tmp/NoteDB
fi

if [ ! -f /tmp/NoteDB/note-blob.dat ]; then
	sudo -u user touch /tmp/NoteDB/note-blob.dat 
fi

if [ ! -d /home/jocke/.notedb ]; then 
	sudo -u user mkdir /home/jocke/.notedb
fi

if [ ! -d /home/jocke/.notedb/blobs ]; then
	sudo -u user mkdir /home/jocke/.notedb/blobs
fi

if [ -L /bin/NoteScribbler ]; then
	rm /bin/NoteScribbler
fi

ln -s "$BINARY_LOCATION/NoteScribbler" "/bin/NoteScribbler"
hash NoteScribbler
