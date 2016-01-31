SERVER=$( cat db.conf | grep server | awk '{ print $2 }' | xargs )
USERNAME=$( cat db.conf | grep user | awk '{ print $2 }' | xargs )
PASSWORD=$( cat db.conf | grep password | awk '{ print $2 }' | xargs )

MYSQL_RUNNING=$( ps aux | grep -v grep | grep mysqld )

if [[ "$MYSQL_RUNNING" == "" ]]; then
	echo "Please start mysqld process."
	exit
fi

echo "Dropping database..."

mysql -h "$SERVER" -u "$USERNAME" "-p$PASSWORD" < "dropdb.sql"

echo "Done."
