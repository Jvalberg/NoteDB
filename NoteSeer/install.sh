
if [[ -L /bin/NoteSeer ]]; then
	rm /bin/NoteSeer 
fi

ln -s /home/jocke/dev/NoteDB/NoteSeer/NoteSeer /bin/NoteSeer
hash NoteSeer
