for f in $(find $1 -type f | grep .bmp); do
	java -jar chformat.jar $f $f
done
