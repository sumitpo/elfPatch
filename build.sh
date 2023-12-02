#!/bin/bash
# File              : build.sh
# Author            : guochuliang <2797366715@qq.com>
# Date              : 02.12.2023
# Last Modified Date: 02.12.2023
# Last Modified By  : guochuliang <2797366715@qq.com>


if [ ! -d build ]; then
  mkdir build
fi

(cd build; cmake .. && make; cp elfPatch ..; cp testExe ..)
rm build -rf
