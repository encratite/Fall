output=Fall
sourceFiles=Source/*.cpp
objectDirectory=Object
outputDirectory=Output

mkdir -p $objectDirectory
mkdir -p $outputDirectory


objects=
for sourceFile in $sourceFiles
do
	outputFile=$(basename $sourceFile | cut -d. -f1).o
	object=$objectDirectory/$outputFile
	echo Building $sourceFile
	g++ -c $sourceFile -o $object -fPIC -std=c++11 -I.
	if [[ $? != 0 ]]
	then
		exit
	fi
	objects="$objects $object"
done

libraryOutput=$outputDirectory/lib$output.a
echo Building $libraryOutput
ar -cq $libraryOutput$objects
