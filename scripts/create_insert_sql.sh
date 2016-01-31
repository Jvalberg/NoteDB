OUTPUTFILE=insert_notes.sql
echo "" > $OUTPUTFILE

for f in blobs/*;
do
	TIMESTAMP=$( head -n 1 $f )	
	CONTENT=$( tail -n +2 $f | sed ':a;N;$!ba;s/\n/\\n/g' )
	echo "INSERT INTO notes (Content, Timestamp) VALUES (\"$CONTENT\", timestamp'$TIMESTAMP');" >> $OUTPUTFILE
done
