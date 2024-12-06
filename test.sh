make build

echo ""
echo ""
echo ""
echo "Testing NEW command"
echo ""
cat tests/test_new1.in | ./mtll > tests/test_new1.out
diff -u tests/test_new1.out tests/test_new1.expected > tests/differences.txt

# Check if there are differences and if there are then store the diferences in differences.txt
if [ -s tests/differences.txt ]; then
    echo "Test failed: Files differ. Differences saved to differences.txt."
    cat differences.txt
else
    echo "Test passed: Files are identical."
    echo "This is the basic test to check the functionality of the NEW command"
fi


echo ""
echo ""
echo ""
echo "Testing VIEW command"
echo ""
cat tests/test_view.in | ./mtll > tests/test_view.out
diff -u tests/test_view.out tests/test_view.expected > tests/differences.txt

# Check if there are differences and if there are then store the diferences in differences.txt
if [ -s tests/differences.txt ]; then
    echo "Test failed: Files differ. Differences saved to differences.txt."
    cat differences.txt
else
    echo "Test passed: Files are identical."
    echo "This is the basic test to check the functionality of the VIEW command"
fi


echo ""
echo ""
echo ""
echo "Testing VIEW ALL command"
echo ""
cat tests/test_view_all.in | ./mtll > tests/test_view_all.out
diff -u tests/test_view_all.out tests/test_view_all.expected > tests/differences.txt

# Check if there are differences and if there are then store the diferences in differences.txt
if [ -s tests/differences.txt ]; then
    echo "Test failed: Files differ. Differences sa ved to differences.txt."
    cat differences.txt
else
    echo "Test passed: Files are identical."
    echo "This is the basic test to check the functionality of the VIEW ALL command"
fi




echo ""
echo ""
echo ""
echo "Testing TYPE command"
echo ""
cat tests/test_type.in | ./mtll > tests/test_type.out
diff -u tests/test_type.out tests/test_type.expected > tests/differences.txt

# Check if there are differences and if there are then store the diferences in differences.txt
if [ -s tests/differences.txt ]; then
    echo "Test failed: Files differ. Differences sa ved to differences.txt."
    cat differences.txt
else
    echo "Test 1 passed: Files are identical."
    echo "This is the basic test to check the functionality of the TYPE command"
fi


echo ""
echo ""
echo ""
echo "Testing REMOVE command"
echo ""
cat tests/test_remove.in | ./mtll > tests/test_remove.out
diff -u tests/test_remove.out tests/test_remove.expected > tests/differences.txt

# Check if there are differences and if there are then store the diferences in differences.txt
if [ -s tests/differences.txt ]; then
    echo "Test failed: Files differ. Differences sa ved to differences.txt."
    cat differences.txt
else
    echo "Test 1 passed: Files are identical."
    echo "This is the basic test to check the functionality of the REMOVE command"
fi



echo ""
echo ""
echo ""
echo "Testing part 1 COMBINED "
echo ""
cat tests/test_combined1.in | ./mtll > tests/test_combined1.out
diff -u tests/test_combined1.out tests/test_combined1.expected > tests/differences.txt

# Check if there are differences and if there are then store the diferences in differences.txt
if [ -s tests/differences.txt ]; then
    echo "Test failed: Files differ. Differences sa ved to differences.txt."
    cat differences.txt
else
    echo "Test 1 passed: Files are identical."
    echo "This is the basic test to check the functionality of the program"
fi