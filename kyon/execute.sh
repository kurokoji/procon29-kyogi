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

if [ "${OS}" = "Mac" ]; then
  cd ./siv3d_v0.2.6_macOS/kyon/kyon/bin
  open ./kyon.app
  cd ../../../../
elif [ "${OS}" = "Linux" ]; then
  cd ./siv3d_v0.2.3_alpha_Linux/kyon/build/
  ./kyon
  cd ../../../
fi
