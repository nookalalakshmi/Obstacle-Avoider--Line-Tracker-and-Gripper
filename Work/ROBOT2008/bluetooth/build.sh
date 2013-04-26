#!/bin/sh

JAVAC="/System/Library/Frameworks/JavaVM.framework/Versions/1.3/Commands/javac"
PREVERIFY="../../mpp-sdk-1127/osx/preverify/preverify"
CLASSPATH="library/jsr082.jar:../../lib/cldcapi10.jar:../../lib/midpapi20.jar:../../lib/mobile.jar" 

echo "Building"
$JAVAC -target 1.1 -bootclasspath $CLASSPATH processing/bluetooth/*.java

echo "Bundling"
mkdir -p to_preverify
jar cvf to_preverify/bluetooth.jar processing/bluetooth/*.class

echo "Preverifying"
$PREVERIFY -classpath /System/Library/Frameworks/JavaVM.framework/Versions/1.3/Classes/classes.jar:$CLASSPATH:. -d library2 to_preverify


