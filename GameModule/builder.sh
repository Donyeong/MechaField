workDir=$1
mainLauncherFile=$2
format=$3
cppPath=${workDir}/${mainLauncherFile}${format}
outPath=${workDir}/${mainLauncherFile}

/usr/bin/g++ -g -std=c++14 ${cppPath} -o ${outPath}

${outPath}