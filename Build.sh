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
	g++ -std=c++11 -static -g -Wall -I. -c $sourceFile -o $object
	if [[ $? != 0 ]]
	then
		exit 1
	fi
	objects="$objects $object"
done

outputPath=$outputDirectory/lib$output.a
echo Building $outputPath

ar rcs $outputPath$objects