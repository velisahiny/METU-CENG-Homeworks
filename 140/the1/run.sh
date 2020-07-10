#ulimit -v 358400
#ulimit -m 358400
ulimit -t 900

mkdir outputs
for i in $(ls inputs); do
	./the1 < inputs/$i &> outputs/$i".out";
done
