for i in `seq 1 $1`; do ./partial > /tmp/out$i; c=`cat /tmp/out$i | grep FAIL | wc -l | awk '{print $0}'`; if [ $c -gt 0 ]; then echo $i; fi; sleep 1; done;
