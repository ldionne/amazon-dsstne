#!/bin/bash
#
# Downloads the Cifar-10 dataset and trains a small model for 1 epoch before
# writing predictions to a file called 'result.nc'.
#

if [[ ! -e training.bin ]]; then
  echo "Downloading Cifar-10 dataset"
  wget --quiet https://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz
  echo "Extracting Cifar-10 dataset"
  tar -xzf cifar-10-binary.tar.gz
  mv cifar-10-batches-bin/test_batch.bin test.bin
  cat cifar-10-batches-bin/data_batch_*.bin > training.bin
else
  echo "Using existing training.bin file"
fi

dparse

echo "Training the network (the result will be in result.nc)"
time train -c config.json -i cifar10_training.nc -o cifar10_test.nc -n result.nc -b 256 -e 1
