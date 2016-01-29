USER=user

echo "Installing NoteDB Software suite."
sudo cp build/noted.out /bin/noted
sudo cp build/notectl.out /bin/notectl
hash noted
hash notectl
echo "Done."

echo "Creating Config & Environment..."

TMP_FILE_LOCATION=/tmp/NoteDB
TMP_FILE_NAME="$TMP_FILE_LOCATION/note-blob-raw.dat"
CONF_LOCATION=/home/jocke/.notedb
CONF_FILE="$CONF_LOCATION/notedb.conf"
LOG_LOCATION=/home/jocke/.notedb/log
RAW_DATA_LOCATION="$CONF_LOCATION/blobs"
DAEMON_DIR="$CONF_LOCATION/daemon"
DAEMON_PORT=6490

# Generate the appropriate files and directories
# if [ ! -d $TMP_FILE_LOCATION ]; then
	# sudo -u $USER mkdir -p $TMP_FILE_LOCATION
# fi

# if [ ! -f $TMP_FILE_NAME ]; then
	# sudo -u $USER touch $TMP_FILE_NAME
# fi

if [ ! -d $LOG_LOCATION ]; then
	sudo -u $USER mkdir -p $LOG_LOCATION
fi

# if [ ! -d $RAW_DATA_LOCATION ]; then
	# sudo -u $USER mkdir -p $RAW_DATA_LOCATION
# fi

if [ ! -d $CONF_LOCATION ]; then
	sudo -u $USER mkdir -p $CONF_LOCATION
fi

sudo -u $USER echo "log $LOG_LOCATION" > $CONF_FILE
echo "tmp_file_location $TMP_FILE_NAME" >> $CONF_FILE
echo "raw_data_location $RAW_DATA_LOCATION" >> $CONF_FILE
echo "editor vim" >> $CONF_FILE
echo "" >> $CONF_FILE
echo "daemon_dir $DAEMON_DIR" >> $CONF_FILE
echo "daemon_port $DAEMON_PORT" >> $CONF_FILE

echo "Done."

