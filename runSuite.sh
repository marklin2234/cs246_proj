#!/bin/bash

# Check if correct # of arguments
# If not args -> run without args
# else if not in -> run without in
# else run with both
# Check if .expect file exists
# Output if test failed to stdout

if [ $# -ne 2 ]; then
  echo "2 arguments required" >&2
  exit 1
fi

for stem in $(cat $1); do
  if [ ! -f ${stem}.expect ]; then
    echo ${stem}.expect does not exist >&2
    exit 1
  fi

  TEMPFILE=$(mktemp)

  if [[ -f ${stem}.args && -f ${stem}.in ]]; then
    $2 $(cat ${stem}.args) <${stem}.in >$TEMPFILE
  elif [ -f ${stem}.in ]; then
    $2 <${stem}.in >$TEMPFILE
  elif [ -f ${stem}.args ]; then
    $2 $(cat ${stem}.args) >$TEMPFILE
  else
    $2 >$TEMPFILE
  fi

  diff $TEMPFILE ${stem}.expect >/dev/null
  if [ $? -ne 0 ]; then
    echo Test failed: $stem
    echo Args:
    if [ -f ${stem}.args ]; then
      echo $(cat ${stem}.args)
    fi
    echo Input:
    if [ -f ${stem}.in ]; then
      echo $(cat ${stem}.in)
    fi
    echo Expected:
    echo $(cat ${stem}.expect)
    echo Actual:
    echo $(cat $TEMPFILE)
  fi

  rm $TEMPFILE
done
