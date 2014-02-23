#!/usr/bin/perl
# std input/output 
# uses : ouput.txt (output of the Kohonen program), produces confusion matrix and performances measures

$classNbr = 0;
@m = ();
$total = 0;

while($line=<>) { # confusion matrix filling
  if ($line =~/P\s+(\d+)\sR\s+(\d+)\s+/) {
     $p = $1;
     $r = $2;
     if ($r > $classNbr) {
       $classNbr = $r;       
     }
     #print "[$line] $r $p\n";     
     $m[$r][$p]++;
     $total++;
  }
}
$classNbr++;

# ouput
print " $classNbr classes\n";
print " $total data vector used\n\n";
print "Confusion Matrix : \n";
print " predicted: ";
$meanPerf = 0;
  print "fr    ";  
  print "en    ";  
  print "de    ";  
  print "es    ";  
  print "pt    ";  
  print "it    ";  
  print "tr    ";  
  print "\n";

$realClassNbr = 0; # some classes may not be present in dataset
for($i=0;$i<$classNbr;$i++) {
  
  if ($i == 0){
     print "real fr      ";
  }
  elsif ($i == 1){
     print "real en      ";
  }
  elsif ($i == 2){
     print "real de      ";
  }
  elsif ($i == 3){
     print "real es      ";
  }
  elsif ($i == 4){
     print "real pt      ";
  }
  elsif ($i == 5){
     print "real it      ";
  }
  elsif ($i == 6){
     print "real tr      ";
  }

  $total = 0;   
  for($j=0;$j<$classNbr;$j++) { # normalisation
    $total += $m[$i][$j];   
  }
  if ($total!=0){
    for($j=0;$j<$classNbr;$j++) {
       $val = 100*$m[$i][$j]/$total;
       if ($i == $j) {
         $meanPerf += $val;
         $realClassNbr++;
       }
       $val = substr($val,0,5);
       while(length($val)< 5) { # padding
         $val = $val." ";
       } 
       print $val." ";
    }
  }
  print "\n";
}

$meanPerf /= $realClassNbr;
print "\n meanPerformance = $meanPerf %\n";


