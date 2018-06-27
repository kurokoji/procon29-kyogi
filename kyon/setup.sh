#!/bin/sh

# OS check
if [ "$(uname)" = 'Darwin' ]; then
  OS='Mac'

elif [ "$(expr substr "$(uname -s)" 1 5)" = 'Linux' ]; then
  OS='Linux'

elif [ "$(expr substr "$(uname -s)" 1 10)" = 'MINGW32_NT' ]; then 
  OS='Cygwin'

else
  echo "Your platform ($(uname -a)) is not supported."
  exit 1
fi

if [ "${OS}" = "Linux" ]; then
  curl -L -o siv3d_v0.2.3_alpha_Linux.tar.bz2 "https://drive.google.com/uc?export=download&id=1yHSy7ZrcGBbfZAIme1MVZaxqDm9KJ7VO"
  tar -jxvf siv3d_v0.2.3_alpha_Linux.tar.bz2
  rm siv3d_v0.2.3_alpha_Linux.tar.bz2

elif [ "${OS}" = "Mac" ]; then
  FILE_ID=1DGGEBVydakUV-7Si297-vLVP0JUpjXu3
  FILE_NAME=siv3d_v0.2.6_macOS.tar.bz2
  curl -sc /tmp/cookie "https://drive.google.com/uc?export=download&id=${FILE_ID}" > /dev/null
  CODE="$(awk '/_warning_/ {print $NF}' /tmp/cookie)"  
  curl -Lb /tmp/cookie "https://drive.google.com/uc?export=download&confirm=${CODE}&id=${FILE_ID}" -o ${FILE_NAME}

  tar -jxvf siv3d_v0.2.6_macOS.tar.bz2
  rm siv3d_v0.2.6_macOS.tar.bz2

fi
