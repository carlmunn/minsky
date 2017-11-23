#! /bin/sh

here=`pwd`
if test $? -ne 0; then exit 2; fi
tmp=/tmp/$$
mkdir $tmp
if test $? -ne 0; then exit 2; fi
cd $tmp
if test $? -ne 0; then exit 2; fi

fail()
{
    echo "FAILED" 1>&2
    cd $here
    chmod -R u+w $tmp
    rm -rf $tmp
    exit 1
}

pass()
{
    echo "PASSED" 1>&2
    cd $here
    chmod -R u+w $tmp
    rm -rf $tmp
    exit 0
}

trap "fail" 1 2 3 15

# checks whether Runge-Kutta solver works correctly on example files
# by comparing with Octave
cp -r $here/examples .
for i in examples/*.mky; do
    # math-examples is not a runnable example
    if [ $i = "examples/math-examples.mky" ]; then continue; fi
    # data object not suppported in Octave
    if [ $i = "examples/data-example.mky" ]; then continue; fi

    for order in 1 2 4; do
        for implicit in 0 1; do 
            #not available
            if [ $order -eq 1 -a $implicit -eq 0 ]; then continue; fi
            cat >extraOpts.tcl <<EOF
minsky.implicit $implicit
minsky.order $order
EOF
               
            $here/gui-tk/minsky $here/test/compareWithOctave.tcl $i
            if test $? -ne 0; then echo $i; fail; fi
            octave --no-window-system --silent $here/test/compareWithOctave.m $i
            if test $? -ne 0; then echo $i; fail; fi
        done
    done
done
pass
