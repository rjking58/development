
#arrays

#array assignment
"START START"

$strAry = @("first","second","third")
$strAry.Count

$strAry
"===================================="
#individual access

'$strAry[1]="' + $strAry[1] + '"'
"===================================="

#hashTable usage

#entry
$EmpNumbers = @{“John Doe” = 112233; “Dave Davis” = 223344; “Justine Smith” = 334455}

#verification
$EmpNumbers
"===================================="

#individual access

'$EmpNumbers["Dave Davis"]=' + $EmpNumbers["Dave Davis"]
"===================================="

#add new

$EmpNumbers["Rose Jones"] = 445566

#verification
$EmpNumbers.Count
$EmpNumbers
"===================================="

#remove

$EmpNumbers.Remove("Rose Jones")

#verification
$EmpNumbers.Count
$EmpNumbers
"===================================="

#clear..
$EmpNumbers.Clear()

#verification
$EmpNumbers
"===================================="


