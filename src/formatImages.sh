for f in $(find -type f $1 | grep .bmp); do
	java -jar chformat.jar $f $f
done
