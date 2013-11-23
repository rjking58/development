# comparison operators

#-eq	Equal to
#-lt	Less than
#-gt	Greater than
#-ge	Greater than or Eqaul to
#-le	Less than or equal to
#-ne	Not equal to

#for strings, append 'i' to make it case insensitive.. 'c' to make it sensitive

#logical operators
#-not
# !
#-and
#-or



#if example
$x = 0 #creates a variable x and assigns 2 as the value
if ($x -eq 5) 
{
  Write-Host "Hello my name is Bob"
}
elseif ($x -eq 4) 
{
  Write-Host "Hello, my name is Sue"
}
elseif ($x -eq 2) 
{
  Write-Host "Hello, my name is Troy"
}
elseif ($x -gt 1) 
{
  Write-Host "Hello, my name is Mary"
}
else 
{
  "I have no idea what my name is?"
}

#case sensitive
if("tom" -ceq "TOM")
{
  Write-Host "equal"
}
else
{
  Write-Host "not equal"
}

#case INsensitive
if("tom" -eq "TOM")
{
  Write-Host "equal"
}
else
{
  Write-Host "not equal"
}

#switch
for ($x = 0; $x -le 4; $x++)
{
  switch($x)
  {
    0
    {
      Write-Host $x " its a 0"
    }
    1
    {
      Write-Host $x " its a 1"
    }
    2
    {
      Write-Host $x " its a 2"
    }
    default
    {
      Write-Host $x " its not know to me"
    }
  }
}

$x = 0
while($x -le 4)
{
  switch($x)
  {
    0
    {
      Write-Host $x " its a 0"
    }
    1
    {
      Write-Host $x " its a 1"
    }
    2
    {
      Write-Host $x " its a 2"
    }
    default
    {
      Write-Host $x " its not know to me"
    }
  }
  $x++
}

#foreach

$myAry = @(1,2,3,4)

foreach($myInt in $myAry)
{
  Write-Host $myInt
}