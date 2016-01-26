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

echo "== Creating Config & Environment... == "

USER=user
TMP_FILE_LOCATION=/tmp/NoteDB
TMP_FILE_NAME="$TMP_FILE_LOCATION/note-blob-raw.dat"
CONF_LOCATION=/home/jocke/.notedb
CONF_FILE="$CONF_LOCATION/notedb.conf"
LOG_LOCATION=/home/jocke/.notedb/log
RAW_DATA_LOCATION="$CONF_LOCATION/blobs"
MASTERMIND_DIR="$CONF_LOCATION/mastermind"

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
echo "mastermind_dir $MASTERMIND_DIR" >> $CONF_FILE

echo "====           Done.              ===="
