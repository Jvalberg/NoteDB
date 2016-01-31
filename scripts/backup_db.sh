SERVER=$( cat db.conf | grep server | awk '{ print $2 }' | xargs )
USERNAME=$( cat db.conf | grep user | awk '{ print $2 }' | xargs )
PASSWORD=$( cat db.conf | grep password | awk '{ print $2 }' | xargs )

MYSQL_RUNNING=$( ps aux | grep -v grep | grep mysqld )

if [[ "$MYSQL_RUNNING" == "" ]]; then
	echo "Please start mysqld process."
	exit
fi

mysqldump notedb -u $USERNAME -h $SERVER "-p$PASSWORD" > db_backup.sql
