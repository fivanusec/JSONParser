RED="\e[31m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

cmake -B build
cd build
make

if [ $? -eq 0 ]; then
   echo -e "${GREEN}JSON parser build successfully${ENDCOLOR}"
else
   echo -e "${RED}There was a problem while building JSON parser ${ENDCOLOR}"
fi