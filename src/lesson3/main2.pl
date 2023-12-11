#! /usr/bin/perl

use warnings FATAL => 'all';
use strict;
use List::Util qw(min);
use List::Util qw(max);

my $filename = '/home/thomas/projects/github.com/advent-of-code-2023/src/lesson3/lesson3-data.txt';

open(FH, '<', $filename) or die $!;
my $globalEnd = 140;
my $line;
my @data = ();
my $i = 0;
while (defined($line = <FH>)) {
    my @splitted = split //, $line;
    my $j = 0;
    foreach (@splitted) {
        if (/[^a-zA-Z0-9\.\s]/) {
            if (/\*/) {
                $data[$i][$j] = "%";
            }
            else {
                $data[$i][$j] = ".";
            }
        }
        else {
            $data[$i][$j] = $_;
        }
        $j++;
    }
    $i++;
}

my $sum = 0;
my %gears = ();
for (my $m = 0; $m < $globalEnd; $m++) {
    my $start = "";
    my $number = "";
    for (my $n = 0; $n <= $globalEnd; $n++) {
        if ($data[$m][$n] eq "." || $data[$m][$n] eq "%" || $n >= $globalEnd) {
            if ($number ne "") {
                check($start, $n, $m, $number);
            }
            $number = "";
            $start = "";
            next
        }
        if ($start eq "") {
            $start = $n;
        }
        $number .= $data[$m][$n];
    }

}
print($sum);

close(FH);

sub check {
    my $start = $_[0];
    my $end = $_[1];
    my $row = $_[2];
    my $number = $_[3];
    my $realStart = max($start - 1, 0);
    my $realEnd = min($end, $globalEnd);
    my $rowStart = max($row - 1, 0);
    my $rowEnd = min($row + 1, $globalEnd - 1);
    for (my $x = $realStart; $x <= $realEnd; $x++) {
        for (my $y = $rowStart; $y <= $rowEnd; $y++) {
            if ($data[$y][$x] eq "%") {
                my $key = $y . "," . $x;
                if (exists($gears{$key})) {
                    $sum = $sum + (($number + 0) * ($gears{$key} + 0));
                }
                else {
                    $gears{$key} = $number;
                }

                return
            }
        }
    }
}

# [10,11 => 345]